/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnStop;
    QPushButton *btnGrab;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *labelPortManufacturer;
    QComboBox *boxPortList;
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QLabel *labelPortSerialNum;
    QLabel *labelPortProductID;
    QLabel *labelPortLoc;
    QLabel *labelPortVendorID;
    QLabel *labelPortDescription;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QComboBox *boxHBin;
    QLabel *labelFrameRate;
    QLabel *labelBinningH;
    QLabel *labelBinningV;
    QPushButton *btnApp;
    QPushButton *btnReset;
    QLabel *labelIntegTime;
    QLabel *labelOffset;
    QSpacerItem *verticalSpacer;
    QLabel *labelBinning;
    QSpinBox *inputIntegTime;
    QLabel *labelGain;
    QComboBox *boxVBin;
    QDoubleSpinBox *inputGain;
    QDoubleSpinBox *inputOffset;
    QDoubleSpinBox *inputFrameRate;
    QGridLayout *gridLayout_6;
    QPushButton *btnQuit;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(508, 376);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 0, 1, 1);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));

        gridLayout_4->addWidget(btnStop, 0, 2, 1, 1);

        btnGrab = new QPushButton(centralwidget);
        btnGrab->setObjectName(QString::fromUtf8("btnGrab"));

        gridLayout_4->addWidget(btnGrab, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout_4, 1, 0, 1, 2);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelPortManufacturer = new QLabel(groupBox_2);
        labelPortManufacturer->setObjectName(QString::fromUtf8("labelPortManufacturer"));

        gridLayout_3->addWidget(labelPortManufacturer, 2, 0, 1, 2);

        boxPortList = new QComboBox(groupBox_2);
        boxPortList->setObjectName(QString::fromUtf8("boxPortList"));

        gridLayout_3->addWidget(boxPortList, 0, 0, 1, 2);

        btnConnect = new QPushButton(groupBox_2);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));

        gridLayout_3->addWidget(btnConnect, 10, 0, 1, 1);

        btnDisconnect = new QPushButton(groupBox_2);
        btnDisconnect->setObjectName(QString::fromUtf8("btnDisconnect"));

        gridLayout_3->addWidget(btnDisconnect, 10, 1, 1, 1);

        labelPortSerialNum = new QLabel(groupBox_2);
        labelPortSerialNum->setObjectName(QString::fromUtf8("labelPortSerialNum"));

        gridLayout_3->addWidget(labelPortSerialNum, 3, 0, 1, 2);

        labelPortProductID = new QLabel(groupBox_2);
        labelPortProductID->setObjectName(QString::fromUtf8("labelPortProductID"));

        gridLayout_3->addWidget(labelPortProductID, 7, 0, 1, 2);

        labelPortLoc = new QLabel(groupBox_2);
        labelPortLoc->setObjectName(QString::fromUtf8("labelPortLoc"));

        gridLayout_3->addWidget(labelPortLoc, 4, 0, 1, 2);

        labelPortVendorID = new QLabel(groupBox_2);
        labelPortVendorID->setObjectName(QString::fromUtf8("labelPortVendorID"));

        gridLayout_3->addWidget(labelPortVendorID, 5, 0, 1, 2);

        labelPortDescription = new QLabel(groupBox_2);
        labelPortDescription->setObjectName(QString::fromUtf8("labelPortDescription"));

        gridLayout_3->addWidget(labelPortDescription, 1, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 11, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        boxHBin = new QComboBox(groupBox);
        boxHBin->addItem(QString());
        boxHBin->addItem(QString());
        boxHBin->addItem(QString());
        boxHBin->addItem(QString());
        boxHBin->setObjectName(QString::fromUtf8("boxHBin"));
        boxHBin->setMouseTracking(true);

        gridLayout->addWidget(boxHBin, 4, 1, 1, 1);

        labelFrameRate = new QLabel(groupBox);
        labelFrameRate->setObjectName(QString::fromUtf8("labelFrameRate"));

        gridLayout->addWidget(labelFrameRate, 7, 0, 1, 1);

        labelBinningH = new QLabel(groupBox);
        labelBinningH->setObjectName(QString::fromUtf8("labelBinningH"));
        labelBinningH->setLayoutDirection(Qt::LeftToRight);
        labelBinningH->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelBinningH, 4, 0, 1, 1);

        labelBinningV = new QLabel(groupBox);
        labelBinningV->setObjectName(QString::fromUtf8("labelBinningV"));
        labelBinningV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelBinningV, 5, 0, 1, 1);

        btnApp = new QPushButton(groupBox);
        btnApp->setObjectName(QString::fromUtf8("btnApp"));

        gridLayout->addWidget(btnApp, 8, 0, 1, 1);

        btnReset = new QPushButton(groupBox);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));

        gridLayout->addWidget(btnReset, 8, 1, 1, 1);

        labelIntegTime = new QLabel(groupBox);
        labelIntegTime->setObjectName(QString::fromUtf8("labelIntegTime"));

        gridLayout->addWidget(labelIntegTime, 6, 0, 1, 1);

        labelOffset = new QLabel(groupBox);
        labelOffset->setObjectName(QString::fromUtf8("labelOffset"));

        gridLayout->addWidget(labelOffset, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 9, 0, 1, 1);

        labelBinning = new QLabel(groupBox);
        labelBinning->setObjectName(QString::fromUtf8("labelBinning"));

        gridLayout->addWidget(labelBinning, 3, 0, 1, 1);

        inputIntegTime = new QSpinBox(groupBox);
        inputIntegTime->setObjectName(QString::fromUtf8("inputIntegTime"));
        inputIntegTime->setMinimum(5);
        inputIntegTime->setMaximum(1000000);
        inputIntegTime->setValue(31221);
        inputIntegTime->setDisplayIntegerBase(10);

        gridLayout->addWidget(inputIntegTime, 6, 1, 1, 1);

        labelGain = new QLabel(groupBox);
        labelGain->setObjectName(QString::fromUtf8("labelGain"));

        gridLayout->addWidget(labelGain, 0, 0, 1, 1);

        boxVBin = new QComboBox(groupBox);
        boxVBin->addItem(QString());
        boxVBin->addItem(QString());
        boxVBin->addItem(QString());
        boxVBin->addItem(QString());
        boxVBin->setObjectName(QString::fromUtf8("boxVBin"));

        gridLayout->addWidget(boxVBin, 5, 1, 1, 1);

        inputGain = new QDoubleSpinBox(groupBox);
        inputGain->setObjectName(QString::fromUtf8("inputGain"));
        inputGain->setMinimum(1.000000000000000);
        inputGain->setMaximum(10.000000000000000);
        inputGain->setSingleStep(0.100000000000000);

        gridLayout->addWidget(inputGain, 0, 1, 1, 1);

        inputOffset = new QDoubleSpinBox(groupBox);
        inputOffset->setObjectName(QString::fromUtf8("inputOffset"));
        inputOffset->setMinimum(-4095.000000000000000);
        inputOffset->setMaximum(4095.000000000000000);
        inputOffset->setSingleStep(1.000000000000000);
        inputOffset->setValue(50.000000000000000);

        gridLayout->addWidget(inputOffset, 1, 1, 1, 1);

        inputFrameRate = new QDoubleSpinBox(groupBox);
        inputFrameRate->setObjectName(QString::fromUtf8("inputFrameRate"));
        inputFrameRate->setMinimum(1.000000000000000);
        inputFrameRate->setMaximum(200000.000000000000000);
        inputFrameRate->setValue(30.000000000000000);

        gridLayout->addWidget(inputFrameRate, 7, 1, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 1, 2, 1);


        gridLayout_2->addLayout(gridLayout_5, 0, 1, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        btnQuit = new QPushButton(centralwidget);
        btnQuit->setObjectName(QString::fromUtf8("btnQuit"));

        gridLayout_6->addWidget(btnQuit, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_6, 2, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 508, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        btnGrab->setText(QCoreApplication::translate("MainWindow", "Grab", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Serial Configuration", nullptr));
        labelPortManufacturer->setText(QCoreApplication::translate("MainWindow", "Manufacturer:", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        btnDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        labelPortSerialNum->setText(QCoreApplication::translate("MainWindow", "Serial Number:", nullptr));
        labelPortProductID->setText(QCoreApplication::translate("MainWindow", "Product ID:", nullptr));
        labelPortLoc->setText(QCoreApplication::translate("MainWindow", "Location:", nullptr));
        labelPortVendorID->setText(QCoreApplication::translate("MainWindow", "Vendor ID:", nullptr));
        labelPortDescription->setText(QCoreApplication::translate("MainWindow", "Description:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Camera Settings", nullptr));
        boxHBin->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        boxHBin->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        boxHBin->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));
        boxHBin->setItemText(3, QCoreApplication::translate("MainWindow", "8", nullptr));

        labelFrameRate->setText(QCoreApplication::translate("MainWindow", "Frame Rate (FPS)", nullptr));
        labelBinningH->setText(QCoreApplication::translate("MainWindow", "Horizontal:", nullptr));
        labelBinningV->setText(QCoreApplication::translate("MainWindow", "Vertical:", nullptr));
        btnApp->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        labelIntegTime->setText(QCoreApplication::translate("MainWindow", "Integration Time (microsec)", nullptr));
        labelOffset->setText(QCoreApplication::translate("MainWindow", "Offset", nullptr));
        labelBinning->setText(QCoreApplication::translate("MainWindow", "Binning", nullptr));
        labelGain->setText(QCoreApplication::translate("MainWindow", "Gain", nullptr));
        boxVBin->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        boxVBin->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        boxVBin->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));
        boxVBin->setItemText(3, QCoreApplication::translate("MainWindow", "8", nullptr));

        btnQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
