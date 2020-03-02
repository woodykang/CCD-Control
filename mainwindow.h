#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>
#include "image.h"
#include "CameraControl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // Member Variables
    image img;
    CameraPort *port;
    QString dir;

    bool isConnected;
    bool isGrabbing;

    bool isSingleFrame;
    bool isBurst;

    // Member Functions
    void fillPortsInfo();
    void updateSettings();
    void showErrorMsg(int error);

public:
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

    void modeSingleFrame();
    void modeBurst();

    void saveImage();
};
#endif // MAINWINDOW_H
