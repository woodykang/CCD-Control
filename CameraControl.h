#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <QSerialPort>
#include "1M30P_Protocol.h"

/**********************************
 * This program uses Qt 5 for
 * serial communication.
**********************************/

class CameraPort : QSerialPort
{
private:
    QByteArray Output;      // reply from camera communication
    int cameraType;         // Camera Type in hex code
    int hBin;               // horizontal binning. either 1, 2, 4, or 8
    int vBin;               // vertical   binning. either 1, 2, 4, or 8
    int Gain;               // gain
    int Offset;             // offset
    int integrationTime;    // integrate time in microseconds
    float frameRate;        // frame rate in fps

public slots:
    void getData();         // reads the reply and saves it in ouput

public:
    CameraPort();
    ~CameraPort();

    void getCameraType();
    void resetADC();
    void resetCamera();
    int getGain();
    int getOffset();

    void adjustGain(float gain);                // 1 <= gain <= 10
    void adjustOffset(float offset);
    void adjustBinning(int hbin, int vbin);     // hbin: horizontal bin, vbin: vertical bin
    void adjustIntegTime(int microsec);         // adjust integration time in microseconds
    void adjustFrameRate(float FrameRate);      // adjust frame rate in fps
};


#endif // CAMERACONTROL_H
