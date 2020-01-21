#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QMessageBox>
#include "CameraControl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    bool cameraConnected;
    CameraPort *port;

    void fillPortsInfo();
    void showPortInfo(int idx);
    void updateSettings();

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

public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
