#include "image.h"

// error checking macro
#define errChk(fCall) if (error = (fCall), error < 0) {goto Error;} else {}

image::image(QLabel* imageLabel) : imageLabel(imageLabel)
{
    thread1 = nullptr;
}

image::~image()
{
    if(thread1 != nullptr)  delete thread1;
}

void image::startGrab()
{
    errChk(imgInterfaceOpen(intfName, &Iid));      // open interface with name intfName and interface id Iid
    errChk(imgSessionOpen(Iid, &Sid));             // open session with interface id Iid and session id Sid

    // Let's check that the Acquisition window is not smaller than the Canvas
    errChk(imgGetAttribute(Sid, IMG_ATTR_ROI_WIDTH, &AcqWinWidth));        // AcqWinWidht = IMG_ATTR_ROI_WIDHT
    errChk(imgGetAttribute(Sid, IMG_ATTR_ROI_HEIGHT, &AcqWinHeight));      // AcqWinHeight = IMG_ATTR_ROI_HEIGHT
    errChk(imgSetAttribute2 (Sid, IMG_ATTR_ROWPIXELS, AcqWinWidth));

    // set the width and height of the imageWindow to the size of the image
    imageLabel->setFixedWidth(AcqWinWidth);
    imageLabel->setFixedHeight(AcqWinHeight);

    // Setup and launch the grap operation
    errChk(imgGrabSetup(Sid, true));

    // allocate a copied buffer with the same size as the imageBuffer
    copiedBuffer = nullptr;
    errChk(imgSessionGetBufferSize(Sid, &bufferSize));
    errChk(imgCreateBuffer(Sid, IMG_HOST_FRAME, bufferSize, &copiedBuffer));

    // create a thread and run
    thread1 = QThread::create(std::bind(&image::grabAndPlot, this));
    thread1->start();

Error :
    if(error < 0)   showError(error);
    return;
}

void image::grabAndPlot()
{
    imageBuffer = nullptr;
    errChk(imgGrab(Sid, &imageBuffer, true));
    imagePlot();

Error:
    if (error < 0)   showError(error);
    return;
}

void image::imagePlot()
{
    int bufferIndex = 0;
    int waitForNext = 1;    // wait until the current acquisition is complete

    while (1)               // Plotting must repeat unless grab stops with stopGrab()
    {
        imgSessionCopyBuffer(Sid, bufferIndex, (unsigned char*)copiedBuffer, waitForNext);    // copy the buffer

        // convert 12-bit image to 16-bit image
        unsigned int j = 0;
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

        img = QImage((unsigned char*)copiedBuffer, AcqWinWidth, AcqWinHeight, QImage::Format_Grayscale16);            // create an image
        imageLabel->setPixmap(QPixmap::fromImage(img));    // show the image

        if (QThread::currentThread()->isInterruptionRequested()) return;
    }
}

void image::stopGrab()
{
    thread1->requestInterruption();
    if (!thread1->wait(3000))
    {
        thread1->terminate();
        thread1->wait();
    }
    thread1 = nullptr;

    errChk(imgSessionStopAcquisition(Sid));

    if (Sid != 0)
    {
        errChk(imgClose(Sid, true));
    }

    if (Iid != 0)
    {
        errChk(imgClose(Iid, true));
    }


Error:
    if (error < 0)   showError(error);
    return;
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
