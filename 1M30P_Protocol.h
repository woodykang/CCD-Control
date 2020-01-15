#ifndef CAMERACONTROLSIGNAL_H
#define CAMERACONTROLSIGNAL_H

/***********************************************************************
 *  Using DALSA 1M30P.
 *  Refer to the CCD manual for detailed information.
 *
 *  1. Serial Port Configuration
 *      1) Baud       : 9600, fixed
 *      2) Start Bits : 1
 *      3) Data  Bits : 8
 *      4) Stop  Bits : 1
 *      5) Parity     : None
 *
 *      All commands are 8-bits (= 1 byte).
 *      Write commands should be followed by 8-bit
 *      data byte. (Except for 2 commands)
 *
 *  2. Read Camera Type
 *      Read Command  : 0xC3 = 1100 0011
 *      Should return : 0x41             (for 1M30P)
 *
 *  3. Reset ADC Boards ("Soft" Reset)
 *      Write Command : 0x00
 *      NO DATA BYTE NEEDED
 *
 *  4. Reset Camera     ("Hard" Reset)
 *      Write Command : 0x80
 *      NO DATA BYTE NEEDED
 *
 *  5. Adjust Gain
 *      Value = 32768 * log10(Gain)
 *      1 <= Gain <= 10
 *
 *      Convert Value into hexadecimal, which will be 4 digits.
 *      1 byte for MSB Write (0x06), COMMAND BYTE
 *      1 byte for MSB of Value,     DATA    BYTE
 *      1 byte for LSB Write (0x05), COMMAND BYTE
 *      1 byte for LSB of Value      DATA    BYTE
 *
 *      cf) MSB : Most  Significant Byte
 *          LSB : Least Significant Byte
 *
 *  6. Read Gain
 *      Read MSB : 0x46
 *      Read LSB : 0x45
 *
 *  7. Adjust Offset
 *      Value = 8 * Offset/Gain
 *      -4095 <= Offset <= 4095
 *
 *      Convert Value into hex, which will be 4 digits.
 *      1 byte for MSB Write (0x03), COMMAND BYTE
 *      1 byte for MSB of Value,     DATA    BYTE
 *      1 byte for LSB Write (0x02), COMMAND BYTE
 *      1 byte for LSB of Value      DATA    BYTE
 *
 *  8. Read Offset
 *      Read MSB : 0x43
 *      Read LSB : 0x42
 *
 *  9. Setting Binning Mode
 *      Write Command : 0x85
 *
 *      0x1 : binned X1 (unbinned)
 *      0x2 : binned X2
 *      0x4 : binned X4
 *      0x0 : binned X8
 *
 *      e.g. horizontal : X2 = 0x2 = 0010, vertical : X4 = 0x4 = 0100
 *      -> Value = 0100 0010
 *
 *  10. Setting Integration Time
 *      !! IMPORTANT !!
 *          1) Integration time  <  [1/fps - (transfer time)].
 *             A safe value for the transfer time is 
 *             2160 microseconds regardless of the binning.
 *             Refer to the manual for detailed information.
 *          2) Integration time > 5 microseconds.
 *          3) Default Integration Time : 31.221 ms
 * 
 *      1) Convert the desired integration time in microseconds.
 *      2) Convert it into hexadecimal.
 *      
 *      LS     Byte Write Command : 0x8A
 *      Center Byte Write Command : 0x8B
 *      MS     Byte Write Command : 0x8C
 * 
 *  11. Setting Frame Rate
 *      !! IMPORTANT !!
 *          1) Make sure the frame rate satisfies the integration
 *             time constraint.
 *          2) Minimum of 1/(frame rate) is 5 microseconds.
 *          3) Default Frame Rate : 30fps
 * 
 *      1) Input value is 1/(frame rate) in microseconds.
 *      2) Convert the value into hexadecimal.
 *
 *      LS     Byte Write Command : 0x8D
 *      Center Byte Write Command : 0x8E
 *      MS     Byte Write Command : 0x8F
 * 
 *      Maximum Frame Rate for Binning Mode :
 * 
 *  Vertical Binning  |  Max Frame Rate
 * --------------------------------------
 *           1x       |     30
 *           2x       |     54
 *           4x       |     88
 *           8x       |    129
 *
*****************************************************************/


#define CMD_READ_CAMERA_TYPE    0xC3    // Read  Command Camera Type
#define CMD_RESET_ADC           0x00    // Write Command Reset ADC 
#define CMD_RESET_CAMERA        0x80    // Write Command Reset Camera
#define CMD_WRITE_GAIN_MSB      0x06    // Write Command Gain MSB
#define CMD_WRITE_GAIN_LSB      0x05    // Write Command Gain LSB
#define CMD_READ_GAIN_MSB       0x46    // Read  Command Gain MSB 
#define CMD_READ_GAIN_LSB       0x45    // Read  Command Gain LSB
#define CMD_WRITE_OFFSET_MSB    0x03    // Write Command Offset MSB
#define CMD_WRITE_OFFSET_LSB    0x02    // Write Command Offset LSB
#define CMD_READ_OFFSET_MSB     0X43    // Read  Command Offset MSB
#define CMD_READ_OFFSET_LSB     0X42    // Read  Command Offset LSB
#define CMD_WRITE_BINNING       0x85    // Write Command Offset Binning
#define CMD_WRITE_INTG_MSB      0x8C    // Write Command Integration Time MSB
#define CMD_WRITE_INTG_2SB      0x8B    // Write Command Integration Time 2SB   (2SB = 2nd Significant Byte) 
#define CMD_WRITE_INTG_LSB      0x8A    // Write Command Integration Time LSB
#define CMD_WRITE_FPS_MSB       0x8F    // Write Command Frame Rate MSB
#define CMD_WRITE_FPS_2SB       0x8E    // Write Command Frame Rate 2SB
#define CMD_WRITE_FPS_LSB       0x8D    // Write Command Frame Rate LSB

#define FACTOR_GAIN             32768   // Factor multiplied to the log10(Gain)
#define FACTOR_OFFSET           8       // Factor multiplied to Offset/Gain

#endif // CAMERACONTROLSIGNAL_H
