#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbconnector.h"
#include "toss.h"
#include <QTimer>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

MainWindow::MainWindow(Camera* basler, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mBasler(basler)
{
    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(DisplayVideo()));
    Timer->start();
    ui->setupUi(this);
    ui->statusBar->showMessage("Connecting to database...");
    dbconnector connector;
    if(connector.connectToDatabase()) {
        ui->statusBar->showMessage("Connected to database");
    }
    else {
        QMessageBox::information(this, "Not connected", "Failed connecting to database");
        ui->statusBar->showMessage("Not connected to database");
    }

    mBasler->camera->StartGrabbing();

    server = new TcpIPServer();
    serverthread = new std::thread(&TcpIPServer::connectToClientandStoplistening, server);

    int numberOfTosses = connector.getNumberOfTosses(mToss);
    std::string tosses = std::to_string(numberOfTosses);
    QString qTosses = QString::fromStdString(tosses);
    ui->leNumberOfTosses->setText(qTosses);

    double averagePrecision = connector.getAveragePrecision(mToss);
    std::string precision = std::to_string(averagePrecision);
    QString qPrecision = QString::fromStdString(precision);
    ui->lePrecision->setText(qPrecision);

    mToss.setTestNumber(connector.getTestNumber());

    int testNumber = mToss.getTestNumber();
    std::string sTestNumber = std::to_string(testNumber);
    QString qTestNumber = QString::fromStdString(sTestNumber);
    ui->leTestNumber->setText(qTestNumber);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbDetectTarget_clicked()
{
    //Call detect target function
    cv::Point2f target;
    while (target.x == 0 && target.y == 0) {
        target = mBasler->getTargetLocation(grappedImage = mBasler->getMat());
    }

    mToss.setTargetPositionX(target.x);
    mToss.setTargetPositionY(target.y);

    std::cout << target.x << " " << target.y << std::endl;


    std::string targetPosition = "[" + std::to_string(mToss.getTargetPositionX()) + ", " + std::to_string(mToss.getTargetPositionY()) + "]";
    QString qTargetPosition = QString::fromStdString(targetPosition);
    ui->leTargetDetected->setText(qTargetPosition);
}

void MainWindow::on_pbGripBall_clicked()
{
    //call grip function
    cv::Point2f ballPosition;

    while (ballPosition.x == 0 && ballPosition.y == 0) {
        ballPosition = mBasler->getBallLocation(grappedImage = mBasler->getMat());
    }


    std::string ballPositionStr = "[" + std::to_string(ballPosition.x) + ", " + std::to_string(ballPosition.y) + "]";
    QString qBallPosition = QString::fromStdString(ballPositionStr);
    ui->leBallDeteced->setText(qBallPosition);

    ballPosition.x /= 1000;
    ballPosition.y /= 1000;
    std::cout << ballPosition.x << " " << ballPosition.y << std::endl;
    if (server->isConnected()) {
        server->sendCoordinate(ballPosition.x, ballPosition.y);
    } else {
        std::cerr << "Robot is not connected" << std::endl;
    }


}

void MainWindow::on_pbTossBall_clicked()
{
    if (server->isConnected()) {
        if (mToss.getTargetPositionX() != 0 && mToss.getTargetPositionY() != 0) {
            server->sendThrowingInformation(mToss.getTargetPositionX(), mToss.getTargetPositionY());
        } else {
            std::cout << "No target has been acquired" << std::endl;
        }
        server->readFromClient();
    } else {
        std::cerr << "Robot is not connected" << std::endl;
    }


    server->readFromClient();
    cv::Point2f ballPosition;
    while (ballPosition.x == 0 && ballPosition.y == 0) {
        ballPosition = mBasler->getBallLocation(grappedImage = mBasler->getMat());
    }

    mToss.setTossPositionX(ballPosition.x);
    mToss.setTossPositionY(ballPosition.y);
    std::string ballLanded = "[" + std::to_string(mToss.getTossPositionX()) + ", " + std::to_string(mToss.getTossPositionY()) + "]";
    QString qBallLanded = QString::fromStdString(ballLanded);
    ui->leBallLanded->setText(qBallLanded);

    std::string ballVelocity = std::to_string(mToss.getVelocity());
    QString qBallVelocity = QString::fromStdString(ballVelocity);
    ui->leVelocityToss->setText(qBallVelocity);

    double precision;
    precision = sqrt((mToss.getTargetPositionX()-mToss.getTossPositionX())*(mToss.getTargetPositionX()-mToss.getTossPositionX())+(mToss.getTargetPositionY()-mToss.getTossPositionY())*(mToss.getTargetPositionY()-mToss.getTossPositionY()));
    std::string tossPrecision = std::to_string(precision);
    QString qTossPrecision = QString::fromStdString(tossPrecision);
    ui->leTossPrecision->setText(qTossPrecision);

}

void MainWindow::on_pbAddToss_clicked()
{
    dbconnector connector;
    connector.addTossToDatabase(mToss);

    int numberOfTosses = connector.getNumberOfTosses(mToss);
    std::string tosses = std::to_string(numberOfTosses);
    QString qTosses = QString::fromStdString(tosses);
    ui->leNumberOfTosses->setText(qTosses);

    double averagePrecision = connector.getAveragePrecision(mToss);
    std::string precision = std::to_string(averagePrecision);
    QString qPrecision = QString::fromStdString(precision);
    ui->lePrecision->setText(qPrecision);
    std::cout << "HELLO" << std::endl;
    serverthread = new std::thread(&TcpIPServer::connectToClientandStoplistening, server);
}

void MainWindow::on_pbCreateNewTest_clicked()
{
    dbconnector connector;
    int oldTestNumber = connector.getTestNumber();
    mToss.setTestNumber(oldTestNumber+1);

    int newTestNumber = mToss.getTestNumber();
    std::string sNewTestNumber = std::to_string(newTestNumber);
    QString qNewTestNumber = QString::fromStdString(sNewTestNumber);
    ui->leTestNumber->setText(qNewTestNumber);

    int numberOfTosses = connector.getNumberOfTosses(mToss);
    std::string tosses = std::to_string(numberOfTosses);
    QString qTosses = QString::fromStdString(tosses);
    ui->leNumberOfTosses->setText(qTosses);

    double averagePrecision = connector.getAveragePrecision(mToss);
    std::string precision = std::to_string(averagePrecision);
    QString qPrecision = QString::fromStdString(precision);
    ui->lePrecision->setText(qPrecision);

}

void MainWindow::DisplayVideo(){
    grappedImage = mBasler->getMat();

    mBasler->getBallLocation(grappedImage);
    if (grappedImage.empty()) {
      std::cout << "Could not load image";
    }

    cv::cvtColor(grappedImage, grappedImage, CV_BGR2RGB);
    QImage imdisplay((uchar*)grappedImage.data, grappedImage.cols, grappedImage.rows, grappedImage.step, QImage::Format_RGB888);
    ui->display_video->setPixmap(QPixmap::fromImage(imdisplay));
}


