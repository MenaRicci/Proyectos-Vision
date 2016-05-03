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
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QFrame *imageFrameS;
    QFrame *imageFrameD;
    QPushButton *captureButton;
    QPushButton *colorButton;
    QPushButton *LoadButton;
    QCheckBox *Check_Corners;
    QFrame *imageFrameS_2;
    QFrame *imageFrameD_2;
    QPushButton *InitButton;
    QPushButton *PropaButton;
    QPushButton *GroundButton;
    QLabel *label;
    QLabel *label_2;
    QLCDNumber *EstimatedLCD;
    QLCDNumber *TrueLCD;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(893, 562);
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
        captureButton->setGeometry(QRect(730, 20, 151, 31));
        captureButton->setCheckable(true);
        captureButton->setChecked(true);
        colorButton = new QPushButton(MainWindow);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));
        colorButton->setGeometry(QRect(730, 60, 151, 31));
        colorButton->setCheckable(true);
        colorButton->setChecked(false);
        LoadButton = new QPushButton(MainWindow);
        LoadButton->setObjectName(QString::fromUtf8("LoadButton"));
        LoadButton->setGeometry(QRect(730, 100, 151, 27));
        Check_Corners = new QCheckBox(MainWindow);
        Check_Corners->setObjectName(QString::fromUtf8("Check_Corners"));
        Check_Corners->setGeometry(QRect(740, 210, 131, 21));
        imageFrameS_2 = new QFrame(MainWindow);
        imageFrameS_2->setObjectName(QString::fromUtf8("imageFrameS_2"));
        imageFrameS_2->setGeometry(QRect(20, 300, 320, 240));
        imageFrameS_2->setFrameShape(QFrame::StyledPanel);
        imageFrameS_2->setFrameShadow(QFrame::Raised);
        imageFrameD_2 = new QFrame(MainWindow);
        imageFrameD_2->setObjectName(QString::fromUtf8("imageFrameD_2"));
        imageFrameD_2->setGeometry(QRect(390, 300, 320, 240));
        imageFrameD_2->setFrameShape(QFrame::StyledPanel);
        imageFrameD_2->setFrameShadow(QFrame::Raised);
        InitButton = new QPushButton(MainWindow);
        InitButton->setObjectName(QString::fromUtf8("InitButton"));
        InitButton->setGeometry(QRect(730, 140, 151, 27));
        PropaButton = new QPushButton(MainWindow);
        PropaButton->setObjectName(QString::fromUtf8("PropaButton"));
        PropaButton->setGeometry(QRect(730, 180, 151, 27));
        PropaButton->setCheckable(true);
        PropaButton->setChecked(false);
        GroundButton = new QPushButton(MainWindow);
        GroundButton->setObjectName(QString::fromUtf8("GroundButton"));
        GroundButton->setGeometry(QRect(730, 320, 151, 27));
        label = new QLabel(MainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(736, 350, 141, 21));
        label_2 = new QLabel(MainWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(760, 421, 101, 20));
        EstimatedLCD = new QLCDNumber(MainWindow);
        EstimatedLCD->setObjectName(QString::fromUtf8("EstimatedLCD"));
        EstimatedLCD->setGeometry(QRect(753, 380, 101, 31));
        TrueLCD = new QLCDNumber(MainWindow);
        TrueLCD->setObjectName(QString::fromUtf8("TrueLCD"));
        TrueLCD->setGeometry(QRect(760, 460, 101, 31));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Proyecto de Visi\303\263n Artificial", 0, QApplication::UnicodeUTF8));
        captureButton->setText(QApplication::translate("MainWindow", "Stop Capture", 0, QApplication::UnicodeUTF8));
        colorButton->setText(QApplication::translate("MainWindow", "Color Image", 0, QApplication::UnicodeUTF8));
        LoadButton->setText(QApplication::translate("MainWindow", "Load File", 0, QApplication::UnicodeUTF8));
        Check_Corners->setText(QApplication::translate("MainWindow", "Show Corners", 0, QApplication::UnicodeUTF8));
        InitButton->setText(QApplication::translate("MainWindow", "Initialize Disparity", 0, QApplication::UnicodeUTF8));
        PropaButton->setText(QApplication::translate("MainWindow", "Propagate Disparity", 0, QApplication::UnicodeUTF8));
        GroundButton->setText(QApplication::translate("MainWindow", "Load Ground Truth", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Estimated disparity", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "True disparity", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
