#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , port(new CameraPort)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("CCD Program");
    img = image(ui->imageLabel);

    // connect SIGNALS with SLOTS
    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(serialConnect()));
    connect(ui->btnDisconnect, SIGNAL(clicked()), this, SLOT(serialDisconnect()));

    connect(ui->btnApplyGain, SIGNAL(clicked()), this, SLOT(applyGain()));
    connect(ui->btnApplyOffset, SIGNAL(clicked()), this, SLOT(applyOffset()));
    connect(ui->btnApplyBin, SIGNAL(clicked()), this, SLOT(applyBin()));
    connect(ui->btnApplyIntegTime, SIGNAL(clicked()), this, SLOT(applyIntegTime()));
    connect(ui->btnApplyFrameRate, SIGNAL(clicked()), this, SLOT(applyFrameRate()));
    connect(ui->btnApplyAll, SIGNAL(clicked()), this, SLOT(applyAll()));
    connect(ui->btnReset, SIGNAL(clicked()), this, SLOT(resetSettings()));
    connect(ui->btnGrab, SIGNAL(clicked()), this, SLOT(startGrab()));
    connect(ui->btnStop, SIGNAL(clicked()), this, SLOT(stopGrab()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnChooseDir, SIGNAL(clicked()), this, SLOT(setDir()));
    connect(ui->inputDir, SIGNAL(editingFinished()), this, SLOT(getInputDir()));

    connect(ui->btnSingleFrame, SIGNAL(clicked()), this, SLOT(modeSingleFrame()));
    connect(ui->btnBurst, SIGNAL(clicked()), this, SLOT(modeBurst()));

    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(saveImage()));

    fillPortsInfo();

    // Wether camera is connected (== port is opend) or not
    isConnected = false;
    ui->btnConnect->setEnabled(!isConnected);       // Button is enabled.
    ui->btnDisconnect->setEnabled(isConnected);     // Button is disabled.
    ui->btnApplyGain->setEnabled(isConnected);
    ui->btnApplyOffset->setEnabled(isConnected);
    ui->btnApplyBin->setEnabled(isConnected);
    ui->btnApplyIntegTime->setEnabled(isConnected);
    ui->btnApplyFrameRate->setEnabled(isConnected);
    ui->btnApplyAll->setEnabled(isConnected);       // Button is disabled.
    ui->btnReset->setEnabled(isConnected);          // Button is disabled.

    isGrabbing = false;
    ui->btnGrab->setEnabled(!isGrabbing);           // Button is enabled.
    ui->btnStop->setEnabled( isGrabbing);           // Button is disabled.

    modeSingleFrame();
    ui->btnSave->setEnabled(isGrabbing);

    dir = QDir::currentPath();                      // Default path is the working directory
    ui->inputDir->setText(dir);                     // show the directory address

}

MainWindow::~MainWindow()
{
    img.~image();
    delete port;
    delete ui;
}

void MainWindow::fillPortsInfo()
{
    ui->boxPortList->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    QString blankString = "";
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
            << (!description.isEmpty() ? description : blankString)
            << (!manufacturer.isEmpty() ? manufacturer : blankString)
            << (!serialNumber.isEmpty() ? serialNumber : blankString)
            << info.systemLocation()
            << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
            << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        ui->boxPortList->addItem(list.first(), list);
    }

    ui->boxPortList->addItem(tr("Custom"));
}


void MainWindow::serialConnect()
{
    QString portName = ui->boxPortList->currentText();
    port->openCameraPort(portName);
    port->getCameraType();
    if(port->cameraType == 0x41)
    {
        ui->groupBoxSettings->setTitle("Camera Settings - 1M30P");
    }

    else
    {
        ui->groupBoxSettings->setTitle("Camera Settings - Unknown Camera");
    }

    isConnected = true;
    ui->btnConnect->setEnabled(!isConnected);       // button disabled
    ui->btnDisconnect->setEnabled(isConnected);     // button enabled
    ui->boxPortList->setEnabled(!isConnected);      // port selection disabled

    ui->btnGrab->setEnabled(!isGrabbing);
    ui->btnStop->setEnabled( isGrabbing);
    ui->btnApplyGain->setEnabled(isConnected);
    ui->btnApplyOffset->setEnabled(isConnected);
    ui->btnApplyBin->setEnabled(isConnected);
    ui->btnApplyIntegTime->setEnabled(isConnected);
    ui->btnApplyFrameRate->setEnabled(isConnected);
    ui->btnApplyAll->setEnabled(isConnected);
    ui->btnReset->setEnabled(isConnected);
}

void MainWindow::serialDisconnect()
{
    port->closeCameraPort();

    isConnected = false;
    ui->btnConnect->setEnabled(!isConnected);       // button enabled.
    ui->btnDisconnect->setEnabled(isConnected);    // button disabled
    ui->boxPortList->setEnabled(!isConnected);      // port selection ensabled

    ui->btnGrab->setEnabled(!isGrabbing && isConnected);
    ui->btnStop->setEnabled( isGrabbing && isConnected);
    ui->btnApplyGain->setEnabled(isConnected);
    ui->btnApplyOffset->setEnabled(isConnected);
    ui->btnApplyBin->setEnabled(isConnected);
    ui->btnApplyIntegTime->setEnabled(isConnected);
    ui->btnApplyFrameRate->setEnabled(isConnected);
    ui->btnApplyAll->setEnabled(isConnected);
    ui->btnReset->setEnabled(isConnected);
}

void MainWindow::applyGain()
{
    float gain = ui->inputGain->text().toFloat();
    if (! port->isGainOK(gain))     // Gain Range Violation
    {
        int error = -1;
        showErrorMsg(error);
        updateSettings();
        return;
    }
    port->adjustGain(gain);

    updateSettings();
}

