#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

class ChessBoard
{
public:
    ChessBoard();

    static std::pair<cv::Mat,cv::Mat> findCalibrationVariables(std::string path);
};

#endif // CHESSBOARD_H
