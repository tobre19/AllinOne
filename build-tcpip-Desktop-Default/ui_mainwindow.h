/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QFormLayout *formLayout;
    QPushButton *pbCreateNewTest;
    QLabel *label_7;
    QLineEdit *leTestNumber;
    QPushButton *pbGripBall;
    QLabel *label_6;
    QLineEdit *leTargetDetected;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *leVelocityToss;
    QLabel *label_8;
    QLineEdit *leTossPrecision;
    QPushButton *pbAddToss;
    QLabel *label_4;
    QLineEdit *leNumberOfTosses;
    QLabel *label_5;
    QLineEdit *lePrecision;
    QLineEdit *leBallDeteced;
    QLineEdit *leBallLanded;
    QPushButton *pbDetectTarget;
    QPushButton *pbTossBall;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *display_video;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1589, 875);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        formLayout = new QFormLayout(widget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        pbCreateNewTest = new QPushButton(widget);
        pbCreateNewTest->setObjectName(QStringLiteral("pbCreateNewTest"));

        formLayout->setWidget(0, QFormLayout::LabelRole, pbCreateNewTest);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_7);

        leTestNumber = new QLineEdit(widget);
        leTestNumber->setObjectName(QStringLiteral("leTestNumber"));

        formLayout->setWidget(1, QFormLayout::FieldRole, leTestNumber);

        pbGripBall = new QPushButton(widget);
        pbGripBall->setObjectName(QStringLiteral("pbGripBall"));

        formLayout->setWidget(5, QFormLayout::LabelRole, pbGripBall);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_6);

        leTargetDetected = new QLineEdit(widget);
        leTargetDetected->setObjectName(QStringLiteral("leTargetDetected"));

        formLayout->setWidget(11, QFormLayout::FieldRole, leTargetDetected);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(14, QFormLayout::LabelRole, label_3);

        leVelocityToss = new QLineEdit(widget);
        leVelocityToss->setObjectName(QStringLiteral("leVelocityToss"));

        formLayout->setWidget(14, QFormLayout::FieldRole, leVelocityToss);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(15, QFormLayout::LabelRole, label_8);

        leTossPrecision = new QLineEdit(widget);
        leTossPrecision->setObjectName(QStringLiteral("leTossPrecision"));

        formLayout->setWidget(15, QFormLayout::FieldRole, leTossPrecision);

        pbAddToss = new QPushButton(widget);
        pbAddToss->setObjectName(QStringLiteral("pbAddToss"));

        formLayout->setWidget(19, QFormLayout::LabelRole, pbAddToss);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(20, QFormLayout::LabelRole, label_4);

        leNumberOfTosses = new QLineEdit(widget);
        leNumberOfTosses->setObjectName(QStringLiteral("leNumberOfTosses"));

        formLayout->setWidget(20, QFormLayout::FieldRole, leNumberOfTosses);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(21, QFormLayout::LabelRole, label_5);

        lePrecision = new QLineEdit(widget);
        lePrecision->setObjectName(QStringLiteral("lePrecision"));

        formLayout->setWidget(21, QFormLayout::FieldRole, lePrecision);

        leBallDeteced = new QLineEdit(widget);
        leBallDeteced->setObjectName(QStringLiteral("leBallDeteced"));

        formLayout->setWidget(12, QFormLayout::FieldRole, leBallDeteced);

        leBallLanded = new QLineEdit(widget);
        leBallLanded->setObjectName(QStringLiteral("leBallLanded"));

        formLayout->setWidget(13, QFormLayout::FieldRole, leBallLanded);

        pbDetectTarget = new QPushButton(widget);
        pbDetectTarget->setObjectName(QStringLiteral("pbDetectTarget"));

        formLayout->setWidget(4, QFormLayout::LabelRole, pbDetectTarget);

        pbTossBall = new QPushButton(widget);
        pbTossBall->setObjectName(QStringLiteral("pbTossBall"));

        formLayout->setWidget(6, QFormLayout::LabelRole, pbTossBall);


        horizontalLayout->addWidget(widget);

        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        display_video = new QLabel(widget_2);
        display_video->setObjectName(QStringLiteral("display_video"));

        verticalLayout_2->addWidget(display_video);


        horizontalLayout->addWidget(widget_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1589, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pbCreateNewTest->setText(QApplication::translate("MainWindow", "Create new test", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Test number", Q_NULLPTR));
        pbGripBall->setText(QApplication::translate("MainWindow", "Grip ball", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Target detected at", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Ball detected at", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Ball landed at", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Velocity af toss", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Precision of toss", Q_NULLPTR));
        pbAddToss->setText(QApplication::translate("MainWindow", "Add toss to database", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Number of tosses in test", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Average precision in test", Q_NULLPTR));
        leBallDeteced->setText(QString());
        pbDetectTarget->setText(QApplication::translate("MainWindow", "Detect target", Q_NULLPTR));
        pbTossBall->setText(QApplication::translate("MainWindow", "Toss ball", Q_NULLPTR));
        display_video->setText(QApplication::translate("MainWindow", "display_video", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
