/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QFrame *imageFrameS;
    QFrame *imageFrameD;
    QPushButton *captureButton;
    QPushButton *colorButton;
    QPushButton *loadButton;
    QFrame *processingFrame;
    QComboBox *operationComboBox;
    QLabel *operationLabel;
    QLabel *gaussianLabel;
    QSpinBox *thresholdSpinBox;
    QLabel *gaussianLabel_2;
    QPushButton *kernelButton;
    QPushButton *operOrderButton;
    QPushButton *pixelTButton;
    QSpinBox *gaussWidthBox;
    QPushButton *saveButton;
    QCheckBox *Ori_checkHisogram;
    QCheckBox *Dest_checkHistogram;
    QLabel *label;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(860, 398);
        imageFrameS = new QFrame(MainWindow);
        imageFrameS->setObjectName(QString::fromUtf8("imageFrameS"));
        imageFrameS->setGeometry(QRect(20, 20, 320, 240));
        imageFrameS->setFrameShape(QFrame::StyledPanel);
        imageFrameS->setFrameShadow(QFrame::Raised);
        imageFrameD = new QFrame(MainWindow);
        imageFrameD->setObjectName(QString::fromUtf8("imageFrameD"));
        imageFrameD->setGeometry(QRect(390, 20, 320, 240));
        imageFrameD->setFrameShape(QFrame::StyledPanel);
        imageFrameD->setFrameShadow(QFrame::Raised);
        captureButton = new QPushButton(MainWindow);
        captureButton->setObjectName(QString::fromUtf8("captureButton"));
        captureButton->setGeometry(QRect(740, 20, 101, 31));
        captureButton->setCheckable(true);
        captureButton->setChecked(true);
        colorButton = new QPushButton(MainWindow);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));
        colorButton->setGeometry(QRect(740, 60, 101, 31));
        colorButton->setCheckable(true);
        colorButton->setChecked(false);
        loadButton = new QPushButton(MainWindow);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(740, 100, 101, 31));
        loadButton->setCheckable(false);
        loadButton->setChecked(false);
        processingFrame = new QFrame(MainWindow);
        processingFrame->setObjectName(QString::fromUtf8("processingFrame"));
        processingFrame->setGeometry(QRect(20, 290, 831, 91));
        processingFrame->setFrameShape(QFrame::StyledPanel);
        processingFrame->setFrameShadow(QFrame::Raised);
        operationComboBox = new QComboBox(processingFrame);
        operationComboBox->setObjectName(QString::fromUtf8("operationComboBox"));
        operationComboBox->setGeometry(QRect(10, 50, 161, 27));
        operationLabel = new QLabel(processingFrame);
        operationLabel->setObjectName(QString::fromUtf8("operationLabel"));
        operationLabel->setGeometry(QRect(30, 30, 121, 17));
        gaussianLabel = new QLabel(processingFrame);
        gaussianLabel->setObjectName(QString::fromUtf8("gaussianLabel"));
        gaussianLabel->setGeometry(QRect(170, 30, 111, 17));
        thresholdSpinBox = new QSpinBox(processingFrame);
        thresholdSpinBox->setObjectName(QString::fromUtf8("thresholdSpinBox"));
        thresholdSpinBox->setGeometry(QRect(290, 50, 60, 27));
        thresholdSpinBox->setMaximum(255);
        thresholdSpinBox->setValue(120);
        gaussianLabel_2 = new QLabel(processingFrame);
        gaussianLabel_2->setObjectName(QString::fromUtf8("gaussianLabel_2"));
        gaussianLabel_2->setGeometry(QRect(280, 30, 81, 17));
        kernelButton = new QPushButton(processingFrame);
        kernelButton->setObjectName(QString::fromUtf8("kernelButton"));
        kernelButton->setGeometry(QRect(550, 40, 111, 41));
        operOrderButton = new QPushButton(processingFrame);
        operOrderButton->setObjectName(QString::fromUtf8("operOrderButton"));
        operOrderButton->setGeometry(QRect(660, 40, 161, 41));
        pixelTButton = new QPushButton(processingFrame);
        pixelTButton->setObjectName(QString::fromUtf8("pixelTButton"));
        pixelTButton->setGeometry(QRect(370, 40, 181, 41));
        gaussWidthBox = new QSpinBox(processingFrame);
        gaussWidthBox->setObjectName(QString::fromUtf8("gaussWidthBox"));
        gaussWidthBox->setGeometry(QRect(200, 50, 60, 27));
        gaussWidthBox->setMinimum(3);
        gaussWidthBox->setMaximum(19);
        gaussWidthBox->setSingleStep(2);
        gaussWidthBox->setValue(3);
        saveButton = new QPushButton(MainWindow);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(740, 140, 101, 31));
        saveButton->setCheckable(false);
        saveButton->setChecked(false);
        Ori_checkHisogram = new QCheckBox(MainWindow);
        Ori_checkHisogram->setObjectName(QString::fromUtf8("Ori_checkHisogram"));
        Ori_checkHisogram->setGeometry(QRect(100, 260, 96, 26));
        Dest_checkHistogram = new QCheckBox(MainWindow);
        Dest_checkHistogram->setObjectName(QString::fromUtf8("Dest_checkHistogram"));
        Dest_checkHistogram->setGeometry(QRect(510, 260, 96, 26));
        label = new QLabel(MainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 270, 221, 31));
        label->setAutoFillBackground(true);
        label->setTextFormat(Qt::RichText);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Proyecto de Visi\303\263n Artificial", 0, QApplication::UnicodeUTF8));
        captureButton->setText(QApplication::translate("MainWindow", "Stop Capture", 0, QApplication::UnicodeUTF8));
        colorButton->setText(QApplication::translate("MainWindow", "Color Image", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("MainWindow", "Load Image", 0, QApplication::UnicodeUTF8));
        operationComboBox->clear();
        operationComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Transform pixel", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Thresholding", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Equalize", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Gaussian Blur", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Median Blur", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Linear Filter", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Dilate", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Erode", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Apply several...", 0, QApplication::UnicodeUTF8)
        );
        operationLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Select operation</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        gaussianLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Gaussian width</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        gaussianLabel_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Threshold</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        kernelButton->setText(QApplication::translate("MainWindow", "Set Kernel", 0, QApplication::UnicodeUTF8));
        operOrderButton->setText(QApplication::translate("MainWindow", "Set Operation Order", 0, QApplication::UnicodeUTF8));
        pixelTButton->setText(QApplication::translate("MainWindow", "Set Pixel Transformation", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("MainWindow", "Save Image", 0, QApplication::UnicodeUTF8));
        Ori_checkHisogram->setText(QApplication::translate("MainWindow", "Histogram", 0, QApplication::UnicodeUTF8));
        Dest_checkHistogram->setText(QApplication::translate("MainWindow", "Histogram", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:600;\">Image Processing</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
