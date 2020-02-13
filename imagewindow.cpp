#include "imagewindow.h"
#include "ui_imagewindow.h"
#include "niimaq.h"


// error checking macro
#define errChk(fCall) if (error = (fCall), error < 0) {goto Error;} else {}

imageWindow::imageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imageWindow)
{
    ui->setupUi(this);
    thread1 = nullptr;
}

imageWindow::~imageWindow()
{
    if(thread1 != nullptr)  delete thread1;
    delete ui;
}

void imageWindow::startGrab()
{
    errChk(imgInterfaceOpen(intfName, &Iid));      // open interface with name intfName and interface id Iid
    errChk(imgSessionOpen(Iid, &Sid));             // open session with interface id Iid and session id Sid

    // Let's check that the Acquisition window is not smaller than the Canvas
    errChk(imgGetAttribute(Sid, IMG_ATTR_ROI_WIDTH, &AcqWinWidth));        // AcqWinWidht = IMG_ATTR_ROI_WIDHT
    errChk(imgGetAttribute(Sid, IMG_ATTR_ROI_HEIGHT, &AcqWinHeight));      // AcqWinHeight = IMG_ATTR_ROI_HEIGHT


    // Set the ROI to the size of the Canvas so that it will fit nicely
    //errChk(imgSetAttribute2 (Sid, IMG_ATTR_ROI_WIDTH, AcqWinWidth));
    //errChk(imgSetAttribute2 (Sid, IMG_ATTR_ROI_HEIGHT, AcqWinHeight));
    errChk(imgSetAttribute2 (Sid, IMG_ATTR_ROWPIXELS, AcqWinWidth));

    // set the width and height of the imageWindow to the size of the image
    setFixedWidth(AcqWinWidth);
    setFixedHeight(AcqWinHeight);

    // Setup and launch the grap operation
    errChk(imgGrabSetup(Sid, true));

    // allocate a copied buffer with the same size as the imageBuffer
    copiedBuffer = nullptr;
    errChk(imgSessionGetBufferSize(Sid, &bufferSize));
    errChk(imgCreateBuffer(Sid, IMG_HOST_FRAME, bufferSize, &copiedBuffer));

    // create a thread and run
    thread1 = QThread::create(std::bind(&imageWindow::grabAndPlot, this));
    thread1->start();

    
Error :
    if(error < 0)   showError(error);
    return;
}

void imageWindow::grabAndPlot()             // imgGrab() and imagePlot() must be on the same thread
{
    imgGrab(Sid, &imageBuffer, true);
    imagePlot();
}

void imageWindow::imagePlot()
{
    showBox("loc: ", 1);
    int bufferIndex = 0;
    int waitForNext = 1;    // wait until the current acquisition is complete
    

    while (1)               // Plotting must repeat unless grab stops with stopGrab()
    {
        imgSessionCopyBuffer(Sid, bufferIndex, (unsigned char*)copiedBuffer, waitForNext);    // copy the buffer

        // convert 12-bit image to 16-bit image
        int j = 0;
        while (j < bufferSize)
        {
            unsigned short value;
            value = ((unsigned char*)copiedBuffer)[j];
            value += ((unsigned char*)copiedBuffer)[j + 1] << 8;
            value <<= 4;
            ((unsigned char*)copiedBuffer)[j] = (value & 0x00FF);
            ((unsigned char*)copiedBuffer)[j + 1] = (value & 0xFF00) >> 8;
            j += 2;
        }
        
        image = QImage((unsigned char*)copiedBuffer, AcqWinWidth, AcqWinHeight, QImage::Format_Grayscale16);            // create an image
        ui->imageLabel->setPixmap(QPixmap::fromImage(image));    // show the image
    }
}


void imageWindow::stopGrab()
{
    errChk(imgSessionStopAcquisition(Sid));

    if(thread1 != nullptr)
    {
        thread1->quit();
        delete thread1;
        thread1 = nullptr;
    }

    if(Sid != 0)
    {
        errChk(imgClose(Sid, true));
    }

    if(Iid != 0)
    {
        errChk(imgClose(Iid, true));
    }
    
    if (copiedBuffer != nullptr)
    {
        errChk(imgDisposeBuffer(copiedBuffer));
        copiedBuffer = nullptr;
    }

Error:
    if (error < 0)   showError(error);
    return;
}

void imageWindow::closeEvent(QCloseEvent* e)
{
    emit windowClosed();
    e->accept();     
}

// in case of error this function will display a dialog box
// with the error message
void showError(int error)
{   
    static char ErrorMessage[256];

    memset(ErrorMessage, 0x00, sizeof(ErrorMessage));

    // converts error code to a message
    imgShowError(error, ErrorMessage);

    QMessageBox errorBox;                                   // Error Message Box
    errorBox.setFixedSize(500, 200);

    errorBox.critical(nullptr, "Error", ErrorMessage);   
}

void showBox(QString str, int i)
{
    QMessageBox Box;                                   // Error Message Box
    QString content = str + QString::number(i);
    Box.setFixedSize(500, 200);

    Box.critical(nullptr, "Here", content);
}