#include "camera.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <camera.h>


Camera::Camera(Pylon::CInstantCamera *realcamera) : camera(realcamera)
{
    calibrationMaps = ChessBoard::findCalibrationVariables("../3Images/*.bmp");
    cameraP = Coordinates::generate4CameraPoints();
    robotP = Coordinates::generate4RobotPoints();

    perspective2D = cv::getPerspectiveTransform(cameraP, robotP);

    int myExposure = 30000;

    try {
        nodemap = &camera->GetNodeMap();
        // Open the camera before accessing any parameters.
        camera->Open();
        // Create pointers to access the camera Width and Height parameters.
        width = nodemap->GetNode("Width");
        height = nodemap->GetNode("Height");

        formatConverter.OutputPixelFormat= Pylon::PixelType_BGR8packed;

        exposureAuto = GenApi::CEnumerationPtr( nodemap->GetNode( "ExposureAuto"));
        if ( GenApi::IsWritable( exposureAuto)){
            exposureAuto->FromString("Off");
            std::cout << "Exposure auto disabled." << std::endl;
        }

        // set custom exposure
        exposureTime = nodemap->GetNode("ExposureTime");
        if(exposureTime.IsValid()) {
            if(myExposure >= exposureTime->GetMin() && myExposure <= exposureTime->GetMax()) {
                exposureTime->SetValue(myExposure);
            }else {
                exposureTime->SetValue(exposureTime->GetMin());
                std::cout << ">> Exposure has been set with the minimum available value." << std::endl;
                std::cout << ">> The available exposure range is [" << exposureTime->GetMin() << " - " << exposureTime->GetMax() << "] (us)" << std::endl;
            }
        }else {

            std::cout << ">> Failed to set exposure value." << std::endl;
        }
        std::cout << "New exposure: " << exposureTime->GetValue() << std::endl;


    } catch (GenICam::GenericException &e)
    {
        // Error handling.
        std::cerr << "An exception occurred." << std::endl
        << e.GetDescription() << std::endl;
        throw;
    }


}

int Camera::getFrameCount() const
{
    return frameCount;
}

cv::Mat Camera::getMat()
{
    cv::Mat table;
    cv::Mat table2D;


    if (camera->IsGrabbing()) {
        // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
        camera->RetrieveResult( 5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);

        // Image grabbed successfully?
        if (ptrGrabResult->GrabSucceeded())
        {
            // Access the image data.
            //cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
            //cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;

            // Convert the grabbed buffer to a pylon image.
            formatConverter.Convert(pylonImage, ptrGrabResult);

            // Create an OpenCV image from a pylon image.
            openCvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());
            cv::remap(openCvImage, openCvImage, calibrationMaps.first, calibrationMaps.second, CV_INTER_LINEAR);

            //////////////////////////////////////////////////////
            //////////// Here your code begins ///////////////////
            //////////////////////////////////////////////////////

            table = cv::Mat(openCvImage, cv::Rect(400,0,700, 905));
//                cv::Mat table(table.rows, table.cols, table.type());


            frameCount++;

        }
        else
        {
            std::cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << std::endl;
        }
    }

    return table;
}

cv::Point2f Camera::getBallLocation(cv::Mat table)
{
    cv::Mat hsv;
    cv::Mat gaussian;
    cv::GaussianBlur(table, gaussian, cv::Size(3,3), 10);
    cv::cvtColor(gaussian, hsv, cv::COLOR_BGR2HSV);


    cv::Mat1b greenmask;
    cv::inRange(hsv, cv::Scalar(50, 170, 100), cv::Scalar(60, 255, 255), greenmask);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(greenmask, circles, CV_HOUGH_GRADIENT, 2, 10, 100, 40, 15, 20);
    cv::Point center;

    for( size_t i = 0; i < circles.size(); i++ )
    {
        cv::Vec3i c = circles[i];
        center = cv::Point(c[0], c[1]);
        // circle center
        cv::circle( table, center, 1, cv::Scalar(0,100,100), 3, cv::LINE_AA);
        // circle outline
        int radius = c[2];
        cv::circle( table, center, radius, cv::Scalar(255,0,255), 3, cv::LINE_AA);
    }

    if (circles.size() == 1) {
        cv::Vec3i c = circles[0];
        center = cv::Point(c[0], c[1]);

        cv::Vec3f angledCenterVec(center.x, center.y, 1);

        cv::Vec3d CenterVec;


//        cv::warpPerspective(table, table2D, perspective2D, table2D.size());


        for (int i = 0 ; i < perspective2D.rows; i++) {
            for (int j = 0; j < perspective2D.cols; j++) {
                CenterVec[i] += perspective2D.at<double>(i,j) * angledCenterVec(j);
            }
        }

        center.x = CenterVec[0];
        center.y = CenterVec[1];

        center = Coordinates::cameraRotateToRobotSys(center);


    }

    return center;
}

cv::Point2f Camera::getTargetLocation(cv::Mat table)
{
    cv::Point2f target;
    cv::Mat hsv;
    cv::Mat gaussian;
    cv::GaussianBlur(table, gaussian, cv::Size(3,3), 10);
    cv::cvtColor(gaussian, hsv, cv::COLOR_BGR2HSV);

    cv::Mat1b redmask1, redmask2;
    cv::inRange(hsv, cv::Scalar(170, 150, 150), cv::Scalar(180, 255, 255), redmask1); //target
    cv::inRange(hsv, cv::Scalar(0, 150, 150), cv::Scalar(10, 255, 255), redmask2); //target

    cv::Mat1b redmask = redmask1 | redmask2;

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(redmask, circles, CV_HOUGH_GRADIENT, 2, 10, 200, 35, 18, 24);

    if (circles.size() == 1) {
        cv::Vec3i c = circles[0];
        target = cv::Point(c[0], c[1]);

        cv::Vec3f angledCenterVec(target.x, target.y, 1);

        cv::Vec3d CenterVec;


//        cv::warpPerspective(table, table2D, perspective2D, table2D.size());


        for (int i = 0 ; i < perspective2D.rows; i++) {
            for (int j = 0; j < perspective2D.cols; j++) {
                CenterVec[i] += perspective2D.at<double>(i,j) * angledCenterVec(j);
            }
        }

        target.x = CenterVec[0];
        target.y = CenterVec[1];

        target = Coordinates::cameraRotateToRobotSys(target);
    }

    return target;
}
