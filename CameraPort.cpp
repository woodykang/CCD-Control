#include "CameraPort.h"
#include <math.h>

#ifndef BYTE
typedef unsigned char BYTE;
#endif  // BYTE

// Constructor
CameraPort::CameraPort(QSerialPort* parent) : QSerialPort(parent)
{
    // Set default settings.
    cameraType = NULL;
    frameRate = DEFAULT_FRAME_RATE;
    integrationTime = DEFAULT_INTG_TIME;

    Gain = DEFAULT_GAIN;
    Offset = DEFAULT_OFFSET;

    hBin = DEFAULT_BIN;
    vBin = DEFAULT_BIN;

    // Connect signals to slots.
    connect(this, SIGNAL(readyRead()), this, SLOT(getData()));

    // Default port connection parameters.
    defaultBaudRate = QSerialPort::Baud9600;
    defaultDataBits = QSerialPort::Data8;
    defaultStopBits = QSerialPort::OneStop;
    defaultParity   = QSerialPort::NoParity;

}

// Destructor
CameraPort::~CameraPort() {}

// This is triggered when data has been sent through the port.
// This reads the data and saves it .
void CameraPort::getData()
{
    Output = readAll();
}

// Opens a serial port with name portName.
void CameraPort::openCameraPort(const QString &portName)
{
    setPortName(portName);
    setBaudRate(defaultBaudRate);
    setDataBits(defaultDataBits);
    setStopBits(defaultStopBits);
    setParity(defaultParity);
    open(QIODevice::ReadWrite);
}

// Overriden function of openCameraPort
void CameraPort::openCameraPort(const QString &portName,
                                QSerialPort::BaudRate baudRate,
                                QSerialPort::DataBits dataBits,
                                QSerialPort::StopBits stopBits,
                                QSerialPort::Parity   parity)
{
    setPortName(portName);
    setBaudRate(baudRate);
    setDataBits(dataBits);
    setStopBits(stopBits);
    setParity(parity);
    open(QIODevice::ReadWrite);
}

// Closes the connected serial port.
void CameraPort::closeCameraPort()
{
    close();
}

// Sends a READ commmand to the camera,
// reads the response, and save the camera type to 'cameraType'.
void CameraPort::getCameraType()
{
    QByteArray command;
    command.resize(1);              // The size of the command is 1 byte.
    command[0] = (BYTE) CMD_READ_CAMERA_TYPE;

    write(command);                 // Write the command to the port.
    waitForReadyRead(100);          // Wait for response.
    cameraType = Output[0];
}

// "Soft Reset"
// Resets gain and offset.
void CameraPort::resetADC()
{
    QByteArray command;
    command.resize(1);              // The size of the command is 1 byte.
    command[0] = (BYTE) CMD_RESET_ADC;

    write(command);                 // Write the command to the port.

    // Gain and Offset are set to their default values.
    Gain = DEFAULT_GAIN;
    Offset = DEFAULT_OFFSET;
}

// "Hard Reset"
// Resets all parameters such as
// gain, offset, binning, integration time, and frame rate.
void CameraPort::resetCamera()
{
    QByteArray command;
    command.resize(1);              // The size of the command is 1 byte.
    command[0] = (BYTE) CMD_RESET_CAMERA;

    write(command);                 // Write the commnad to the port.

    // All parameters are set to their default values.
    Gain = DEFAULT_GAIN;
    Offset = DEFAULT_OFFSET;
    hBin = DEFAULT_BIN;
    vBin = DEFAULT_BIN;
    frameRate = DEFAULT_FRAME_RATE;
    integrationTime = DEFAULT_INTG_TIME;    
}

// Returns 'Gain'.
float CameraPort::getGain()
{
    return Gain;
}

// Returns 'Offset'.
float CameraPort::getOffset()
{
    return Offset;
}

// Returns 'hBin' (horizontal binning).
int CameraPort::getHBin()
{
    return hBin;
}

// Returns 'vBin' (vertical binning).
int CameraPort::getVBin()
{
    return vBin;
}

// Returns 'integTime' (integration time).
int CameraPort::getIntegTime()
{
    return integrationTime;
}

// Returns 'frameRate' (frame rate).
float CameraPort::getFrameRate()
{
    return frameRate;
}

