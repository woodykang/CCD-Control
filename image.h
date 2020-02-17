#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <QMessageBox>
#include <QImage>
#include <QLabel>
#include <QThread>
#include "niimaq.h"

class image
{
public:
    image(QLabel *imageLabel = nullptr);
    ~image();

    void startGrab();
    void stopGrab();
    void imagePlot();
    void grabAndPlot();

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
};

void showError(int error);

#endif // IMAGE_H
