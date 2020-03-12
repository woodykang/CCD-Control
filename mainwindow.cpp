#include "mainwindow.h"
#include "ui_mainwindow.h"


// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , port(new CameraPort)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("CCD Program");
    img = image(ui->imageLabel, ui->stdevLabel);

    // connect SIGNALs with SLOTs
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

    connect(ui->btnSingleFrame, SIGNAL(clicked()), this, SLOT(setSingleFrame()));
    connect(ui->btnBurst, SIGNAL(clicked()), this, SLOT(setBurst()));

    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(saveImage()));

    /*Begin of Test*/
    connect(ui->btnModeSingle, SIGNAL(clicked()), this, SLOT(setModeSingle()));
    connect(ui->btnModeUnlim, SIGNAL(clicked()), this, SLOT(setModeUnlim()));
    connect(ui->btnModeNFrm, SIGNAL(clicked()), this, SLOT(setModeNFrm()));
    connect(ui->btnSequnce, SIGNAL(clicked()), this, SLOT(setModeSqn()));
    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(startCapture()));
    connect(ui->btnCancle, SIGNAL(clicked()), this, SLOT(cancelCapture()));

    captureMode = 0;
    isSequence = true;
    /*End of Test*/

    fillPortsInfo();        // load available ports

    isConnected = false;    // true if camera is connected (== port is opend)
    isGrabbing = false;     // true if currently grabbing
    isSingleFrame = true;   // true if save mode is Single Frame
    isBurst = false;        // true if save mode is Burst

    setSingleFrame();       // default mode is Single Frame

    updateButton();         // enable/disable buttons

    dir = QDir::currentPath();                      // Default path is the working directory
    ui->inputDir->setText(dir);                     // show the directory address
}

// Destructor
MainWindow::~MainWindow()
{
    img.~image();
    delete port;
    delete ui;
}

// Loads available ports
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

// Connects to selected serial port as member variable 'port'.
void MainWindow::serialConnect()
{
    QString portName = ui->boxPortList->currentText();  // currently selected port
    port->openCameraPort(portName);                     // open port
    port->getCameraType();                              // get the type of the camera

    if(port->cameraType == 0x41)                        // camera type value of 1M30P
    {
        ui->groupBoxSettings->setTitle("Camera Settings - 1M30P");
    }

    else
    {
        ui->groupBoxSettings->setTitle("Camera Settings - Unknown Camera");
    }

    isConnected = true;     // port is connected
    updateButton();
}

// Disconnects serial port.
void MainWindow::serialDisconnect()
{
    port->closeCameraPort();

    isConnected = false;
    updateButton();
}

// Applies gain from 'inputGain' to 'port'.
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

// Applies offset from 'inputOffset' to 'port'.
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

// Applies binning from 'inputHBin' and 'inputVBin' to 'port'.
void MainWindow::applyBin()
{
    int hbin = ui->inputHBin->currentText().toInt();          // Horizontal Bin
    int vbin = ui->inputVBin->currentText().toInt();          // Vertial    Bin

    if (isGrabbing) stopGrab();

    port->adjustBinning(hbin, vbin);
    updateSettings();
    startGrab();
}

// Applies integration time from 'inputIntegTime' to 'port'.
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

// Applies frame rate from 'inputFrameRate' to 'port'.
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

// Applies all parameters from inputs to 'port'.
void MainWindow::applyAll()
{
    applyGain();
    applyOffset();
    applyBin();
    applyIntegTime();
    applyFrameRate();
}

// Resets camera settings.
void MainWindow::resetSettings()
{
    port->resetCamera();
    updateSettings();
}

// Updates settings parameter shown in the ui.
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

// Starts grabbing.
void MainWindow::startGrab()
{
    int hbin = ui->currentHBin->text().toInt();
    int vbin = ui->currentVBin->text().toInt();

    int error = img.startGrab(hbin, vbin);  // Returns 0 on success, 1 on failure.
    if (!error) isGrabbing = true;
    else        isGrabbing = false;
    
    updateButton();
}