// Adjusts the camera's 'Gain' (current state) to 'gain' (input).
void CameraPort::adjustGain(float gain)                 // 1 <= gain <= 10
{
    if (!isGainOK(gain))    return; // Check if 'gain' is OK.

    QByteArray command;
    unsigned short value;
    BYTE MSB, LSB;
    value = FACTOR_GAIN * log10(gain);

    MSB = (value & 0xFF00) >> 8;    // bit-wise AND
    LSB = value & 0x00FF;           // bit-wise AND

    command.resize(4);
    command[0] = (BYTE) CMD_WRITE_GAIN_MSB;
    command[1] = MSB;
    command[2] = (BYTE) CMD_WRITE_GAIN_LSB;
    command[3] = LSB;

    write(command);

    //Gain = gain;        // Set the value of the member variable to the input value.

    /*Begin of Test*/
    readGain();
    /*End of Test*/
}

// Adjusts the camera's 'Offset' (current state) to 'offset' (input).
void CameraPort::adjustOffset(float offset)             // -4095 <= offset <= 4095
{
    if (!isOffsetOK(offset))    return; // Check if 'offset' is OK.

    QByteArray command;
    unsigned short value;
    BYTE MSB, LSB;
    value = FACTOR_OFFSET * offset/Gain;

    MSB = (value & 0xFF00) >> 8;        // bit-wise AND
    LSB = (value & 0x00FF);             // bit-wise AND

    command.resize(4);
    command[0] = (BYTE)CMD_WRITE_OFFSET_MSB;
    command[1] = MSB;
    command[2] = (BYTE)CMD_WRITE_OFFSET_LSB;
    command[3] = LSB;

    write(command);

    //Offset = offset;    // Set value of the member variable as the input value.

    /*Begin of Test*/
    readOffset();
    /*End of Test*/
}

// Adjusts the camera's 'hBin', 'vBin' (current state) to 'hbin', 'vbin' (input).
void CameraPort::adjustBinning(int hbin, int vbin)      // hbin: horizontal bin, vbin: vertical bin
{
    QByteArray command;
    BYTE value = 0x00;

    // vertical binning
    switch (vbin)
    {
    case 1:
        value += CMD_WRITE_BIN_X1;
        break;
    case 2:
        value += CMD_WRITE_BIN_X2;
        break;
    case 4:
        value += CMD_WRITE_BIN_X4;
        break;
    case 8:
        value += CMD_WRITE_BIN_X8;
        break;
    default:                // If hbin is invalid, assume hbin = 1.
        value += CMD_WRITE_BIN_X1;
        break;
    }

    value = value << 4;     // Shift 4 bits (= half byte).

    // horizontal binning
    switch (hbin)
    {
    case 1:
        value += CMD_WRITE_BIN_X1;
        break;
    case 2:
        value += CMD_WRITE_BIN_X2;
        break;
    case 4:
        value += CMD_WRITE_BIN_X4;
        break;
    case 8:
        value += CMD_WRITE_BIN_X8;
        break;
    default:                // If vbin is invalid, assume vbin = 1.
        value += CMD_WRITE_BIN_X1;
        break;
    }

    command.resize(2);      // Size of the command is 2 bytes.
    command[0] = (BYTE) CMD_WRITE_BINNING;
    command[1] = value;

    write(command);         // Write command to the port.

    // Set the values of the member variables as the input value. 
    hBin = hbin;
    vBin = vbin;
}

// Adjusts the camera's 'integTime' (current state) to 'microsec' (input).
void CameraPort::adjustIntegTime(int microsec)            // adjust integration time in microseconds
{
    if (!isIntegTimeOK(microsec))   return; // Check if 'microsec' is OK.

    QByteArray command;
    BYTE MSB, SSB, LSB;
    // MSB : Most Significant Byte
    // SSB: Second Most Significant Byte
    // LSB: Least Significant Byte

    MSB = ( (unsigned int)microsec & 0xFF0000) >> 16;      // bit-wise AND
    SSB = ( (unsigned int)microsec & 0x00FF00) >> 8;      // bit-wise AND
    LSB = (unsigned int)microsec & 0x0000FF;      // bit-wise AND

    // To make sure that the integration time programmed in the
    // registers never become less than 5 microseconds, the first
    // command is to set the LSB to 0x06;
    BYTE Minimum = 0x06;

    command.resize(8);
    command[0] = (BYTE) CMD_WRITE_INTG_LSB;
    command[1] = Minimum;

    command[2] = (BYTE) CMD_WRITE_INTG_MSB;
    command[3] = MSB;

    command[4] = (BYTE) CMD_WRITE_INTG_SSB;
    command[5] = SSB;

    command[6] = (BYTE) CMD_WRITE_INTG_LSB;
    command[7] = LSB;

    write(command);     // Write the command to the port.

    integrationTime = microsec;     // Set the value of the member variable as the input value.
}

