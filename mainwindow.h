#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>
#include "image.h"
#include "CameraPort.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // Private Member Variables
    image img;
    CameraPort *port;
    QString dir;

    bool isConnected;
    bool isGrabbing;

    bool isSingleFrame;
    bool isBurst;

    /*Begin of Test*/
    int captureMode;
    bool isSequence;
    bool isCapturing;
    QTimer sequenceTimer;
    int countIter;
    /*End of Test*/

    // Private Member Functions
    void fillPortsInfo();
    void updateSettings();
    void showErrorMsg(int error);

public:
    // Public Member Fuctions
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    Ui::MainWindow *ui;

private slots:
    void serialConnect();
    void serialDisconnect();

    void applyGain();
    void applyOffset();
    void applyBin();
    void applyIntegTime();
    void applyFrameRate();
    void applyAll();
    void resetSettings();

    void startGrab();
    void stopGrab();

    void setDir();
    void getInputDir();

    void setSingleFrame();
    void setBurst();
    void saveImage();

    /*Begin of Test*/
    void setModeSingle();
    void setModeUnlim();
    void setModeNFrm();
    void setModeSqn();
    void startCapture();
    void cancelCapture();

    void captureEnded();
    /*End of Test*/

    void updateButton();
};
#endif // MAINWINDOW_H
