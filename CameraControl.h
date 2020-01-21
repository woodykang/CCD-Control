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

    QSerialPort::BaudRate defaultBaudRate;
    QSerialPort::DataBits defaultDataBits;
    QSerialPort::StopBits defaultStopBits;
    QSerialPort::Parity   defaultParity;

public slots:
    void getData();         // reads the reply and saves it in ouput

public:
    CameraPort();
    ~CameraPort();

    void openCameraPort(const QString &portName);
    void openCameraPort(const QString &portName,
                        QSerialPort::BaudRate baudRate,
                        QSerialPort::DataBits dataBits,
                        QSerialPort::StopBits stopBits,
                        QSerialPort::Parity   parity);

    void closeCameraPort();

    void getCameraType();
    void resetADC();
    void resetCamera();
    int getGain();
    int getOffset();
    int getHBin();
    int getVBin();
    int getIntegTime();
    float getFrameRate();

    void adjustGain(float gain);                // 1 <= gain <= 10
    void adjustOffset(float offset);
    void adjustBinning(int hbin, int vbin);     // hbin: horizontal bin, vbin: vertical bin
    void adjustIntegTime(int microsec);         // adjust integration time in microseconds
    void adjustFrameRate(float FrameRate);      // adjust frame rate in fps

    bool isGainOK(float gain);                  // returns true if gain satisfies Gain Condition
    bool isOffsetOK(float offset);              // returns true if offset satisfies Offset Condition
    bool isIntegTimeOK(int microsec);           // returns true if microsec satisifes Integration Time Condition
    bool isFrameRateOK(int FrameRate);          // returns true if FrameRate satisifes Frame Rate Condition
};


#endif // CAMERACONTROL_H
