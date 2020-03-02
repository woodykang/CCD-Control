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

void image::startGrab(int hbin, int vbin)
{
    const unsigned long defaultWidth  = DEFAULT_WIDTH;
    const unsigned long defaultHeight = DEFAULT_HEIGHT;

    unsigned long top = 0;
    unsigned long left = 0;
    unsigned long height = defaultHeight / hbin;
    unsigned long width = defaultWidth / vbin;

    unsigned long fittedTop;
    unsigned long fittedLeft;
    unsigned long fittedHeight;
    unsigned long fittedWidth;

    errChk(imgInterfaceOpen(intfName, &Iid));      // open interface with name intfName and interface id Iid
    errChk(imgSessionOpen(Iid, &Sid));             // open session with interface id Iid and session id Sid

    errChk(imgSessionFitROI(Sid, IMG_ROI_FIT_SMALLER, top, left, height, width, &fittedTop, &fittedLeft, &fittedHeight, &fittedWidth));
    errChk(imgSessionConfigureROI(Sid, fittedTop, fittedLeft, fittedHeight, fittedWidth));

    AcqWinWidth = fittedWidth;
    AcqWinHeight = fittedHeight;

    errChk(imgSetAttribute2(Sid, IMG_ATTR_ROI_WIDTH, AcqWinWidth));
    errChk(imgSetAttribute2(Sid, IMG_ATTR_ROI_HEIGHT, AcqWinHeight));

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

void image::saveSingleFrame(QString dir, int timeIntv, int nFile, float gain, int hBin, int vBin, float frameRate, float integTime)
{
    const QString extension = ".fits";      // file extension
    const int nFrame = 1;                   // number of frames per file

    QTimer timer;
    QDateTime time = QDateTime::currentDateTime();
    QString filename = dir + "\/" + time.toString("yyyyMMdd_hhmmss") + "_" + QString::number(nFile) + extension;


    // save recursively after timer has timed out in timeIntv msec
    if (nFile > 1)
    {
        timer.singleShot(timeIntv, std::bind(&image::saveSingleFrame, this, dir, timeIntv, nFile - 1, gain, hBin, vBin, frameRate, integTime));
    }
    
    else showBox("File saved.");
    
    save(filename, nFrame, gain, hBin, vBin, frameRate, integTime);    
}

void image::saveBurst(QString dir, int nFrame, int nFile, float gain, int hBin, int vBin, float frameRate, float integTime)
{
    const QString extension = ".fits";      // file extension
    QDateTime time = QDateTime::currentDateTime();
    for (int i = 0; i < nFile; i++)
    {
        //"!" overwrites file with the same name
        QString filename = "!" + dir + "\/" + time.toString("yyyyMMdd_hhmmss") + "_" + QString::number(i) + extension;   // February 18th, 2020 14:37:45 -> 20200218_143745

        save(filename, nFrame, gain, hBin, vBin, frameRate, integTime);
    }

    showBox("File saved.");
}

void image::save(QString filename, int nFrame, float gain, int hBin, int vBin, float frameRate, float integTime)
{
    char err_text[30] = "";

    fitsfile* fptr;                             // pointer to the fits file
    int status = 0;                             // status > means error(s) occured
    int decimalNum = 2;                         // number of digits after the decimal point 

    int naxis = 2;                              // number of axes
    long naxes[2];                              // size of each axis
    long fpixel[2];                             // 1-based coordinate where to write the pixel value
    long nelements;                             // number of elements in an image
    naxes[0] = AcqWinWidth;                     // size of the first axis
    naxes[1] = AcqWinHeight;                    // size of the second axis
    //naxes[2] = nFrame;                          // size of the third axis
    nelements = naxes[0] * naxes[1];            // number of elements
    fpixel[0] = 1;                              // write the pixel value starting from column 1
    fpixel[1] = 1;                              // write the pixel value starting from column 2

    int bufIndex = 0;           // index of the buffer
    int waitForNext = 1;        // wait for the acquisition to be complete

    unsigned char* buffer = nullptr;                    // secondary buffer used for saving image
    errChk(imgSessionGetBufferSize(Sid, &bufferSize));  // get the buffer size of session Sid    
    errChk(imgCreateBuffer(Sid, IMG_HOST_FRAME, bufferSize, (void **)&buffer));     // create a buffer with size bufferSize

    fits_create_file(&fptr, (const char*)filename.toStdString().c_str(), &status);  // create a fits file at pointer fptr

    // write images nFrame times
    for (int i = 0; i < nFrame; i++)
    {
        //fpixel[2] = i + 1;
        errChk(imgSessionCopyBuffer(Sid, bufIndex, buffer, waitForNext));   // copy the original buffer to secondary buffer

        // convert 12-bit image to 16-bit image by bit-shifting
        unsigned int j = 0;
        while (j < bufferSize)
        {
            unsigned short value = 0;

            // the memory is little endian
            value += buffer[j];
            value += buffer[j + 1] << 8;
            value <<= 4;
            buffer[j] = (value & 0x00FF);
            buffer[j + 1] = (value & 0xFF00) >> 8;
            j += 2;
        }

        fits_create_img(fptr, USHORT_IMG, naxis, naxes, &status);

        // write header
        QDateTime currentTime = QDateTime::currentDateTime();           // time of observation
        fits_write_key_str(fptr, "TIME_OBS", (const char*)currentTime.toString("yyyy.MM.dd hh:mm:ss.zz").toStdString().c_str(), "Observing Time", &status);
        fits_write_key_flt(fptr, "EXPOSURE", integTime, decimalNum, "milliseconds", &status);
        fits_write_key_flt(fptr, "GAIN", gain, decimalNum, "relative ADU/electrons", &status);
        fits_write_key_flt(fptr, "RATE", frameRate, decimalNum, "frames per second", &status);
        fits_write_key_log(fptr, "HBIN", hBin, "horizontal bin", &status);
        fits_write_key_log(fptr, "VBIN", vBin, "vertical bin", &status);

        // write pixel value
        fits_write_pix(fptr, TUSHORT, fpixel, nelements, buffer, &status);
    }
    
    fits_close_file(fptr, &status);
    
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
