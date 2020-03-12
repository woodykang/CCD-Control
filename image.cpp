#include "image.h"

// error checking macro
#define errChk(fCall) if (error = (fCall), error < 0) {goto Error;} else {}

// Constructor
image::image(QLabel* imageLabel, QLabel* stdevLabel) : imageLabel(imageLabel), stdevLabel(stdevLabel)
{
    thread1 = nullptr;
}

// Destructor
image::~image()
{
    if(thread1 != nullptr)  delete thread1;
}

// Starts grabbing.
// Opens a session and get ready for grabbing.
// Runs grabAndPlot() in a different thread.
// Returns 0 on success, 1 on failure.
int image::startGrab(int hbin, int vbin)
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

    errChk(imgInterfaceOpen(intfName, &Iid));      // open interface with name 'intfName' and interface id 'Iid'
    errChk(imgSessionOpen(Iid, &Sid));             // open session with interface id 'Iid' and session id 'Sid'

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

    // Set the width and height of the imageWindow to the size of the image.
    imageLabel->setFixedWidth(AcqWinWidth);
    imageLabel->setFixedHeight(AcqWinHeight);

    // Setup and launch the grap operation
    errChk(imgGrabSetup(Sid, true));

    // Allocate a copied buffer with the same size as the 'imageBuffer'.
    copiedBuffer = nullptr;
    errChk(imgSessionGetBufferSize(Sid, &bufferSize));
    errChk(imgCreateBuffer(Sid, IMG_HOST_FRAME, bufferSize, &copiedBuffer));

    // Create a thread and run.
    thread1 = QThread::create(std::bind(&image::grabAndPlot, this));
    thread1->start();

    return 0;       // Function terminated successfully.

Error :
    if(error < 0)   showError(error);
    return 1;       // Error has occured.
}

// Initiates 'imgGrab()' and 'imagePlot()'.
// This function was implemented to be run in a separate thread
// by 'startGrab()'.
// Returns 0 on success, 1 on failure.
int image::grabAndPlot()
{
    imageBuffer = nullptr;
    errChk(imgGrab(Sid, &imageBuffer, true));
    imagePlot();

    return 0;       // Function terminated successfully.

Error:
    if (error < 0)   showError(error);
    return 1;       // Error has occurred.
}

// Plots the acquired image on imageLabel of the ui.
// Returns 0 on success, 1 on failure.
void image::imagePlot()
{
    int bufferIndex = 0;
    int waitForNext = 1;    // Wait until the current acquisition is complete.

    unsigned short value;   // pixel value

    unsigned int i;         // index for while loop
    unsigned int j;         // index for calculation of standard devaition
    float mean;             // mean of the pixel value
    float tempMean;         // temporary mean value
    float stdev;            // standard deviation

    while (1)               // Plotting must repeat unless grab stops with stopGrab()
    {
        // Copy the buffer.
        imgSessionCopyBuffer(Sid, bufferIndex, (unsigned char*)copiedBuffer, waitForNext);

        // Initialize variables.
        i = 0;
        j = 1;
        mean = 0;
        tempMean = 0;
        stdev = 0;

        // Convert 12-bit image to 16-bit image
        // and calculate the standard deviation using Welford's method.
        while (i < bufferSize)
        {
            value = ((unsigned char*)copiedBuffer)[i];
            value += ((unsigned char*)copiedBuffer)[i + 1] << 8;

            // Welford's method of standard deviation calculation
            tempMean = mean;
            mean += (value - tempMean) / j;
            stdev += (value - tempMean) * (value - mean);
            j++;

            // Shift pixel by 4 bits to make it a 16-bit image.
            value <<= 4;
            ((unsigned char*)copiedBuffer)[i] = (value & 0x00FF);           // LSB
            ((unsigned char*)copiedBuffer)[i + 1] = (value & 0xFF00) >> 8;  // MSB
            i += 2;
        }

        // Show the standard deviation of the pixel values.
        stdevLabel->setText(QString("Std Dev: ") + QString::number(stdev));

        // Create an image.
        img = QImage((unsigned char*)copiedBuffer, AcqWinWidth, AcqWinHeight, QImage::Format_Grayscale16);

        // Show the image.
        imageLabel->setPixmap(QPixmap::fromImage(img));

        if (QThread::currentThread()->isInterruptionRequested()) return;
    }
}

// Stops grabbing.
// Returns 0 on success, 1 on failure.
int image::stopGrab()
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

    return 0;       // Function terminated successfully.

Error:
    if (error < 0)   showError(error);
    return 1;       // Error has occurred.
}

// Saves one frame per file with each file taken after timeIntv (msec).
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

