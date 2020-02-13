#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QMessageBox>
#include "imagewindow.h"
#include "CameraControl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    imageWindow *imgWin;
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

    void applySettings();
    void resetSettings();

    void startGrab();
    void stopGrab();

    void imageWindowClosed();

public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
