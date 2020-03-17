#ifndef IMAGE_H
#define IMAGE_H

#define CAPTURE_MODE_SINGLE 0
#define CAPTURE_MODE_UNLIM  1
#define CAPTURE_MODE_NFRM   2

#include <QObject>
#include <QMessageBox>
#include <QImage>
#include <QLabel>
#include <QThread>
#include <QDateTime>
#include <QTimer>
#include "niimaq.h"
#include "fitsio.h"
#include "1M30P_Protocol.h"

class image
{
public:
    // public member funcitons
    image(QLabel *imageLabel = nullptr, QLabel *stdevLabel = nullptr);
    ~image();

    int startGrab(int hbin, int vbin);
    int stopGrab();
    void imagePlot();
    int grabAndPlot();
    void saveSingleFrame(QString dir, int timeIntv, int nFile, float gain, int hBin, int vBin, float frameRate, float integTime);
    void saveBurst(QString dir, int nFrame, int nFile, float gain, int hBin, int vBin, float frameRate, float integTime);
    void save(QString filename, int nFrame, float gain, int hBin, int vBin, float frameRate, float integTime);

private:
    // private member variables
    QImage img;
    QLabel* imageLabel;
    QLabel* stdevLabel;

    int error;

    char intfName[10] = "img0";      // interface name
    INTERFACE_ID Iid = 0;
    SESSION_ID Sid = 0;

    unsigned int AcqWinWidth;       // Acquisition Window Width
    unsigned int AcqWinHeight;      // Acquisition Window Height

    void* imageBuffer;
    void* copiedBuffer;

    unsigned long bufferSize;

    QThread* threadGrab;

    // private member fuction
    void showError(int error);

    /*Begin of Test*/
public:
    void startCapture(int mode, QString dir, int nFrm, float gain, float offset, int hBin, int vBin, float integTime, float frameRate);

    void captureSingle(QString dir, float gain, float offset, int hBin, int vBin, float integTime, float frameRate);
    void captureUnlim(QString dir, float gain, float offset, int hBin, int vBin, float integTime, float frameRate);
    void captureNFrm(QString dir, int nFrm, float gain, float offset, int hBin, int vBin, float integTime, float frameRate);

    void capture(QString dir, int nFrm, float gain, float offset, int hBin, int vBin, float frameRate, float integTime);
    void cancelCapture();

    QThread* threadCapture;
    QTimer sequenceTimer;

signals:
    void endOfCapture();
    /*End of Test*/
};

void showBox(QString content);

#endif // IMAGE_H
