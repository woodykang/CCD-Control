#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <QMessageBox>
#include <QImage>
#include <QLabel>
#include <QThread>
#include <QDateTime>
#include <QTimer>
#include <QElapsedTimer>
#include "niimaq.h"
#include "fitsio.h"
#include "1M30P_Protocol.h"

class image
{
public:
    image(QLabel *imageLabel = nullptr);
    ~image();

    void startGrab(int hbin, int vbin);
    void stopGrab();
    void imagePlot();
    void grabAndPlot();
    void saveSingleFrame(QString dir, int timeIntv, int nFile, float gain, int hBin, int vBin, float frameRate, float integTime);
    void saveBurst(QString dir, int nFrame, int nFile, float gain, int hBin, int vBin, float frameRate, float integTime);
    void save(QString filename, int nFrame, float gain, int hBin, int vBin, float frameRate, float integTime);
private:
    QImage img;
    QLabel* imageLabel;

    int error;

    char intfName[10] = "img0";      // interface name
    INTERFACE_ID Iid = 0;
    SESSION_ID Sid = 0;

    unsigned int AcqWinWidth;       // Acquisition Window Width
    unsigned int AcqWinHeight;      // Acquisition Window Height

    void* imageBuffer;
    void* copiedBuffer;

    unsigned long bufferSize;

    QThread* thread1;

    void showError(int error);
};

void showBox(QString content);

#endif // IMAGE_H
