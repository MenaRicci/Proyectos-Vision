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
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QFrame *imageFrameS;
    QFrame *imageFrameD;
    QPushButton *captureButton;
    QPushButton *colorButton;
    QPushButton *AddObjIma;
    QLabel *label;
    QComboBox *SelectComboBox;
    QPushButton *DelObjIma;
    QSlider *horizontalSlider;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(860, 373);
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
        captureButton->setGeometry(QRect(710, 20, 151, 31));
        captureButton->setCheckable(true);
        captureButton->setChecked(true);
        colorButton = new QPushButton(MainWindow);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));
        colorButton->setGeometry(QRect(710, 50, 151, 31));
        colorButton->setCheckable(true);
        colorButton->setChecked(false);
        AddObjIma = new QPushButton(MainWindow);
        AddObjIma->setObjectName(QString::fromUtf8("AddObjIma"));
        AddObjIma->setGeometry(QRect(710, 200, 151, 31));
        AddObjIma->setCheckable(false);
        AddObjIma->setChecked(false);
        AddObjIma->setAutoRepeat(false);
        label = new QLabel(MainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(750, 120, 91, 21));
        SelectComboBox = new QComboBox(MainWindow);
        SelectComboBox->setObjectName(QString::fromUtf8("SelectComboBox"));
        SelectComboBox->setGeometry(QRect(740, 140, 101, 31));
        DelObjIma = new QPushButton(MainWindow);
        DelObjIma->setObjectName(QString::fromUtf8("DelObjIma"));
        DelObjIma->setGeometry(QRect(710, 240, 151, 29));
        horizontalSlider = new QSlider(MainWindow);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(470, 310, 160, 29));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(5);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Proyecto de Visi\303\263n Artificial", 0, QApplication::UnicodeUTF8));
        captureButton->setText(QApplication::translate("MainWindow", "Stop Capture", 0, QApplication::UnicodeUTF8));
        colorButton->setText(QApplication::translate("MainWindow", "Color Image", 0, QApplication::UnicodeUTF8));
        AddObjIma->setText(QApplication::translate("MainWindow", "Add Object Image", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Select Object", 0, QApplication::UnicodeUTF8));
        SelectComboBox->clear();
        SelectComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Obj1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Obj2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Obj3", 0, QApplication::UnicodeUTF8)
        );
        DelObjIma->setText(QApplication::translate("MainWindow", "Del Object Image", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
