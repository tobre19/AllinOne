#include "mainwindow.h"
#include <QApplication>
#include "dbconnector.h"
#include "toss.h"
#include "tcpipserver.h"

int main(int argc, char *argv[])
{
    Pylon::PylonAutoInitTerm autoInitTerm;

    try {
        Pylon::CInstantCamera realcamera( Pylon::CTlFactory::GetInstance().CreateFirstDevice());
        Camera* basler = new Camera(&realcamera);


        QApplication a(argc, argv);
        MainWindow w(basler);
        w.show();

        return a.exec();

    } catch (GenICam::GenericException &e) {
        // Error handling.
        std::cerr << "An exception occurred." << std::endl
        << e.GetDescription() << std::endl;
    }
}