void MainWindow::applyOffset()
{
    float offset = ui->inputOffset->text().toFloat();
    if (! port->isOffsetOK(offset)) // Offset Range Violation
    {
        int error = -2;
        showErrorMsg(error);
        updateSettings();
        return;
    }
    port->adjustOffset(offset);

    updateSettings();
}

void MainWindow::applyBin()
{
    int hbin = ui->inputHBin->currentText().toInt();          // Horizontal Bin
    int vbin = ui->inputVBin->currentText().toInt();          // Vertial    Bin

    if (isGrabbing) stopGrab();

    port->adjustBinning(hbin, vbin);
    updateSettings();
    startGrab();
}

void MainWindow::applyIntegTime()
{
    int microsec = ui->inputIntegTime->text().toInt();      // Integration Time in microseconds
    if (! port->isIntegTimeOK(microsec))    // Inetgration Time Condition Violation
    {
        int error = -3;
        showErrorMsg(error);
        updateSettings();
        return;
    }
    port->adjustIntegTime(microsec);        // adjust integration time in microseconds

    updateSettings();
}

void MainWindow::applyFrameRate()
{
    float frameRate = ui->inputFrameRate->text().toFloat(); // Frame Rate
    if (! port->isFrameRateOK(frameRate))   // Frame Rate Condition Violation
    {
        int error = -4;
        showErrorMsg(error);
        updateSettings();
        return;
    }
    port->adjustFrameRate(frameRate);

    updateSettings();
}

void MainWindow::applyAll()
{
    applyGain();
    applyOffset();
    applyBin();
    applyIntegTime();
    applyFrameRate();
}

void MainWindow::resetSettings()
{
    port->resetCamera();
    updateSettings();
}

void MainWindow::updateSettings()
{
    float gain = port->getGain();
    float offset = port->getOffset();
    int hBin = port->getHBin();
    int vBin = port->getVBin();
    int msec = port->getIntegTime();
    float frameRate = port->getFrameRate();

    ui->currentGain->setText(QString::number(gain));
    ui->currentOffset->setText(QString::number(offset));
    ui->currentHBin->setText(QString::number(hBin));
    ui->currentVBin->setText(QString::number(vBin));
    ui->currentIntegTime->setText(QString::number(msec));
    ui->currentFrameRate->setText(QString::number(frameRate));
}

void MainWindow::startGrab()
{
    int hbin = ui->currentHBin->text().toInt();
    int vbin = ui->currentVBin->text().toInt();
    img.startGrab(hbin, vbin);
    isGrabbing = true;
    ui->btnGrab->setEnabled(!isGrabbing);
    ui->btnStop->setEnabled( isGrabbing);
    ui->btnSave->setEnabled(isGrabbing);
}

void MainWindow::stopGrab()
{
    img.stopGrab();
    isGrabbing = false;
    ui->btnGrab->setEnabled(!isGrabbing);
    ui->btnStop->setEnabled( isGrabbing);
    ui->btnSave->setEnabled(isGrabbing);
}

void MainWindow::setDir()
{
//-- need to change so that user input into inputDir is accecpted 
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);     // Choose directory to save image
    ui->inputDir->setText(dir);     // show directory
}

void MainWindow::getInputDir()
{
    dir = ui->inputDir->text();
}

void MainWindow::modeSingleFrame()
{
    isSingleFrame = true;
    isBurst = false;

    ui->inputTimeIntv->setEnabled(isSingleFrame);
    ui->inputNFrame->setEnabled(isSingleFrame);
    ui->inputFramePerFile->setEnabled(isBurst);
    ui->inputNFile->setEnabled(isBurst);
}

void MainWindow::modeBurst()
{
    isSingleFrame = false;
    isBurst = true;

    ui->inputTimeIntv->setEnabled(isSingleFrame);
    ui->inputNFrame->setEnabled(isSingleFrame);
    ui->inputFramePerFile->setEnabled(isBurst);
    ui->inputNFile->setEnabled(isBurst);
}

void MainWindow::saveImage()
{
    int nFrame = ui->inputNFrame->value();      // number of frames to be saved
    float gain = port->getGain();
    int   hBin = port->getHBin();
    int   vBin = port->getVBin();
    float frameRate = port->getFrameRate();
    float integTime = port->getIntegTime();

    if (isSingleFrame)
    {
        int timeIntv = ui->inputTimeIntv->value();
        int nFrame = ui->inputNFrame->value();
        img.saveSingleFrame(dir, timeIntv, nFrame, gain, hBin, vBin, frameRate, integTime);
    }

    else if (isBurst)
    {
        int FramePerFile = ui->inputFramePerFile->value();
        int nFile = ui->inputNFile->value();
        img.saveBurst(dir, FramePerFile, nFile, gain, hBin, vBin, frameRate, integTime);
    }

    img.save(dir, nFrame, gain, hBin, vBin, frameRate, integTime);                      // save image to directory
}

void MainWindow::showErrorMsg(int error)
{
    QMessageBox errorBox;                                   // Error Message Box
    errorBox.setFixedSize(500, 200);

    QString boxTitle = "Error";     // title of the message box
    QString errorContent;           // content of the error message

    switch (error)
    {
    case -1:
        errorContent = QString("Gain must be between %1 and %2.").arg(MIN_GAIN, MAX_GAIN);
        break;

    case -2:
        errorContent = QString("Offset must be between %1 and %2.").arg(MIN_OFFSET, MAX_OFFSET);
        break;

    case -3:
        errorContent = QString("Inetgration Time Condition Violation");
        break;

    case -4:
        errorContent = QString("Frame Rate Condition Violation");
        break;

    default:
        errorContent = QString("Unknown Error");
    }

    errorBox.critical(nullptr, boxTitle, errorContent);
}
