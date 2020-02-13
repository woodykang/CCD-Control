#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , imgWin(new imageWindow)
    , port(new CameraPort)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setCentralWidget(this);

    // connect SIGNALS with SLOTS
    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(serialConnect()));
    connect(ui->btnDisconnect, SIGNAL(clicked()), this, SLOT(serialDisconnect()));
    connect(ui->btnApp, SIGNAL(clicked()), this, SLOT(applySettings()));
    connect(ui->btnReset, SIGNAL(clicked()), this, SLOT(resetSettings()));
    connect(ui->btnGrab, SIGNAL(clicked()), this, SLOT(startGrab()));
    connect(ui->btnStop, SIGNAL(clicked()), this, SLOT(stopGrab()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->boxPortList, SIGNAL(currentIndexChanged()), this, SLOT(showPortInfo()));
    connect(imgWin, SIGNAL(imageWindow::windowClosed()), this, SLOT(imageWindowClosed()));

    // Fill Port List
    fillPortsInfo();

    // Wether camera is connected (== port is opend) or not
    isConnected = false;
    ui->btnConnect->setEnabled(!isConnected);       // Button is enabled.
    ui->btnDisconnect->setEnabled(isConnected);     // Button is disabled.

    isGrabbing = false;
    ui->btnGrab->setEnabled(!isGrabbing && isConnected);
    ui->btnStop->setEnabled( isGrabbing && isConnected);

    isImageWindowOn = false;

}

MainWindow::~MainWindow()
{
    imgWin->close();
    delete imgWin;
    delete port;
    delete ui;
}

void MainWindow::serialConnect()
{
    QString portName = ui->boxPortList->currentText();
    port->openCameraPort(portName);

    isConnected = true;
    ui->btnConnect->setEnabled(!isConnected);       // button disabled
    ui->btnDisconnect->setEnabled(isConnected);     // button enabled
    ui->boxPortList->setEnabled(!isConnected);      // port selection disabled

    ui->btnGrab->setEnabled(!isGrabbing && isConnected);
    ui->btnStop->setEnabled( isGrabbing && isConnected);
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
}

void MainWindow::applySettings()
{
    float gain = ui->inputGain->text().toFloat();           // Gain
    float offset = ui->inputOffset->text().toFloat();       // Offset
    int hbin = ui->boxHBin->currentText().toInt();          // Horizontal Bin
    int vbin = ui->boxVBin->currentText().toInt();          // Vertial    Bin
    int microsec = ui->inputIntegTime->text().toInt();      // Integration Time
    float frameRate = ui->inputFrameRate->text().toFloat(); // Frame Rate

    // adjust gain
    if (! port->isGainOK(gain))     // Gain Range Violation
    {
        int error = -1;
        showErrorMsg(error);
        updateSettings();
        return;
    }
    port->adjustGain(gain);                 // 1 <= gain <= 10

    // adjust offset
    if (! port->isOffsetOK(offset)) // Offset Range Violation
    {
        int error = -2;
        showErrorMsg(error);
        updateSettings();
        return;
    }
    port->adjustOffset(offset);             // -4095 <= gain <= 4095

    // adjust binning
    port->adjustBinning(hbin, vbin);        // hbin: horizontal bin, vbin: vertical bin


    // adjust integration time in microseconds
    if (! port->isIntegTimeOK(microsec))    // Inetgration Time Condition Violation
    {
        int error = -3;
        showErrorMsg(error);
        updateSettings();
        return;
    }
    port->adjustIntegTime(microsec);        // adjust integration time in microseconds


    // adjust frame rate
    if (! port->isFrameRateOK(frameRate))   // Frame Rate Condition Violation
    {
        int error = -4;
        showErrorMsg(error);
        updateSettings();
        return;
    }
    port->adjustFrameRate(frameRate);       // adjust frame rate in fps
    
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

    ui->inputGain->setValue(gain);
    ui->inputOffset->setValue(offset);
    ui->boxHBin->setCurrentText(QString(hBin));
    ui->boxVBin->setCurrentText(QString(vBin));
    ui->inputIntegTime->setValue(msec);
    ui->inputFrameRate->setValue(frameRate);
}

void MainWindow::startGrab()
{
    if (!isImageWindowOn)   imgWin->show();
    isImageWindowOn = true;

    imgWin->startGrab();
    isGrabbing = true;

    ui->btnGrab->setEnabled(!isGrabbing && isConnected);
    ui->btnStop->setEnabled( isGrabbing && isConnected);
}

void MainWindow::stopGrab()
{
    imgWin->stopGrab();
    isGrabbing = false;

    ui->btnGrab->setEnabled(!isGrabbing && isConnected);
    ui->btnStop->setEnabled( isGrabbing && isConnected);
}

void MainWindow::imageWindowClosed()
{
    isImageWindowOn = false;
    if (isGrabbing)  stopGrab();
}

void MainWindow::fillPortsInfo()
{
    ui->boxPortList->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    QString blankString = "";
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
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

void MainWindow::showPortInfo(int idx)
{
    if (idx == -1)
        return;

    QString blankString = "";
    const QStringList list = ui->boxPortList->itemData(idx).toStringList();
    ui->labelPortDescription->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : blankString));
    ui->labelPortManufacturer->setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : blankString));
    ui->labelPortSerialNum->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : blankString));
    ui->labelPortLoc->setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : blankString));
    ui->labelPortVendorID->setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : blankString));
    ui->labelPortProductID->setText(tr("Product Identifier: %1").arg(list.count() > 6 ? list.at(6) : blankString));
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
