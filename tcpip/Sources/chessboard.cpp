#include "chessboard.h"

ChessBoard::ChessBoard()
{

}


std::pair<cv::Mat, cv::Mat> ChessBoard::findCalibrationVariables(std::string path)
{
    std::vector<cv::String> fileNames;
    cv::glob(path, fileNames, false);
    cv::Size patternSize(7 - 1, 10  - 1);
    std::vector<std::vector<cv::Point2f>> q(fileNames.size());

    // Detect feature points
    std::size_t i = 0;
    for (auto const &f : fileNames) {
      std::cout << std::string(f) << std::endl;

      cv::Mat img = cv::imread(f);
      bool success;
      // 1. Read in the image an call cv::findChessboardCorners()
      success = cv::findChessboardCorners(img, patternSize, q[i]);
  //    std::cout << success << std::endl;

      // 2. Use cv::cornerSubPix() to refine the found corner detections
      cv::Mat grey(img.rows, img.rows, img.type(), cv::Scalar(0,0,0));
      cv::cvtColor(img, grey, cv::COLOR_BGR2GRAY);
      if (success) {
          cv::cornerSubPix(grey, q[i], cv::Size(4,4), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.01));
      }
      // Display
      cv::drawChessboardCorners(grey, patternSize, q[i], success);

      i++;
    }

    std::vector<cv::Point3f> QView;
    for (int i = 0; i < patternSize.width; ++i) {
        for (int j = 0; j < patternSize.height; ++j) {
            cv::Point3f p3f(static_cast<float>(j)*70,static_cast<float>(i)*70, 0.f);
            QView.push_back(p3f);
        }
    }

    std::vector<std::vector<cv::Point3f>> Q(fileNames.size());
    for (int i = 0; i < fileNames.size(); ++i) { Q[i] = QView; }

    cv::Matx33f K(cv::Matx33f::eye());  // intrinsic camera matrix
    cv::Vec<float, 5> k(0, 0, 0, 0, 0); // distortion coefficients

    std::vector<cv::Mat> rvecs, tvecs;
    std::vector<double> stdIntrinsics, stdExtrinsics, perViewErrors;
    int flags = cv::CALIB_FIX_ASPECT_RATIO + cv::CALIB_FIX_K3 +
                cv::CALIB_ZERO_TANGENT_DIST + cv::CALIB_FIX_PRINCIPAL_POINT;
    cv::Size frameSize(1440, 1080);

    std::cout << "Calibrating..." << std::endl;
    // 4. Call "float error = cv::calibrateCamera()" with the input coordinates
    // and output parameters as declared above...

    float error = cv::calibrateCamera(Q, q, frameSize, K, k, rvecs, tvecs, stdIntrinsics, stdExtrinsics, perViewErrors, flags);

    std::cout << "Reprojection error = " << error << "\nK =\n"
              << K << "\nk=\n"
              << k << std::endl;

    // Precompute lens correction interpolation
    cv::Mat mapX, mapY;
    cv::initUndistortRectifyMap(K, k, cv::Matx33f::eye(), K, frameSize, CV_32FC1,
                                mapX, mapY);
    std::pair<cv::Mat,cv::Mat> calibrationVariables(mapX, mapY);
    return calibrationVariables;

}
