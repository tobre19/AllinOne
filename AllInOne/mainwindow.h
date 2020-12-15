#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStatusBar>
#include <camera.h>
#include <toss.h>
#include <tcpipserver.h>
#include <thread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Camera* basler, QWidget *parent = 0);
    ~MainWindow();
    QImage imdisplay;
    QTimer* Timer;

private slots:
    void on_pbDetectTarget_clicked();
    void on_pbTossBall_clicked();
    void on_pbAddToss_clicked();
    void on_pbGripBall_clicked();
    void on_pbCreateNewTest_clicked();

public slots:
    void DisplayVideo();

private slots:
    void on_pbConnecToRobot_clicked();

private:
    Ui::MainWindow *ui;
    Camera* mBasler;
    cv::Mat grappedImage;

    TcpIPServer* server;
    std::thread* serverthread;

    Toss mToss;
};

#endif // MAINWINDOW_H