// Saves images as fast as the computer can handle.
// 'nFrame' per file, with total of 'nFile'.
void image::saveBurst(QString dir, int nFrame, int nFile, float gain, int hBin, int vBin, float frameRate, float integTime)
{
    const QString extension = ".fits";              // file extension
    QDateTime time = QDateTime::currentDateTime();  // time when the file is created
    for (int i = 0; i < nFile; i++)
    {
        //"!" overwrites file with the same name
        QString filename = "!" + dir + "\/" + time.toString("yyyyMMdd_hhmmss") + "_" + QString::number(i) + extension;
        save(filename, nFrame, gain, hBin, vBin, frameRate, integTime);
    }

    showBox("File saved.");
}

// Saves a single file with 'nFrame' being the number of frames in a file
void image::save(QString filename, int nFrame, float gain, int hBin, int vBin, float frameRate, float integTime)
{
    fitsfile* fptr;                             // pointer to the fits file
    int status = 0;                             // status > means error(s) occured
    int decimalNum = 2;                         // number of digits after the decimal point 

    int naxis = 2;                              // number of axes
    long naxes[2];                              // size of each axis
    long fpixel[2];                             // 1-based coordinate where to write the pixel value
    long nelements;                             // number of elements in an image
    naxes[0] = AcqWinWidth;                     // size of the first axis
    naxes[1] = AcqWinHeight;                    // size of the second axis
    nelements = naxes[0] * naxes[1];            // number of elements
    fpixel[0] = 1;                              // write the pixel value starting from column 1
    fpixel[1] = 1;                              // write the pixel value starting from column 2

    int bufIndex = 0;           // index of the buffer
    int waitForNext = 1;        // wait for the acquisition to be complete

    unsigned char* buffer = nullptr;            // secondary buffer used for saving image

    // Get the buffer size of session 'Sid'.
    errChk(imgSessionGetBufferSize(Sid, &bufferSize));
    // Create a buffer with size bufferSize.
    errChk(imgCreateBuffer(Sid, IMG_HOST_FRAME, bufferSize, (void **)&buffer));

    // Create a fits file at 'fptr'.
    fits_create_file(&fptr, (const char*)filename.toStdString().c_str(), &status);

    // Write images 'nFrame' times.
    for (int i = 0; i < nFrame; i++)
    {
        // Copy the original buffer to secondary buffer.
        errChk(imgSessionCopyBuffer(Sid, bufIndex, buffer, waitForNext));

        // Convert 12-bit image to 16-bit image by bit-shifting.
        // Bit-shifting is one of the fastest operation in C/C++.
        unsigned int j = 0;
        while (j < bufferSize)
        {
            unsigned short value = 0;

            // The memory is little endian.
            value += buffer[j];             // first byte
            value += buffer[j + 1] << 8;    // second byte
            value <<= 4;                    // shift 4 bits to make it 16-bit value
            buffer[j] = (value & 0x00FF);
            buffer[j + 1] = (value & 0xFF00) >> 8;
            j += 2;                         // reading 2 bytes per iteration
        }

        fits_create_img(fptr, USHORT_IMG, naxis, naxes, &status);

        // Write header.
        QDateTime currentTime = QDateTime::currentDateTime();           // time of observation
        fits_write_key_str(fptr, "TIME_OBS", (const char*)currentTime.toString("yyyy.MM.dd hh:mm:ss.zz").toStdString().c_str(), "Observing Time", &status);
        fits_write_key_flt(fptr, "EXPOSURE", integTime, decimalNum, "milliseconds", &status);       // exposure
        fits_write_key_flt(fptr, "GAIN", gain, decimalNum, "relative ADU/electrons", &status);      // gain
        fits_write_key_flt(fptr, "RATE", frameRate, decimalNum, "frames per second", &status);      // frame rate
        fits_write_key_log(fptr, "HBIN", hBin, "horizontal bin", &status);                          // horizontal bin
        fits_write_key_log(fptr, "VBIN", vBin, "vertical bin", &status);                            // vertical bin

        // Write pixel value.
        fits_write_pix(fptr, TUSHORT, fpixel, nelements, buffer, &status);
    }
    
    // Close file.
    fits_close_file(fptr, &status);
    
    // Dispose buffer.
    errChk(imgDisposeBuffer(buffer));

Error:
    if (error < 0)   showError(error);
    return;
}

// In case of error, this function will display a dialog box
// with the error message.
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

// Pops up a message box showing content.
void showBox(QString content)
{
    QMessageBox box;
    box.setFixedSize(500, 200);
    box.critical(nullptr, "Box", content);
}

/*Begin of Test*/
void image::captureSingle(QString dir, float gain, float offset, int hbin, int vbin, float integTime, float frameRate)
{

}

void image::captureUnlim(QString dir, float gain, float offset, int hbin, int vbin, float integTime, float frameRate)
{

}

void image::captureNFrm(QString dir, int nFrm, float gain, float offset, int hbin, int vbin, float integTime, float frameRate)
{

}

/*End of Test*/