// Adjusts the camera's frameRate (current state) to FrameRate (input).
void CameraPort::adjustFrameRate(float framerate)            // adjust frame rate in fps
{
    if (!isFrameRateOK(framerate))  return;

    QByteArray command;
    unsigned int value;
    BYTE MSB, SSB, LSB;
    // MSB : Most Significant Byte
    // SSB: Second Most Significant Byte
    // LSB: Least Significant Byte

    value = FACTOR_S2MS/framerate;          // conversion to microseconds

    MSB = (value & 0xFF0000) >> 16;         // bit-wise AND
    SSB = (value & 0x00FF00) >> 8;          // bit-wise AND
    LSB = value & 0x0000FF;                 // bit-wise AND

    // To make sure that 1/(frame rate) programmed in the registers
    // never become less than 5 microseconds, the first command is
    // to set the LSB to 0x06;
    BYTE Minimum = 0x06;

    command.resize(8);

    command[0] = (BYTE) CMD_WRITE_FRAMERATE_LSB;
    command[1] = Minimum;

    command[2] = (BYTE) CMD_WRITE_FRAMERATE_MSB;
    command[3] = MSB;

    command[4] = (BYTE) CMD_WRITE_FRAMERATE_SSB;
    command[5] = SSB;

    command[6] = (BYTE) CMD_WRITE_FRAMERATE_LSB;
    command[7] = LSB;

    write(command);     // Write the command to the port.

    frameRate = FACTOR_S2MS/value;      // Set the value of the member variable as the input value.
}

// Returns true if gain satisfies Gain Condition
bool CameraPort::isGainOK(float gain)
{
    return (MIN_GAIN <= gain) || (gain <= MAX_GAIN);
}

// Returns true if offset satisfies Offset Condition
bool CameraPort::isOffsetOK(float offset)
{
    return (MIN_OFFSET <= offset) || (offset <= MAX_OFFSET);
}

// Returns true if microsec satisifes Integration Time Condition
bool CameraPort::isIntegTimeOK(int microsec)            
{
/********************************************************************
    * Integration time must satisfy
    *      1) (integration time) < 1/(frame rate) - 2160 microseconds
    *      2) 5 microseconds < (integration time)
********************************************************************/

    bool b;
    b = (microsec <= (float)FACTOR_S2MS/frameRate - (float)FACTOR_INTEG_COND) && (MIN_TIME <= microsec);
    return b;
}

// Returns true if FrameRate satisifes Frame Rate Condition
bool CameraPort::isFrameRateOK(int FrameRate)           
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
    bool b;

    b = (integrationTime <= (float)FACTOR_S2MS/FrameRate - FACTOR_INTEG_COND) && (MIN_TIME <= FACTOR_S2MS/FrameRate);

    switch (vBin)
    {
    case 1:
        if (FrameRate > 30) b = false;
        break;

    case 2:
        if (FrameRate > 54) b = false;
        break;

    case 4:
        if (FrameRate > 88) b = false;
        break;

    case 8:
        if (FrameRate > 129) b = false;
        break;

    default:
        if (FrameRate > 30) b = false;
        break;
    }

    return b;
}


/*Begin of Test*/
void CameraPort::readGain()
{
    QByteArray command;
    int gain = 0;

    command.resize(2);              // The size of the command is 2 byte.
    command[0] = (BYTE)CMD_READ_GAIN_MSB; // Read the Most  Significant Byte.
    command[1] = (BYTE)CMD_READ_GAIN_LSB; // Read the Least Significant Byte.


    write(command);
    waitForReadyRead(100);  // Wati for response.

    gain += Output[0];      // MSB
    gain = gain << 8;       // shift 8 bits (= 1 byte)

    gain += Output[1];      // LSB

    Gain = gain;
}

void CameraPort::readOffset()
{
    QByteArray command;
    int offset = 0;

    command.resize(2);              // The size of the command is 2 byte.
    command[0] = (BYTE)CMD_READ_GAIN_MSB; // Read the Most  Significant Byte.
    command[1] = (BYTE)CMD_READ_GAIN_LSB; // Read the Least Significant Byte.


    write(command);
    waitForReadyRead(100);

    offset += Output[0];    // MSB
    offset = offset << 8;   // shift 8 bits (= 1 byte)
    offset += Output[1];     // LSB

    Offset = offset;
}
/*End of Test*/