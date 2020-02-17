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
    QGridLayout *gridLayout_6;
    QPushButton *btnQuit;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBoxSettings;
    QGridLayout *gridLayout;
    QLabel *currentVBin;
    QLabel *labelBinningV;
    QLabel *currentFrameRate;
    QPushButton *btnApplyGain;
    QLabel *currentValue;
    QSpacerItem *verticalSpacer;
    QPushButton *btnApplyFrameRate;
    QComboBox *inputVBin;
    QPushButton *btnApplyAll;
    QLabel *currentGain;
    QLabel *currentHBin;
    QLabel *labelBinningH;
    QLabel *labelIntegTime;
    QLabel *inputValue;
    QLabel *labelBinning;
    QLabel *labelOffset;
    QLabel *labelFrameRate;
    QPushButton *btnReset;
    QDoubleSpinBox *inputGain;
    QSpinBox *inputIntegTime;
    QDoubleSpinBox *inputFrameRate;
    QPushButton *btnApplyIntegTime;
    QComboBox *inputHBin;
    QLabel *currentIntegTime;
    QDoubleSpinBox *inputOffset;
    QLabel *currentOffset;
    QLabel *labelGain;
    QPushButton *btnApplyOffset;
    QPushButton *btnApplyBin;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnStop;
    QPushButton *btnGrab;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBoxSerial;
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
    QLabel *imageLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(640, 595);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        btnQuit = new QPushButton(centralwidget);
        btnQuit->setObjectName(QString::fromUtf8("btnQuit"));

        gridLayout_6->addWidget(btnQuit, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_6, 3, 0, 1, 3);

        groupBoxSettings = new QGroupBox(centralwidget);
        groupBoxSettings->setObjectName(QString::fromUtf8("groupBoxSettings"));
        gridLayout = new QGridLayout(groupBoxSettings);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        currentVBin = new QLabel(groupBoxSettings);
        currentVBin->setObjectName(QString::fromUtf8("currentVBin"));
        currentVBin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentVBin, 6, 1, 1, 1);

        labelBinningV = new QLabel(groupBoxSettings);
        labelBinningV->setObjectName(QString::fromUtf8("labelBinningV"));
        labelBinningV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelBinningV, 6, 0, 1, 1);

        currentFrameRate = new QLabel(groupBoxSettings);
        currentFrameRate->setObjectName(QString::fromUtf8("currentFrameRate"));
        currentFrameRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentFrameRate, 8, 1, 1, 1);

        btnApplyGain = new QPushButton(groupBoxSettings);
        btnApplyGain->setObjectName(QString::fromUtf8("btnApplyGain"));

        gridLayout->addWidget(btnApplyGain, 1, 3, 1, 1);

        currentValue = new QLabel(groupBoxSettings);
        currentValue->setObjectName(QString::fromUtf8("currentValue"));
        currentValue->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(currentValue, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 10, 0, 1, 1);

        btnApplyFrameRate = new QPushButton(groupBoxSettings);
        btnApplyFrameRate->setObjectName(QString::fromUtf8("btnApplyFrameRate"));

        gridLayout->addWidget(btnApplyFrameRate, 8, 3, 1, 1);

        inputVBin = new QComboBox(groupBoxSettings);
        inputVBin->addItem(QString());
        inputVBin->addItem(QString());
        inputVBin->addItem(QString());
        inputVBin->addItem(QString());
        inputVBin->setObjectName(QString::fromUtf8("inputVBin"));

        gridLayout->addWidget(inputVBin, 6, 2, 1, 1);

        btnApplyAll = new QPushButton(groupBoxSettings);
        btnApplyAll->setObjectName(QString::fromUtf8("btnApplyAll"));

        gridLayout->addWidget(btnApplyAll, 9, 2, 1, 1);

        currentGain = new QLabel(groupBoxSettings);
        currentGain->setObjectName(QString::fromUtf8("currentGain"));
        currentGain->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentGain, 1, 1, 1, 1);

        currentHBin = new QLabel(groupBoxSettings);
        currentHBin->setObjectName(QString::fromUtf8("currentHBin"));
        currentHBin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentHBin, 5, 1, 1, 1);

        labelBinningH = new QLabel(groupBoxSettings);
        labelBinningH->setObjectName(QString::fromUtf8("labelBinningH"));
        labelBinningH->setLayoutDirection(Qt::LeftToRight);
        labelBinningH->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelBinningH, 5, 0, 1, 1);

        labelIntegTime = new QLabel(groupBoxSettings);
        labelIntegTime->setObjectName(QString::fromUtf8("labelIntegTime"));

        gridLayout->addWidget(labelIntegTime, 7, 0, 1, 1);

        inputValue = new QLabel(groupBoxSettings);
        inputValue->setObjectName(QString::fromUtf8("inputValue"));

        gridLayout->addWidget(inputValue, 0, 2, 1, 1);

        labelBinning = new QLabel(groupBoxSettings);
        labelBinning->setObjectName(QString::fromUtf8("labelBinning"));

        gridLayout->addWidget(labelBinning, 4, 0, 1, 1);

        labelOffset = new QLabel(groupBoxSettings);
        labelOffset->setObjectName(QString::fromUtf8("labelOffset"));

        gridLayout->addWidget(labelOffset, 2, 0, 1, 1);

        labelFrameRate = new QLabel(groupBoxSettings);
        labelFrameRate->setObjectName(QString::fromUtf8("labelFrameRate"));

        gridLayout->addWidget(labelFrameRate, 8, 0, 1, 1);

        btnReset = new QPushButton(groupBoxSettings);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));

        gridLayout->addWidget(btnReset, 9, 1, 1, 1);

        inputGain = new QDoubleSpinBox(groupBoxSettings);
        inputGain->setObjectName(QString::fromUtf8("inputGain"));
        inputGain->setMinimum(1.000000000000000);
        inputGain->setMaximum(10.000000000000000);
        inputGain->setSingleStep(0.100000000000000);

        gridLayout->addWidget(inputGain, 1, 2, 1, 1);

        inputIntegTime = new QSpinBox(groupBoxSettings);
        inputIntegTime->setObjectName(QString::fromUtf8("inputIntegTime"));
        inputIntegTime->setMinimum(5);
        inputIntegTime->setMaximum(1000000);
        inputIntegTime->setValue(31221);
        inputIntegTime->setDisplayIntegerBase(10);

        gridLayout->addWidget(inputIntegTime, 7, 2, 1, 1);

        inputFrameRate = new QDoubleSpinBox(groupBoxSettings);
        inputFrameRate->setObjectName(QString::fromUtf8("inputFrameRate"));
        inputFrameRate->setMinimum(1.000000000000000);
        inputFrameRate->setMaximum(200000.000000000000000);
        inputFrameRate->setValue(30.000000000000000);

        gridLayout->addWidget(inputFrameRate, 8, 2, 1, 1);

        btnApplyIntegTime = new QPushButton(groupBoxSettings);
        btnApplyIntegTime->setObjectName(QString::fromUtf8("btnApplyIntegTime"));

        gridLayout->addWidget(btnApplyIntegTime, 7, 3, 1, 1);

        inputHBin = new QComboBox(groupBoxSettings);
        inputHBin->addItem(QString());
        inputHBin->addItem(QString());
        inputHBin->addItem(QString());
        inputHBin->addItem(QString());
        inputHBin->setObjectName(QString::fromUtf8("inputHBin"));
        inputHBin->setMouseTracking(true);

        gridLayout->addWidget(inputHBin, 5, 2, 1, 1);

        currentIntegTime = new QLabel(groupBoxSettings);
        currentIntegTime->setObjectName(QString::fromUtf8("currentIntegTime"));
        currentIntegTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentIntegTime, 7, 1, 1, 1);

        inputOffset = new QDoubleSpinBox(groupBoxSettings);
        inputOffset->setObjectName(QString::fromUtf8("inputOffset"));
        inputOffset->setMinimum(-4095.000000000000000);
        inputOffset->setMaximum(4095.000000000000000);
        inputOffset->setSingleStep(1.000000000000000);
        inputOffset->setValue(50.000000000000000);

        gridLayout->addWidget(inputOffset, 2, 2, 1, 1);

        currentOffset = new QLabel(groupBoxSettings);
        currentOffset->setObjectName(QString::fromUtf8("currentOffset"));
        currentOffset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentOffset, 2, 1, 1, 1);

        labelGain = new QLabel(groupBoxSettings);
        labelGain->setObjectName(QString::fromUtf8("labelGain"));

        gridLayout->addWidget(labelGain, 1, 0, 1, 1);

        btnApplyOffset = new QPushButton(groupBoxSettings);
        btnApplyOffset->setObjectName(QString::fromUtf8("btnApplyOffset"));

        gridLayout->addWidget(btnApplyOffset, 2, 3, 1, 1);

        btnApplyBin = new QPushButton(groupBoxSettings);
        btnApplyBin->setObjectName(QString::fromUtf8("btnApplyBin"));

        gridLayout->addWidget(btnApplyBin, 4, 3, 1, 1);


        gridLayout_2->addWidget(groupBoxSettings, 1, 0, 1, 1);

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


        gridLayout_2->addLayout(gridLayout_4, 2, 0, 1, 1);

        groupBoxSerial = new QGroupBox(centralwidget);
        groupBoxSerial->setObjectName(QString::fromUtf8("groupBoxSerial"));
        gridLayout_3 = new QGridLayout(groupBoxSerial);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelPortManufacturer = new QLabel(groupBoxSerial);
        labelPortManufacturer->setObjectName(QString::fromUtf8("labelPortManufacturer"));

        gridLayout_3->addWidget(labelPortManufacturer, 2, 0, 1, 2);

        boxPortList = new QComboBox(groupBoxSerial);
        boxPortList->setObjectName(QString::fromUtf8("boxPortList"));

        gridLayout_3->addWidget(boxPortList, 0, 0, 1, 2);

        btnConnect = new QPushButton(groupBoxSerial);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));

        gridLayout_3->addWidget(btnConnect, 10, 0, 1, 1);

        btnDisconnect = new QPushButton(groupBoxSerial);
        btnDisconnect->setObjectName(QString::fromUtf8("btnDisconnect"));

        gridLayout_3->addWidget(btnDisconnect, 10, 1, 1, 1);

        labelPortSerialNum = new QLabel(groupBoxSerial);
        labelPortSerialNum->setObjectName(QString::fromUtf8("labelPortSerialNum"));

        gridLayout_3->addWidget(labelPortSerialNum, 3, 0, 1, 2);

        labelPortProductID = new QLabel(groupBoxSerial);
        labelPortProductID->setObjectName(QString::fromUtf8("labelPortProductID"));

        gridLayout_3->addWidget(labelPortProductID, 7, 0, 1, 2);

        labelPortLoc = new QLabel(groupBoxSerial);
        labelPortLoc->setObjectName(QString::fromUtf8("labelPortLoc"));

        gridLayout_3->addWidget(labelPortLoc, 4, 0, 1, 2);

        labelPortVendorID = new QLabel(groupBoxSerial);
        labelPortVendorID->setObjectName(QString::fromUtf8("labelPortVendorID"));

        gridLayout_3->addWidget(labelPortVendorID, 5, 0, 1, 2);

        labelPortDescription = new QLabel(groupBoxSerial);
        labelPortDescription->setObjectName(QString::fromUtf8("labelPortDescription"));

        gridLayout_3->addWidget(labelPortDescription, 1, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 11, 0, 1, 1);


        gridLayout_2->addWidget(groupBoxSerial, 0, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        imageLabel = new QLabel(centralwidget);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));

        gridLayout_5->addWidget(imageLabel, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_5, 0, 1, 3, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 22));
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
        btnQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        groupBoxSettings->setTitle(QCoreApplication::translate("MainWindow", "Camera Settings", nullptr));
        currentVBin->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        labelBinningV->setText(QCoreApplication::translate("MainWindow", "Vertical:", nullptr));
        currentFrameRate->setText(QCoreApplication::translate("MainWindow", "30.00", nullptr));
        btnApplyGain->setText(QCoreApplication::translate("MainWindow", "Apply Gain", nullptr));
        currentValue->setText(QCoreApplication::translate("MainWindow", "Current Value", nullptr));
        btnApplyFrameRate->setText(QCoreApplication::translate("MainWindow", "Apply Frame Rate", nullptr));
        inputVBin->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        inputVBin->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        inputVBin->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));
        inputVBin->setItemText(3, QCoreApplication::translate("MainWindow", "8", nullptr));

        btnApplyAll->setText(QCoreApplication::translate("MainWindow", "Apply All", nullptr));
        currentGain->setText(QCoreApplication::translate("MainWindow", "1.00", nullptr));
        currentHBin->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        labelBinningH->setText(QCoreApplication::translate("MainWindow", "Horizontal:", nullptr));
        labelIntegTime->setText(QCoreApplication::translate("MainWindow", "Integration Time (microsec)", nullptr));
        inputValue->setText(QCoreApplication::translate("MainWindow", "Set as", nullptr));
        labelBinning->setText(QCoreApplication::translate("MainWindow", "Binning", nullptr));
        labelOffset->setText(QCoreApplication::translate("MainWindow", "Offset", nullptr));
        labelFrameRate->setText(QCoreApplication::translate("MainWindow", "Frame Rate (FPS)", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        btnApplyIntegTime->setText(QCoreApplication::translate("MainWindow", "Aplply Integration Time", nullptr));
        inputHBin->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        inputHBin->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        inputHBin->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));
        inputHBin->setItemText(3, QCoreApplication::translate("MainWindow", "8", nullptr));

        currentIntegTime->setText(QCoreApplication::translate("MainWindow", "31221", nullptr));
        currentOffset->setText(QCoreApplication::translate("MainWindow", "50.00", nullptr));
        labelGain->setText(QCoreApplication::translate("MainWindow", "Gain", nullptr));
        btnApplyOffset->setText(QCoreApplication::translate("MainWindow", "Apply Offset", nullptr));
        btnApplyBin->setText(QCoreApplication::translate("MainWindow", "Apply Binning", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        btnGrab->setText(QCoreApplication::translate("MainWindow", "Grab", nullptr));
        groupBoxSerial->setTitle(QCoreApplication::translate("MainWindow", "Serial Configuration", nullptr));
        labelPortManufacturer->setText(QCoreApplication::translate("MainWindow", "Manufacturer:", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        btnDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        labelPortSerialNum->setText(QCoreApplication::translate("MainWindow", "Serial Number:", nullptr));
        labelPortProductID->setText(QCoreApplication::translate("MainWindow", "Product ID:", nullptr));
        labelPortLoc->setText(QCoreApplication::translate("MainWindow", "Location:", nullptr));
        labelPortVendorID->setText(QCoreApplication::translate("MainWindow", "Vendor ID:", nullptr));
        labelPortDescription->setText(QCoreApplication::translate("MainWindow", "Description:", nullptr));
        imageLabel->setText(QCoreApplication::translate("MainWindow", " No image to show. ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
