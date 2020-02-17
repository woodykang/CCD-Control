#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
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
    image img;
    bool isConnected;
    CameraPort *port;

    bool isGrabbing;
    bool isImageWindowOn;

    void fillPortsInfo();
    void showPortInfo(int idx);
    void updateSettings();
    void showErrorMsg(int error);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