// Stops grabbing.
void MainWindow::stopGrab()
{
    int error = img.stopGrab();             // Returns 0 on success, 1 on failure.
    if (!error) isGrabbing = false;
    else        isGrabbing = true;

    updateButton();
}

// Opens a directory selection dialog
// and sets the directory for saving files as 'dir'.
void MainWindow::setDir()
{
//-- need to change so that user input into inputDir is accecpted 
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);     // Choose directory to save image
    ui->inputDir->setText(dir);     // show directory
}

// Triggered when changes is made to 'inputDir'.
// Sets the directory shown as in the 'inputDir'.
void MainWindow::getInputDir()
{
    dir = ui->inputDir->text();
}

// Triggered when save mode is changed to Single Frame.
void MainWindow::setSingleFrame()
{
    isSingleFrame = true;
    isBurst = false;
    updateButton();
}

// Triggered when save mode is changed to Burst.
void MainWindow::setBurst()
{
    isSingleFrame = false;
    isBurst = true;
    updateButton();
}

// Triggered when 'save' button is clicked.
void MainWindow::saveImage()
{
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
}

// Updates which buttons are enabled and which are disabled.
void MainWindow::updateButton()
{
    ui->btnConnect->setEnabled(  !isConnected);
    ui->btnDisconnect->setEnabled(isConnected);
    ui->boxPortList->setEnabled( !isConnected);

    ui->btnApplyGain->setEnabled(     isConnected);
    ui->btnApplyOffset->setEnabled(   isConnected);
    ui->btnApplyBin->setEnabled(      isConnected);
    ui->btnApplyIntegTime->setEnabled(isConnected);
    ui->btnApplyFrameRate->setEnabled(isConnected);
    ui->btnApplyAll->setEnabled(      isConnected);
    ui->btnReset->setEnabled(         isConnected);

    ui->btnGrab->setEnabled(!isGrabbing);           // Button is enabled.
    ui->btnStop->setEnabled( isGrabbing);           // Button is disabled.

    ui->btnSave->setEnabled(isGrabbing);

    ui->inputTimeIntv->setEnabled(isSingleFrame);
    ui->inputNFrame->setEnabled(isSingleFrame);
    ui->inputFramePerFile->setEnabled(isBurst);
    ui->inputNFile->setEnabled(isBurst);

    /*Begin of Test*/
    ui->inputNFrm->setEnabled(captureMode == 2);
    ui->inputNIter->setEnabled(isSequence);
    ui->inputTIntv->setEnabled(isSequence);
    /*End of Test*/
}

// Pops up an message dialog showing the type of error
// made during changing camera's settings.
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


/*Begin of Test*/
void MainWindow::setModeSingle()
{
    captureMode = 0;
    updateButton();
}


void MainWindow::setModeUnlim()
{
    captureMode = 1;
    updateButton();
}


void MainWindow::setModeNFrm()
{
    captureMode = 2;
    updateButton();
}


void MainWindow::setModeSqn()
{
    isSequence = true;
    updateButton();
}


void MainWindow::startCapture()
{
    // Get camera settings.
    float gain = port->getGain();
    float offset = port->getOffset();
    int hbin = port->getHBin();
    int vbin = port->getVBin();
    float integTime = port->getIntegTime();
    float frameRate = port->getFrameRate();

    int nIter = ui->inputNIter->value();
    int tIntv = ui->inputTIntv->value();


    switch (captureMode)
    {
    case 0:     // Single Frame Mode
        img.captureSingle(dir, gain, offset, hbin, vbin, integTime, frameRate);
        break;

    case 1:     // Unlimited Mode
        img.captureUnlim(dir, gain, offset, hbin, vbin, integTime, frameRate);
        break;

    case 2:     // Number of Frame Mode
        int nFrm = ui->inputNFrm->value();
        img.captureNFrm(dir, nFrm, gain, offset, hbin, vbin, integTime, frameRate);
        break;

    default:
        break;
    }
}


void MainWindow::cancelCapture() {}
/*End of Test*/