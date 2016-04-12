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
    QCheckBox *Check_Border;
    QCheckBox *Check_Statistics;
    QCheckBox *Check_Merge;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(860, 285);
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
        colorButton->setGeometry(QRect(710, 70, 151, 31));
        colorButton->setCheckable(true);
        colorButton->setChecked(false);
        LoadButton = new QPushButton(MainWindow);
        LoadButton->setObjectName(QString::fromUtf8("LoadButton"));
        LoadButton->setGeometry(QRect(710, 120, 151, 27));
        Check_Border = new QCheckBox(MainWindow);
        Check_Border->setObjectName(QString::fromUtf8("Check_Border"));
        Check_Border->setGeometry(QRect(720, 160, 97, 22));
        Check_Statistics = new QCheckBox(MainWindow);
        Check_Statistics->setObjectName(QString::fromUtf8("Check_Statistics"));
        Check_Statistics->setGeometry(QRect(720, 200, 97, 22));
        Check_Merge = new QCheckBox(MainWindow);
        Check_Merge->setObjectName(QString::fromUtf8("Check_Merge"));
        Check_Merge->setGeometry(QRect(720, 240, 97, 22));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Proyecto de Visi\303\263n Artificial", 0, QApplication::UnicodeUTF8));
        captureButton->setText(QApplication::translate("MainWindow", "Stop Capture", 0, QApplication::UnicodeUTF8));
        colorButton->setText(QApplication::translate("MainWindow", "Color Image", 0, QApplication::UnicodeUTF8));
        LoadButton->setText(QApplication::translate("MainWindow", "Load File", 0, QApplication::UnicodeUTF8));
        Check_Border->setText(QApplication::translate("MainWindow", "Draw Borders", 0, QApplication::UnicodeUTF8));
        Check_Statistics->setText(QApplication::translate("MainWindow", "Use statistics", 0, QApplication::UnicodeUTF8));
        Check_Merge->setText(QApplication::translate("MainWindow", "Merge", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
