#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QThread>
#include "CameraControl.h"
#include "niimaq.h"

namespace Ui {
class imageWindow;
}

class imageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit imageWindow(QWidget *parent = nullptr);
    ~imageWindow();

    void startGrab();
    void stopGrab();
    void imagePlot();
    void grabAndPlot();

    void closeEvent(QCloseEvent* e);

signals:
    void windowClosed();

private:
    Ui::imageWindow *ui;

    int error;

    char intfName[10] = "img0";      // interface name
    INTERFACE_ID Iid = 0;
    SESSION_ID Sid = 0;

    unsigned int AcqWinWidth;       // Acquisition Window Width
    unsigned int AcqWinHeight;      // Acquisition Window Height

    void* imageBuffer;
    void* copiedBuffer;

    unsigned long bufferSize;

    QImage image;
    QThread* thread1;
};

void showError(int error);
void showBox(QString str, int i);

#endif // IMAGEWINDOW_H
