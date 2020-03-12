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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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
    QGridLayout *gridLayout_8;
    QLabel *imageLabel;
    QGridLayout *gridLayout_5;
    QTabWidget *tabWidget;
    QWidget *tabSettings;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBoxSerial;
    QGridLayout *gridLayout_3;
    QPushButton *btnConnect;
    QComboBox *boxPortList;
    QPushButton *btnDisconnect;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBoxSettings;
    QGridLayout *gridLayout;
    QPushButton *btnApplyGain;
    QDoubleSpinBox *inputOffset;
    QLabel *currentFrameRate;
    QLabel *labelBinning;
    QLabel *currentVBin;
    QComboBox *inputHBin;
    QLabel *currentHBin;
    QPushButton *btnApplyOffset;
    QLabel *labelOffset;
    QLabel *labelBinningV;
    QDoubleSpinBox *inputGain;
    QPushButton *btnApplyAll;
    QPushButton *btnApplyBin;
    QPushButton *btnReset;
    QDoubleSpinBox *inputFrameRate;
    QLabel *inputValue;
    QLabel *labelBinningH;
    QLabel *labelFrameRate;
    QPushButton *btnApplyFrameRate;
    QSpinBox *inputIntegTime;
    QLabel *labelIntegTime;
    QLabel *currentOffset;
    QLabel *currentIntegTime;
    QLabel *currentValue;
    QLabel *labelGain;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnApplyIntegTime;
    QComboBox *inputVBin;
    QLabel *currentGain;
    QWidget *tabSave;
    QGridLayout *gridLayout_11;
    QGroupBox *groupBoxSqn;
    QGridLayout *gridLayout_13;
    QLabel *labelNIter;
    QCheckBox *chkSequence;
    QLabel *labelTIntv;
    QSpinBox *inputNIter;
    QSpinBox *inputTIntv;
    QGridLayout *gridLayout_14;
    QPushButton *btnCancel;
    QPushButton *btnStart;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *groupBoxSave;
    QGridLayout *gridLayout_9;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelDirectory;
    QPushButton *btnChooseDir;
    QGridLayout *gridLayout_7;
    QSpinBox *inputNFrame;
    QSpinBox *inputTimeIntv;
    QLabel *labelTimeIntv;
    QSpinBox *inputNFile;
    QLabel *labelNFrame;
    QLabel *labelFramePerFile;
    QSpinBox *inputFramePerFile;
    QLabel *labelNFile;
    QRadioButton *btnBurst;
    QRadioButton *btnSingleFrame;
    QPushButton *btnSave;
    QLineEdit *inputDir;
    QGroupBox *groupBoxMode;
    QGridLayout *gridLayout_12;
    QSpinBox *inputNFrm;
    QRadioButton *labelSingleMode;
    QRadioButton *labelNFrmMode;
    QRadioButton *labelUnlimMode;
    QLabel *stdevLabel;
    QGridLayout *gridLayout_4;
    QPushButton *btnGrab;
    QPushButton *btnStop;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(665, 640);
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


        gridLayout_2->addLayout(gridLayout_6, 6, 3, 1, 1);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        imageLabel = new QLabel(centralwidget);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));

        gridLayout_8->addWidget(imageLabel, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_8, 0, 0, 6, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabSettings = new QWidget();
        tabSettings->setObjectName(QString::fromUtf8("tabSettings"));
        gridLayout_10 = new QGridLayout(tabSettings);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        groupBoxSerial = new QGroupBox(tabSettings);
        groupBoxSerial->setObjectName(QString::fromUtf8("groupBoxSerial"));
        gridLayout_3 = new QGridLayout(groupBoxSerial);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        btnConnect = new QPushButton(groupBoxSerial);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));

        gridLayout_3->addWidget(btnConnect, 4, 0, 1, 1);

        boxPortList = new QComboBox(groupBoxSerial);
        boxPortList->setObjectName(QString::fromUtf8("boxPortList"));

        gridLayout_3->addWidget(boxPortList, 0, 0, 1, 2);

        btnDisconnect = new QPushButton(groupBoxSerial);
        btnDisconnect->setObjectName(QString::fromUtf8("btnDisconnect"));

        gridLayout_3->addWidget(btnDisconnect, 4, 1, 1, 1);


        gridLayout_10->addWidget(groupBoxSerial, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_2, 2, 0, 1, 1);

        groupBoxSettings = new QGroupBox(tabSettings);
        groupBoxSettings->setObjectName(QString::fromUtf8("groupBoxSettings"));
        gridLayout = new QGridLayout(groupBoxSettings);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnApplyGain = new QPushButton(groupBoxSettings);
        btnApplyGain->setObjectName(QString::fromUtf8("btnApplyGain"));

        gridLayout->addWidget(btnApplyGain, 1, 3, 1, 1);

        inputOffset = new QDoubleSpinBox(groupBoxSettings);
        inputOffset->setObjectName(QString::fromUtf8("inputOffset"));
        inputOffset->setMinimum(-4095.000000000000000);
        inputOffset->setMaximum(4095.000000000000000);
        inputOffset->setSingleStep(1.000000000000000);
        inputOffset->setValue(0.000000000000000);

        gridLayout->addWidget(inputOffset, 2, 2, 1, 1);

        currentFrameRate = new QLabel(groupBoxSettings);
        currentFrameRate->setObjectName(QString::fromUtf8("currentFrameRate"));
        currentFrameRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentFrameRate, 7, 1, 1, 1);

        labelBinning = new QLabel(groupBoxSettings);
        labelBinning->setObjectName(QString::fromUtf8("labelBinning"));

        gridLayout->addWidget(labelBinning, 3, 0, 1, 1);

        currentVBin = new QLabel(groupBoxSettings);
        currentVBin->setObjectName(QString::fromUtf8("currentVBin"));
        currentVBin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentVBin, 5, 1, 1, 1);

        inputHBin = new QComboBox(groupBoxSettings);
        inputHBin->addItem(QString());
        inputHBin->addItem(QString());
        inputHBin->addItem(QString());
        inputHBin->addItem(QString());
        inputHBin->setObjectName(QString::fromUtf8("inputHBin"));
        inputHBin->setMouseTracking(true);

        gridLayout->addWidget(inputHBin, 4, 2, 1, 1);

        currentHBin = new QLabel(groupBoxSettings);
        currentHBin->setObjectName(QString::fromUtf8("currentHBin"));
        currentHBin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentHBin, 4, 1, 1, 1);

        btnApplyOffset = new QPushButton(groupBoxSettings);
        btnApplyOffset->setObjectName(QString::fromUtf8("btnApplyOffset"));

        gridLayout->addWidget(btnApplyOffset, 2, 3, 1, 1);

        labelOffset = new QLabel(groupBoxSettings);
        labelOffset->setObjectName(QString::fromUtf8("labelOffset"));

        gridLayout->addWidget(labelOffset, 2, 0, 1, 1);

        labelBinningV = new QLabel(groupBoxSettings);
        labelBinningV->setObjectName(QString::fromUtf8("labelBinningV"));
        labelBinningV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelBinningV, 5, 0, 1, 1);

        inputGain = new QDoubleSpinBox(groupBoxSettings);
        inputGain->setObjectName(QString::fromUtf8("inputGain"));
        inputGain->setMinimum(1.000000000000000);
        inputGain->setMaximum(10.000000000000000);
        inputGain->setSingleStep(0.100000000000000);

        gridLayout->addWidget(inputGain, 1, 2, 1, 1);

        btnApplyAll = new QPushButton(groupBoxSettings);
        btnApplyAll->setObjectName(QString::fromUtf8("btnApplyAll"));

        gridLayout->addWidget(btnApplyAll, 8, 2, 1, 1);

        btnApplyBin = new QPushButton(groupBoxSettings);
        btnApplyBin->setObjectName(QString::fromUtf8("btnApplyBin"));

        gridLayout->addWidget(btnApplyBin, 3, 3, 1, 1);

        btnReset = new QPushButton(groupBoxSettings);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));

        gridLayout->addWidget(btnReset, 8, 1, 1, 1);

        inputFrameRate = new QDoubleSpinBox(groupBoxSettings);
        inputFrameRate->setObjectName(QString::fromUtf8("inputFrameRate"));
        inputFrameRate->setMinimum(1.000000000000000);
        inputFrameRate->setMaximum(200000.000000000000000);
        inputFrameRate->setValue(30.000000000000000);

        gridLayout->addWidget(inputFrameRate, 7, 2, 1, 1);

        inputValue = new QLabel(groupBoxSettings);
        inputValue->setObjectName(QString::fromUtf8("inputValue"));
        inputValue->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(inputValue, 0, 2, 1, 1);

        labelBinningH = new QLabel(groupBoxSettings);
        labelBinningH->setObjectName(QString::fromUtf8("labelBinningH"));
        labelBinningH->setLayoutDirection(Qt::LeftToRight);
        labelBinningH->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelBinningH, 4, 0, 1, 1);

        labelFrameRate = new QLabel(groupBoxSettings);
        labelFrameRate->setObjectName(QString::fromUtf8("labelFrameRate"));

        gridLayout->addWidget(labelFrameRate, 7, 0, 1, 1);

        btnApplyFrameRate = new QPushButton(groupBoxSettings);
        btnApplyFrameRate->setObjectName(QString::fromUtf8("btnApplyFrameRate"));

        gridLayout->addWidget(btnApplyFrameRate, 7, 3, 1, 1);

        inputIntegTime = new QSpinBox(groupBoxSettings);
        inputIntegTime->setObjectName(QString::fromUtf8("inputIntegTime"));
        inputIntegTime->setMinimum(5);
        inputIntegTime->setMaximum(1000000);
        inputIntegTime->setValue(31221);
        inputIntegTime->setDisplayIntegerBase(10);

        gridLayout->addWidget(inputIntegTime, 6, 2, 1, 1);

        labelIntegTime = new QLabel(groupBoxSettings);
        labelIntegTime->setObjectName(QString::fromUtf8("labelIntegTime"));

        gridLayout->addWidget(labelIntegTime, 6, 0, 1, 1);

        currentOffset = new QLabel(groupBoxSettings);
        currentOffset->setObjectName(QString::fromUtf8("currentOffset"));
        currentOffset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentOffset, 2, 1, 1, 1);

        currentIntegTime = new QLabel(groupBoxSettings);
        currentIntegTime->setObjectName(QString::fromUtf8("currentIntegTime"));
        currentIntegTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentIntegTime, 6, 1, 1, 1);

        currentValue = new QLabel(groupBoxSettings);
        currentValue->setObjectName(QString::fromUtf8("currentValue"));
        currentValue->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(currentValue, 0, 1, 1, 1);

        labelGain = new QLabel(groupBoxSettings);
        labelGain->setObjectName(QString::fromUtf8("labelGain"));

        gridLayout->addWidget(labelGain, 1, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 4, 1, 1);

        btnApplyIntegTime = new QPushButton(groupBoxSettings);
        btnApplyIntegTime->setObjectName(QString::fromUtf8("btnApplyIntegTime"));

        gridLayout->addWidget(btnApplyIntegTime, 6, 3, 1, 1);

        inputVBin = new QComboBox(groupBoxSettings);
        inputVBin->addItem(QString());
        inputVBin->addItem(QString());
        inputVBin->addItem(QString());
        inputVBin->addItem(QString());
        inputVBin->setObjectName(QString::fromUtf8("inputVBin"));

        gridLayout->addWidget(inputVBin, 5, 2, 1, 1);

        currentGain = new QLabel(groupBoxSettings);
        currentGain->setObjectName(QString::fromUtf8("currentGain"));
        currentGain->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentGain, 1, 1, 1, 1);


        gridLayout_10->addWidget(groupBoxSettings, 1, 0, 1, 1);

        tabWidget->addTab(tabSettings, QString());
        tabSave = new QWidget();
        tabSave->setObjectName(QString::fromUtf8("tabSave"));
        gridLayout_11 = new QGridLayout(tabSave);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        groupBoxSqn = new QGroupBox(tabSave);
        groupBoxSqn->setObjectName(QString::fromUtf8("groupBoxSqn"));
        gridLayout_13 = new QGridLayout(groupBoxSqn);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        labelNIter = new QLabel(groupBoxSqn);
        labelNIter->setObjectName(QString::fromUtf8("labelNIter"));

        gridLayout_13->addWidget(labelNIter, 1, 0, 1, 1);

        chkSequence = new QCheckBox(groupBoxSqn);
        chkSequence->setObjectName(QString::fromUtf8("chkSequence"));

        gridLayout_13->addWidget(chkSequence, 0, 0, 1, 1);

        labelTIntv = new QLabel(groupBoxSqn);
        labelTIntv->setObjectName(QString::fromUtf8("labelTIntv"));

        gridLayout_13->addWidget(labelTIntv, 2, 0, 1, 1);

        inputNIter = new QSpinBox(groupBoxSqn);
        inputNIter->setObjectName(QString::fromUtf8("inputNIter"));
        inputNIter->setMinimum(1);
        inputNIter->setMaximum(1000000);

        gridLayout_13->addWidget(inputNIter, 1, 1, 1, 1);

        inputTIntv = new QSpinBox(groupBoxSqn);
        inputTIntv->setObjectName(QString::fromUtf8("inputTIntv"));
        inputTIntv->setMinimum(100);
        inputTIntv->setMaximum(1000000);

        gridLayout_13->addWidget(inputTIntv, 2, 1, 1, 1);


        gridLayout_11->addWidget(groupBoxSqn, 2, 0, 1, 1);

        gridLayout_14 = new QGridLayout();
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        btnCancel = new QPushButton(tabSave);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        gridLayout_14->addWidget(btnCancel, 0, 2, 1, 1);

        btnStart = new QPushButton(tabSave);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        gridLayout_14->addWidget(btnStart, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_14->addItem(horizontalSpacer_6, 0, 0, 1, 1);


        gridLayout_11->addLayout(gridLayout_14, 3, 0, 1, 1);

        groupBoxSave = new QGroupBox(tabSave);
        groupBoxSave->setObjectName(QString::fromUtf8("groupBoxSave"));
        gridLayout_9 = new QGridLayout(groupBoxSave);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_5, 0, 4, 1, 1);

        labelDirectory = new QLabel(groupBoxSave);
        labelDirectory->setObjectName(QString::fromUtf8("labelDirectory"));

        gridLayout_9->addWidget(labelDirectory, 0, 0, 1, 1);

        btnChooseDir = new QPushButton(groupBoxSave);
        btnChooseDir->setObjectName(QString::fromUtf8("btnChooseDir"));

        gridLayout_9->addWidget(btnChooseDir, 0, 3, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        inputNFrame = new QSpinBox(groupBoxSave);
        inputNFrame->setObjectName(QString::fromUtf8("inputNFrame"));
        inputNFrame->setMinimum(1);

        gridLayout_7->addWidget(inputNFrame, 2, 1, 1, 1);

        inputTimeIntv = new QSpinBox(groupBoxSave);
        inputTimeIntv->setObjectName(QString::fromUtf8("inputTimeIntv"));
        inputTimeIntv->setMinimum(1000);
        inputTimeIntv->setMaximum(100000);
        inputTimeIntv->setSingleStep(100);

        gridLayout_7->addWidget(inputTimeIntv, 1, 1, 1, 1);

        labelTimeIntv = new QLabel(groupBoxSave);
        labelTimeIntv->setObjectName(QString::fromUtf8("labelTimeIntv"));

        gridLayout_7->addWidget(labelTimeIntv, 1, 0, 1, 1);

        inputNFile = new QSpinBox(groupBoxSave);
        inputNFile->setObjectName(QString::fromUtf8("inputNFile"));
        inputNFile->setMinimum(1);

        gridLayout_7->addWidget(inputNFile, 5, 1, 1, 1);

        labelNFrame = new QLabel(groupBoxSave);
        labelNFrame->setObjectName(QString::fromUtf8("labelNFrame"));

        gridLayout_7->addWidget(labelNFrame, 2, 0, 1, 1);

        labelFramePerFile = new QLabel(groupBoxSave);
        labelFramePerFile->setObjectName(QString::fromUtf8("labelFramePerFile"));

        gridLayout_7->addWidget(labelFramePerFile, 4, 0, 1, 1);

        inputFramePerFile = new QSpinBox(groupBoxSave);
        inputFramePerFile->setObjectName(QString::fromUtf8("inputFramePerFile"));
        inputFramePerFile->setMinimum(1);

        gridLayout_7->addWidget(inputFramePerFile, 4, 1, 1, 1);

        labelNFile = new QLabel(groupBoxSave);
        labelNFile->setObjectName(QString::fromUtf8("labelNFile"));

        gridLayout_7->addWidget(labelNFile, 5, 0, 1, 1);

        btnBurst = new QRadioButton(groupBoxSave);
        btnBurst->setObjectName(QString::fromUtf8("btnBurst"));

        gridLayout_7->addWidget(btnBurst, 3, 0, 1, 2);

        btnSingleFrame = new QRadioButton(groupBoxSave);
        btnSingleFrame->setObjectName(QString::fromUtf8("btnSingleFrame"));

        gridLayout_7->addWidget(btnSingleFrame, 0, 0, 1, 2);


        gridLayout_9->addLayout(gridLayout_7, 1, 0, 1, 5);

        btnSave = new QPushButton(groupBoxSave);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        gridLayout_9->addWidget(btnSave, 2, 0, 1, 2);

        inputDir = new QLineEdit(groupBoxSave);
        inputDir->setObjectName(QString::fromUtf8("inputDir"));

        gridLayout_9->addWidget(inputDir, 0, 2, 1, 1);


        gridLayout_11->addWidget(groupBoxSave, 0, 0, 1, 1);

        groupBoxMode = new QGroupBox(tabSave);
        groupBoxMode->setObjectName(QString::fromUtf8("groupBoxMode"));
        gridLayout_12 = new QGridLayout(groupBoxMode);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        inputNFrm = new QSpinBox(groupBoxMode);
        inputNFrm->setObjectName(QString::fromUtf8("inputNFrm"));
        inputNFrm->setMinimum(1);
        inputNFrm->setMaximum(1000000);

        gridLayout_12->addWidget(inputNFrm, 2, 1, 1, 1);

        labelSingleMode = new QRadioButton(groupBoxMode);
        labelSingleMode->setObjectName(QString::fromUtf8("labelSingleMode"));

        gridLayout_12->addWidget(labelSingleMode, 0, 0, 1, 1);

        labelNFrmMode = new QRadioButton(groupBoxMode);
        labelNFrmMode->setObjectName(QString::fromUtf8("labelNFrmMode"));

        gridLayout_12->addWidget(labelNFrmMode, 2, 0, 1, 1);

        labelUnlimMode = new QRadioButton(groupBoxMode);
        labelUnlimMode->setObjectName(QString::fromUtf8("labelUnlimMode"));

        gridLayout_12->addWidget(labelUnlimMode, 1, 0, 1, 1);


        gridLayout_11->addWidget(groupBoxMode, 1, 0, 1, 1);

        tabWidget->addTab(tabSave, QString());

        gridLayout_5->addWidget(tabWidget, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_5, 0, 3, 4, 1);

        stdevLabel = new QLabel(centralwidget);
        stdevLabel->setObjectName(QString::fromUtf8("stdevLabel"));

        gridLayout_2->addWidget(stdevLabel, 6, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        btnGrab = new QPushButton(centralwidget);
        btnGrab->setObjectName(QString::fromUtf8("btnGrab"));

        gridLayout_4->addWidget(btnGrab, 0, 1, 1, 1);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));

        gridLayout_4->addWidget(btnStop, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout_4, 5, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 665, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        imageLabel->setText(QCoreApplication::translate("MainWindow", " No image to show. ", nullptr));
        groupBoxSerial->setTitle(QCoreApplication::translate("MainWindow", "Serial Configuration", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        btnDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        groupBoxSettings->setTitle(QCoreApplication::translate("MainWindow", "Camera Settings", nullptr));
        btnApplyGain->setText(QCoreApplication::translate("MainWindow", "Apply Gain", nullptr));
        currentFrameRate->setText(QCoreApplication::translate("MainWindow", "30.00", nullptr));
        labelBinning->setText(QCoreApplication::translate("MainWindow", "Binning", nullptr));
        currentVBin->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        inputHBin->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        inputHBin->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        inputHBin->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));
        inputHBin->setItemText(3, QCoreApplication::translate("MainWindow", "8", nullptr));

        currentHBin->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btnApplyOffset->setText(QCoreApplication::translate("MainWindow", "Apply Offset", nullptr));
        labelOffset->setText(QCoreApplication::translate("MainWindow", "Offset", nullptr));
        labelBinningV->setText(QCoreApplication::translate("MainWindow", "Vertical:", nullptr));
        btnApplyAll->setText(QCoreApplication::translate("MainWindow", "Apply All", nullptr));
        btnApplyBin->setText(QCoreApplication::translate("MainWindow", "Apply Binning", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        inputValue->setText(QCoreApplication::translate("MainWindow", "Set as", nullptr));
        labelBinningH->setText(QCoreApplication::translate("MainWindow", "Horizontal:", nullptr));
        labelFrameRate->setText(QCoreApplication::translate("MainWindow", "Frame Rate (FPS)", nullptr));
        btnApplyFrameRate->setText(QCoreApplication::translate("MainWindow", "Apply Frame Rate", nullptr));
        labelIntegTime->setText(QCoreApplication::translate("MainWindow", "Integration Time (microsec)", nullptr));
        currentOffset->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        currentIntegTime->setText(QCoreApplication::translate("MainWindow", "31221", nullptr));
        currentValue->setText(QCoreApplication::translate("MainWindow", "Current Value", nullptr));
        labelGain->setText(QCoreApplication::translate("MainWindow", "Gain", nullptr));
        btnApplyIntegTime->setText(QCoreApplication::translate("MainWindow", "Aplply Integration Time", nullptr));
        inputVBin->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        inputVBin->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        inputVBin->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));
        inputVBin->setItemText(3, QCoreApplication::translate("MainWindow", "8", nullptr));

        currentGain->setText(QCoreApplication::translate("MainWindow", "1.00", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSettings), QCoreApplication::translate("MainWindow", "Camera Settings", nullptr));
        groupBoxSqn->setTitle(QCoreApplication::translate("MainWindow", "Capture Sequence", nullptr));
        labelNIter->setText(QCoreApplication::translate("MainWindow", "Number of iteration", nullptr));
        chkSequence->setText(QCoreApplication::translate("MainWindow", "Perfrom a sequence of capture", nullptr));
        labelTIntv->setText(QCoreApplication::translate("MainWindow", "Time interval between captures (msec)", nullptr));
        btnCancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        groupBoxSave->setTitle(QCoreApplication::translate("MainWindow", "Save image", nullptr));
        labelDirectory->setText(QCoreApplication::translate("MainWindow", "Directory", nullptr));
        btnChooseDir->setText(QCoreApplication::translate("MainWindow", "Choose...", nullptr));
        labelTimeIntv->setText(QCoreApplication::translate("MainWindow", "Time interval (msec):", nullptr));
        labelNFrame->setText(QCoreApplication::translate("MainWindow", "# of frames:", nullptr));
        labelFramePerFile->setText(QCoreApplication::translate("MainWindow", "# of frames per file: ", nullptr));
        labelNFile->setText(QCoreApplication::translate("MainWindow", "# of files:", nullptr));
        btnBurst->setText(QCoreApplication::translate("MainWindow", "Burst Mode", nullptr));
        btnSingleFrame->setText(QCoreApplication::translate("MainWindow", "Single Frame Mode", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        groupBoxMode->setTitle(QCoreApplication::translate("MainWindow", "Capture Mode", nullptr));
        labelSingleMode->setText(QCoreApplication::translate("MainWindow", "Single Frame", nullptr));
        labelNFrmMode->setText(QCoreApplication::translate("MainWindow", "Number of Frames", nullptr));
        labelUnlimMode->setText(QCoreApplication::translate("MainWindow", "Unlimited", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSave), QCoreApplication::translate("MainWindow", "Capture", nullptr));
        stdevLabel->setText(QCoreApplication::translate("MainWindow", "Std Dev: N/A", nullptr));
        btnGrab->setText(QCoreApplication::translate("MainWindow", "Grab", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
