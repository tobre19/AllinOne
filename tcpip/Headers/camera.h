#ifndef CAMERA_H
#define CAMERA_H
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <pylon/PylonIncludes.h>
#include <chessboard.h>
#include <coordinates.h>

class Camera
{
public:
    Camera(Pylon::CInstantCamera* realcamera);

    cv::Mat getMat();
    cv::Point2f getBallLocation(cv::Mat table);
    cv::Point2f getTargetLocation(cv::Mat table);


    Pylon::CInstantCamera* camera;

    int getFrameCount() const;

private:
    std::pair<cv::Mat,cv::Mat> calibrationMaps;
    cv::Point2f* cameraP;
    cv::Point2f* robotP;
    Pylon::PylonAutoInitTerm autoInitTerm;

    cv::Mat perspective2D;

    GenApi::INodeMap* nodemap;

    GenApi::CIntegerPtr width;
    GenApi::CIntegerPtr height;

    Pylon::CImageFormatConverter formatConverter;

    Pylon::CPylonImage pylonImage;
    cv::Mat openCvImage;

    GenApi::CEnumerationPtr exposureAuto;

    GenApi::CFloatPtr exposureTime;

    // This smart pointer will receive the grab result data.
    Pylon::CGrabResultPtr ptrGrabResult;

    int frameCount;
};


#endif // CAMERA_H
