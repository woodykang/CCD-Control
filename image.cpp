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

    errChk(imgSetAttribute2(Sid, IMG_ATTR_ROI_WIDTH, AcqWinWidth));
    errChk(imgSetAttribute2(Sid, IMG_ATTR_ROI_HEIGHT, AcqWinHeight));
    errChk(imgSetAttribute2(Sid, IMG_ATTR_ROWPIXELS, AcqWinWidth));

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

void image::save(QString dir, int nFrame, float gain, int hBin, int vBin, float frameRate, float integTime)
{
    char err_text[30] = "asdf";
    const QString extension = ".fits";      // file extension
    QDateTime currentTime = QDateTime::currentDateTime();
    
    QString filename = "!" + dir + "\/" + currentTime.toString("yyyyMMdd_hhmmss") + extension;   // February 18th, 2020 14:37:45 -> 20200218_143745

    fitsfile* fptr;
    int status = 0;
    int decimalNum = 2;

    int naxis = 3;                              // number of axes
    long naxes[3], fpixel[3], nelements;
    naxes[0] = AcqWinWidth;                     // size of the first axis
    naxes[1] = AcqWinHeight;                    // size of the second axis
    naxes[2] = nFrame;                          // size of the third axis
    nelements = naxes[0] * naxes[1];            // number of elements
    fpixel[0] = 1;
    fpixel[1] = 1;

    int bufIndex = 0;           // index of the buffer
    int waitForNext = 1;        // wait for the acquisition to be complete

    unsigned char* buffer = nullptr;
    errChk(imgSessionGetBufferSize(Sid, &bufferSize));
    errChk(imgCreateBuffer(Sid, IMG_HOST_FRAME, bufferSize, (void **)&buffer));

    fits_create_file(&fptr, (const char*)filename.toStdString().c_str(), &status);

    for (int i = 0; i < nFrame; i++)
    {
        fpixel[2] = i + 1;
        errChk(imgSessionCopyBuffer(Sid, bufIndex, buffer, waitForNext));

        unsigned int j = 0;
        while (j < bufferSize)
        {
            unsigned short value;
            value = buffer[j];
            value += buffer[j + 1] << 8;
            value <<= 4;
            buffer[j] = (value & 0x00FF);
            buffer[j + 1] = (value & 0xFF00) >> 8;
            j += 2;
        }

        fits_create_img(fptr, SHORT_IMG, naxis, naxes, &status);

        fits_write_key_str(fptr, "TIME_OBS", (const char*)currentTime.toString("yyyy.MM.dd hh:mm:ss").toStdString().c_str(), "Observing Time", &status);
        fits_write_key_flt(fptr, "EXPOSURE", integTime, decimalNum, "milliseconds", &status);
        fits_write_key_flt(fptr, "GAIN", gain, decimalNum, "relative ADU/electrons", &status);
        fits_write_key_flt(fptr, "RATE", frameRate, decimalNum, "frames per second", &status);
        fits_write_key_log(fptr, "HBIN", hBin, "horizontal bin", &status);
        fits_write_key_log(fptr, "VBIN", vBin, "vertical bin", &status);

        fits_write_pix(fptr, TUSHORT, fpixel, nelements, buffer, &status);
    }

    showBox("Outside for loop.");

    fits_get_errstatus(status, err_text);
    showBox(err_text);
    
    fits_close_file(fptr, &status);
    showBox("File closed.");
    errChk(imgDisposeBuffer(buffer));

Error:
    if (error < 0)   showError(error);
    return;
}

// in case of error this function will display a dialog box
// with the error message
void image::showError(int error)
{
    static char ErrorMessage[256];

    memset(ErrorMessage, 0x00, sizeof(ErrorMessage));

    // converts error code to a message
    imgShowError(error, ErrorMessage);

    QMessageBox errorBox;                                   // Error Message Box
    errorBox.setFixedSize(500, 200);
    errorBox.critical(nullptr, "Error", ErrorMessage);
}

void showBox(QString content)
{
    QMessageBox box;
    box.setFixedSize(500, 200);
    box.critical(nullptr, "Box", content);
}
