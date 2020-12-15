#include "coordinates.h"
#include <math.h>

cv::Point Coordinates::offset(-440.085,-49.193);
float Coordinates::pixelsToMM = 1.162;

Coordinates::Coordinates() {}

cv::Point Coordinates::cameraRotateToRobotSys(const cv::Point &cameraXandY)
{
    cv::Point RobotXandY;

    double rotationMatrix[2][2]  = {{0.9235008, 0.38359656}, {0.38359656, -0.9235008}};

    RobotXandY.x = (rotationMatrix[0][0] * (cameraXandY.x * pixelsToMM) + rotationMatrix[0][1] * (cameraXandY.y * pixelsToMM)) + offset.x;
    RobotXandY.y = (rotationMatrix[1][0] * (cameraXandY.x * pixelsToMM) + rotationMatrix[1][1] * (cameraXandY.y * pixelsToMM)) + offset.y;

    return RobotXandY;
}

cv::Point2f *Coordinates::generate4CameraPoints()
{
    cv::Point2f* cameraP = new cv::Point2f[4];
//    cameraP[0] = cameraRotateToRobotSys(cv::Point2f(23, 169));
//    cameraP[1] = cameraRotateToRobotSys(cv::Point2f(25, 855));
//    cameraP[2] = cameraRotateToRobotSys(cv::Point2f(677, 157));
//    cameraP[3] = cameraRotateToRobotSys(cv::Point2f(677, 859));

    cameraP[0] = cv::Point2f(23, 111);
    cameraP[1] = cv::Point2f(669, 105);
    cameraP[2] = cv::Point2f(21, 885);
    cameraP[3] = cv::Point2f(673, 885);

    return cameraP;
}

cv::Point2f *Coordinates::generate4RobotPoints()
{
    cv::Point2f* robotP = new cv::Point2f[4];
//    robotP[0] = cv::Point2f((-332.08), (-245.8));
//    robotP[1] = cv::Point2f((-25.1), (-994.22));
//    robotP[2] = cv::Point2f((363.3), (41.05));
//    robotP[3] = cv::Point2f((677), (-700));

    robotP[0] = cv::Point2f((23), (111));
    robotP[1] = cv::Point2f((669), (111));
    robotP[2] = cv::Point2f((23), (885));
    robotP[3] = cv::Point2f((669), (885));

    return robotP;
}

cv::Point Coordinates::getOffset() const
{
    return offset;
}


