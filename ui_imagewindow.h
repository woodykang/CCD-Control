/********************************************************************************
** Form generated from reading UI file 'imagewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEWINDOW_H
#define UI_IMAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_imageWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *imageLabel;

    void setupUi(QDialog *imageWindow)
    {
        if (imageWindow->objectName().isEmpty())
            imageWindow->setObjectName(QString::fromUtf8("imageWindow"));
        imageWindow->resize(400, 300);
        gridLayout = new QGridLayout(imageWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        imageLabel = new QLabel(imageWindow);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
        imageLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(imageLabel, 0, 0, 1, 1);


        retranslateUi(imageWindow);

        QMetaObject::connectSlotsByName(imageWindow);
    } // setupUi

    void retranslateUi(QDialog *imageWindow)
    {
        imageWindow->setWindowTitle(QCoreApplication::translate("imageWindow", "Dialog", nullptr));
        imageLabel->setText(QCoreApplication::translate("imageWindow", "No image.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class imageWindow: public Ui_imageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEWINDOW_H
