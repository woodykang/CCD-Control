#include "CameraControl.h"
#include <math.h>

#ifndef BYTE
typedef unsigned char BYTE;
#endif

CameraPort::CameraPort()
{
    frameRate = 1/DEFAULT_FRAME_RATE;
    integrationTime = DEFAULT_INTG_TIME;

    Gain = DEFAULT_GAIN;
    Offset = DEFAULT_OFFSET;

    hBin = DEFAULT_BIN;
    vBin = DEFAULT_BIN;

    connect(this, SIGNAL(readyRead()), this, SLOT(getData()));
}
CameraPort::~CameraPort() {}

void CameraPort::getData()
{
    Output = readAll();
}

void CameraPort::getCameraType()
{
    QByteArray command;
    command.resize(1);              // The size of the command is 1 byte.
    command[0] = CMD_READ_CAMERA_TYPE;

    write(command);
    cameraType = Output[0];
}

void CameraPort::resetADC()
{
    QByteArray command;
    command.resize(1);              // The size of the command is 1 byte.
    command[0] = CMD_RESET_ADC;

    write(command);
}

void CameraPort::resetCamera()
{
    QByteArray command;
    command.resize(1);              // The size of the command is 1 byte.
    command[0] = CMD_RESET_CAMERA;

    write(command);
}


int CameraPort::getGain()
{
    QByteArray command;
    int gain = 0;

    command.resize(2);              // The size of the command is 2 byte.
    command[0] = CMD_READ_GAIN_MSB; // Read the Most  Significant Byte.
    command[1] = CMD_READ_GAIN_LSB; // Read the Least Significant Byte.


    write(command);

    gain += Output[0];      // MSB
    gain = gain << 8;       // shift 8 bits (= 1 byte)

    gain += Output[1];      // LSB

    return gain;
}


int CameraPort::getOffset()
{
    QByteArray command;
    int offset = 0;

    command.resize(2);              // The size of the command is 2 byte.
    command[0] = CMD_READ_GAIN_MSB; // Read the Most  Significant Byte.
    command[1] = CMD_READ_GAIN_LSB; // Read the Least Significant Byte.


    write(command);

    offset += Output[0];    // MSB
    offset = offset << 8;   // shift 8 bits (= 1 byte)
    offset += Output[1];     // LSB

    return offset;
}

void CameraPort::adjustGain(float gain)                 // 1 <= gain <= 10
{
    if (gain <1 || gain > 10)
    {
        return;
    }

    QByteArray command;
    int value;
    BYTE MSB, LSB;
    value = (int)log10(gain);

    MSB = value & 0xFF00;       // bit-wise AND
    LSB = value & 0x00FF;       // bit-wise AND


    command[0] = CMD_WRITE_GAIN_MSB;
    command[1] = MSB;
    command[2] = CMD_WRITE_GAIN_LSB;
    command[3] = LSB;

    write(command);
}

void CameraPort::adjustOffset(float offset)             // -4095 <= offset <= 4095
{
    if (offset < -4095 || offset > 4095)
    {
        return;
    }

    QByteArray command;
    int value;
    BYTE MSB, LSB;
    int gain;

    gain = getGain();

    value = (int) FACTOR_OFFSET * offset/gain;

    MSB = value & 0xFF00;       // bit-wise AND
    LSB = value & 0x00FF;       // bit-wise AND

    command[0] = CMD_WRITE_OFFSET_MSB;
    command[1] = MSB;
    command[2] = CMD_WRITE_OFFSET_LSB;
    command[3] = LSB;

    write(command);
}

