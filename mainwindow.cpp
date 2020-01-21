#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , port(new CameraPort)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(this);

    // connect SIGNALS with SLOTS
    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(serialConnect()));
    connect(ui->btnDisconnect, SIGNAL(clicked()), this, SLOT(serialDisconnect()));
    connect(ui->btnApp, SIGNAL(clicked()), this, SLOT(applySettings()));
    connect(ui->btnReset, SIGNAL(clicked()), this, SLOT(resetSettings()));
    connect(ui->btnGrab, SIGNAL(clicked()), this, SLOT(stopGrab()));
    connect(ui->btnStop, SIGNAL(clicked()), this, SLOT(stopGrab()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(quit()));

    // Fill Port List
    fillPortsInfo();

    // Wether camera is connected (== port is opend) or not
    cameraConnected = false;
    ui->btnConnect->setEnabled(!cameraConnected);       // Button is enabled.
    ui->btnDisconnect->setEnabled(cameraConnected);     // Button is disabled.

}

MainWindow::~MainWindow()
{
    delete port;
    delete ui;
}

void MainWindow::serialConnect()
{
    QString portName = ui->boxPortList->currentText();
    port->openCameraPort(portName);

    cameraConnected = true;
    ui->btnConnect->setEnabled(!cameraConnected);       // button disabled
    ui->btnDisconnect->setEnabled(cameraConnected);     // button enabled
    ui->boxPortList->setEnabled(!cameraConnected);      // port selection disabled
}

void MainWindow::serialDisconnect()
{
    port->closeCameraPort();

    cameraConnected = false;
    ui->btnConnect->setEnabled(!cameraConnected);       // button enabled.
    ui->btnDisconnect->setEnabled(cameraConnected);    // button disabled
    ui->boxPortList->setEnabled(!cameraConnected);      // port selection ensabled
}

void MainWindow::applySettings()
{
    float gain = ui->inputGain->text().toFloat();           // Gain
    float offset = ui->inputOffset->text().toFloat();       // Offset
    int hbin = ui->boxHBin->currentText().toInt();          // Horizontal Bin
    int vbin = ui->boxVBin->currentText().toInt();          // Vertial    Bin
    int microsec = ui->inputIntegTime->text().toInt();      // Integration Time
    float frameRate = ui->inputFrameRate->text().toFloat(); // Frame Rate

    QMessageBox errorBox;                                   // Error Message Box
    errorBox.setFixedSize(500, 200);

    // Gain Range Violation
    if (! port->isGainOK(gain))
    {
        errorBox.critical(nullptr, "Error", QString("Gain must be between %1 and %2.").arg(MIN_GAIN, MAX_GAIN));
        errorBox.exec();
        updateSettings();
        return;
    }

    // Offset Range Violation
    if (! port->isOffsetOK(offset))
    {
        errorBox.critical(nullptr, "Error", QString("Offset must be between %1 and %2.").arg(MIN_OFFSET, MAX_OFFSET));
        errorBox.exec();
        updateSettings();
        return;
    }

    // Inetgration Time Condition Violation
    if (! port->isIntegTimeOK(microsec))
    {
        errorBox.critical(nullptr, "Error", "Inetgration Time Condition Violation");
        errorBox.exec();
        updateSettings();
        return;
    }

    // Frame Rate Condition Violation
    if (! port->isFrameRateOK(frameRate))
    {
        errorBox.critical(nullptr, "Error", "Frame Rate Condition Violation");
        errorBox.exec();
        updateSettings();
        return;
    }

    port->adjustGain(gain);                 // 1 <= gain <= 10
    port->adjustOffset(offset);             // -4095 <= gain <= 4095
    port->adjustBinning(hbin, vbin);        // hbin: horizontal bin, vbin: vertical bin
    port->adjustIntegTime(microsec);        // adjust integration time in microseconds
    port->adjustFrameRate(frameRate);       // adjust frame rate in fps
}

void MainWindow::resetSettings()
{
    port->resetCamera();
    updateSettings();
}

void MainWindow::startGrab()
{

}

void MainWindow::stopGrab()
{

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
