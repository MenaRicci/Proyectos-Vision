/********************************************************************************
** Form generated from reading UI file 'pixelTForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIXELTFORM_H
#define UI_PIXELTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_PixelTForm
{
public:
    QSpinBox *origPixelBox1;
    QSpinBox *origPixelBox4;
    QSpinBox *origPixelBox2;
    QSpinBox *origPixelBox3;
    QSpinBox *newPixelBox4;
    QSpinBox *newPixelBox2;
    QSpinBox *newPixelBox3;
    QSpinBox *newPixelBox1;
    QLabel *origLabel;
    QLabel *origLabel_2;
    QPushButton *okButton;
    QComboBox *comboBox;

    void setupUi(QDialog *PixelTForm)
    {
        if (PixelTForm->objectName().isEmpty())
            PixelTForm->setObjectName(QString::fromUtf8("PixelTForm"));
        PixelTForm->resize(511, 272);
        origPixelBox1 = new QSpinBox(PixelTForm);
        origPixelBox1->setObjectName(QString::fromUtf8("origPixelBox1"));
        origPixelBox1->setEnabled(true);
        origPixelBox1->setGeometry(QRect(30, 60, 61, 27));
        origPixelBox1->setReadOnly(true);
        origPixelBox1->setMaximum(255);
        origPixelBox4 = new QSpinBox(PixelTForm);
        origPixelBox4->setObjectName(QString::fromUtf8("origPixelBox4"));
        origPixelBox4->setEnabled(true);
        origPixelBox4->setGeometry(QRect(270, 60, 61, 27));
        origPixelBox4->setReadOnly(true);
        origPixelBox4->setMaximum(255);
        origPixelBox4->setValue(255);
        origPixelBox2 = new QSpinBox(PixelTForm);
        origPixelBox2->setObjectName(QString::fromUtf8("origPixelBox2"));
        origPixelBox2->setEnabled(true);
        origPixelBox2->setGeometry(QRect(110, 60, 61, 27));
        origPixelBox2->setReadOnly(false);
        origPixelBox2->setMaximum(255);
        origPixelBox2->setValue(85);
        origPixelBox3 = new QSpinBox(PixelTForm);
        origPixelBox3->setObjectName(QString::fromUtf8("origPixelBox3"));
        origPixelBox3->setEnabled(true);
        origPixelBox3->setGeometry(QRect(190, 60, 61, 27));
        origPixelBox3->setReadOnly(false);
        origPixelBox3->setMaximum(255);
        origPixelBox3->setValue(170);
        newPixelBox4 = new QSpinBox(PixelTForm);
        newPixelBox4->setObjectName(QString::fromUtf8("newPixelBox4"));
        newPixelBox4->setEnabled(true);
        newPixelBox4->setGeometry(QRect(270, 130, 61, 27));
        newPixelBox4->setReadOnly(false);
        newPixelBox4->setMaximum(255);
        newPixelBox4->setValue(255);
        newPixelBox2 = new QSpinBox(PixelTForm);
        newPixelBox2->setObjectName(QString::fromUtf8("newPixelBox2"));
        newPixelBox2->setEnabled(true);
        newPixelBox2->setGeometry(QRect(110, 130, 61, 27));
        newPixelBox2->setReadOnly(false);
        newPixelBox2->setMaximum(255);
        newPixelBox2->setValue(85);
        newPixelBox3 = new QSpinBox(PixelTForm);
        newPixelBox3->setObjectName(QString::fromUtf8("newPixelBox3"));
        newPixelBox3->setEnabled(true);
        newPixelBox3->setGeometry(QRect(190, 130, 61, 27));
        newPixelBox3->setReadOnly(false);
        newPixelBox3->setMaximum(255);
        newPixelBox3->setValue(170);
        newPixelBox1 = new QSpinBox(PixelTForm);
        newPixelBox1->setObjectName(QString::fromUtf8("newPixelBox1"));
        newPixelBox1->setEnabled(true);
        newPixelBox1->setGeometry(QRect(30, 130, 61, 27));
        newPixelBox1->setReadOnly(false);
        newPixelBox1->setMaximum(255);
        origLabel = new QLabel(PixelTForm);
        origLabel->setObjectName(QString::fromUtf8("origLabel"));
        origLabel->setGeometry(QRect(110, 20, 161, 21));
        origLabel->setTextFormat(Qt::RichText);
        origLabel_2 = new QLabel(PixelTForm);
        origLabel_2->setObjectName(QString::fromUtf8("origLabel_2"));
        origLabel_2->setGeometry(QRect(120, 100, 131, 21));
        origLabel_2->setTextFormat(Qt::RichText);
        okButton = new QPushButton(PixelTForm);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(130, 190, 98, 27));
        comboBox = new QComboBox(PixelTForm);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(370, 60, 121, 31));

        retranslateUi(PixelTForm);

        QMetaObject::connectSlotsByName(PixelTForm);
    } // setupUi

    void retranslateUi(QDialog *PixelTForm)
    {
        PixelTForm->setWindowTitle(QApplication::translate("PixelTForm", "Set pixel transformation", 0, QApplication::UnicodeUTF8));
        origLabel->setText(QApplication::translate("PixelTForm", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Original pixel value</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        origLabel_2->setText(QApplication::translate("PixelTForm", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">New pixel value</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("PixelTForm", "Ok", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("PixelTForm", "Personalizado", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PixelTForm", "Identidad", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PixelTForm", "Negativo", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PixelTForm", "Logaritmo", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class PixelTForm: public Ui_PixelTForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIXELTFORM_H