void CameraPort::adjustBinning(int hbin, int vbin)      // hbin: horizontal bin, vbin: vertical bin
{
    QByteArray command;
    BYTE value = 0x00;

    switch (vbin)
    {
    case 1:
        value += 0x1;
    case 2:
        value += 0x2;
    case 4:
        value += 0x4;
    case 8:
        value += 0x0;
    default:                // if hbin is invalid, assume hbin = 1
        value += 0x1;
    }

    value = value << 4;     // shift 4 bits (= half byte)

    switch (hbin)
    {
    case 1:
        value += 0x1;
    case 2:
        value += 0x2;
    case 4:
        value += 0x4;
    case 8:
        value += 0x0;
    default:                // if vbin is invalid, assume vbin = 1
        value += 0x1;
    }

    command[0] = CMD_WRITE_BINNING;
    command[1] = value;

    write(command);
}

void CameraPort::adjustIntegTime(int microsec)            // adjust integration time in microseconds
{
/********************************************************************
 * Integration time must satisfy
 *      1) (integration time) < 1/(frame rate) - 2160 microseconds
 *      2) 5 microseconds < (integration time)
********************************************************************/

    if (microsec < 1/frameRate - 2160 || microsec > 5)
    {
        return;
    }

    QByteArray command;
    BYTE MSB, SSB, LSB;
    // MSB : Most Significant Byte
    // SSB: Second Most Significant Byte
    // LSB: Least Significant Byte

    MSB = microsec & 0xFF0000;      // bit-wise AND
    SSB = microsec & 0x00FF00;      // bit-wise AND
    LSB = microsec & 0x0000FF;      // bit-wise AND

    // To make sure that the integration time programmed in the
    // registers never become less than 5 microseconds, the first
    // command is to set the LSB to 0x05;
    BYTE Minimum = 0x05;

    command.resize(8);
    command[0] = CMD_WRITE_INTG_LSB;
    command[1] = Minimum;

    command[2] = CMD_WRITE_INTG_MSB;
    command[3] = MSB;

    command[4] = CMD_WRITE_INTG_SSB;
    command[5] = SSB;

    command[6] = CMD_WRITE_INTG_LSB;
    command[7] = LSB;

    write(command);
}

void CameraPort::adjustFrameRate(float FrameRate)            // adjust frame rate in fps
{
/*******************************************************************
 * Frame rate must satisfy:
 *      1) (integration time) < 1/(frame rate) - 2160 microseconds
 *      2) 5 microseconds < 1/(frame rate)
 *      3) (frame rate) < (maximum frame rate)
 *      Vertical Binning  |  Max Frame Rate
 *      --------------------------------------
 *              1x        |         30
 *              2x        |         54
 *              4x        |         88
 *              8x        |        129
*******************************************************************/
    if (integrationTime < (1/FrameRate)*1000000 - 2160 || (1/FrameRate)*1000000 > 5)
    {
        return;
    }

    switch (vBin)
    {
    case 1:
        if (FrameRate > 30) return;

    case 2:
        if (FrameRate > 54) return;

    case 4:
        if (FrameRate > 88) return;

    case 8:
        if (FrameRate > 129) return;
    default:
        if (FrameRate > 30) return;
    }

    QByteArray command;
    int value;
    BYTE MSB, SSB, LSB;
    // MSB : Most Significant Byte
    // SSB: Second Most Significant Byte
    // LSB: Least Significant Byte

    value = 1/FrameRate * 1000000;          // conversion to microseconds

    MSB = value & 0xFF0000;         // bit-wise AND
    SSB = value & 0x00FF00;         // bit-wise AND
    LSB = value & 0x0000FF;          // bit-wise AND

    // To make sure that 1/(frame rate) programmed in the registers
    // never become less than 5 microseconds, the first command is
    // to set the LSB to 0x05;
    BYTE Minimum = 0x05;

    command.resize(8);

    command[0] = CMD_WRITE_FRAMERATE_LSB;
    command[1] = Minimum;

    command[2] = CMD_WRITE_FRAMERATE_MSB;
    command[3] = MSB;

    command[4] = CMD_WRITE_FRAMERATE_SSB;
    command[5] = SSB;

    command[6] = CMD_WRITE_FRAMERATE_LSB;
    command[7] = LSB;

    write(command);
}
