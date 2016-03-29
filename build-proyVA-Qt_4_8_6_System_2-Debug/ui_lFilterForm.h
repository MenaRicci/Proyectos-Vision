/********************************************************************************
** Form generated from reading UI file 'lFilterForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LFILTERFORM_H
#define UI_LFILTERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_LFilterForm
{
public:
    QPushButton *okButton;
    QLabel *label;
    QDoubleSpinBox *kernelBox12;
    QDoubleSpinBox *kernelBox13;
    QDoubleSpinBox *kernelBox22;
    QDoubleSpinBox *kernelBox23;
    QDoubleSpinBox *kernelBox21;
    QDoubleSpinBox *kernelBox33;
    QDoubleSpinBox *kernelBox32;
    QDoubleSpinBox *kernelBox31;
    QDoubleSpinBox *kernelBox11;
    QLabel *label_2;
    QSpinBox *addedVBox;

    void setupUi(QDialog *LFilterForm)
    {
        if (LFilterForm->objectName().isEmpty())
            LFilterForm->setObjectName(QString::fromUtf8("LFilterForm"));
        LFilterForm->resize(342, 231);
        okButton = new QPushButton(LFilterForm);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(120, 180, 91, 31));
        label = new QLabel(LFilterForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 20, 57, 15));
        kernelBox12 = new QDoubleSpinBox(LFilterForm);
        kernelBox12->setObjectName(QString::fromUtf8("kernelBox12"));
        kernelBox12->setGeometry(QRect(90, 40, 51, 41));
        kernelBox12->setAlignment(Qt::AlignCenter);
        kernelBox12->setButtonSymbols(QAbstractSpinBox::NoButtons);
        kernelBox12->setMinimum(-99.99);
        kernelBox12->setValue(0);
        kernelBox13 = new QDoubleSpinBox(LFilterForm);
        kernelBox13->setObjectName(QString::fromUtf8("kernelBox13"));
        kernelBox13->setGeometry(QRect(140, 40, 51, 41));
        kernelBox13->setAlignment(Qt::AlignCenter);
        kernelBox13->setButtonSymbols(QAbstractSpinBox::NoButtons);
        kernelBox13->setMinimum(-99.99);
        kernelBox13->setValue(0);
        kernelBox22 = new QDoubleSpinBox(LFilterForm);
        kernelBox22->setObjectName(QString::fromUtf8("kernelBox22"));
        kernelBox22->setGeometry(QRect(90, 80, 51, 41));
        kernelBox22->setAlignment(Qt::AlignCenter);
        kernelBox22->setButtonSymbols(QAbstractSpinBox::NoButtons);
        kernelBox22->setMinimum(-99.99);
        kernelBox22->setValue(1);
        kernelBox23 = new QDoubleSpinBox(LFilterForm);
        kernelBox23->setObjectName(QString::fromUtf8("kernelBox23"));
        kernelBox23->setGeometry(QRect(140, 80, 51, 41));
        kernelBox23->setAlignment(Qt::AlignCenter);
        kernelBox23->setButtonSymbols(QAbstractSpinBox::NoButtons);
        kernelBox23->setMinimum(-99.99);
        kernelBox23->setValue(0);
        kernelBox21 = new QDoubleSpinBox(LFilterForm);
        kernelBox21->setObjectName(QString::fromUtf8("kernelBox21"));
        kernelBox21->setGeometry(QRect(40, 80, 51, 41));
        kernelBox21->setAlignment(Qt::AlignCenter);
        kernelBox21->setButtonSymbols(QAbstractSpinBox::NoButtons);
        kernelBox21->setMinimum(-99.99);
        kernelBox21->setValue(0);
        kernelBox33 = new QDoubleSpinBox(LFilterForm);
        kernelBox33->setObjectName(QString::fromUtf8("kernelBox33"));
        kernelBox33->setGeometry(QRect(140, 120, 51, 41));
        kernelBox33->setAlignment(Qt::AlignCenter);
        kernelBox33->setButtonSymbols(QAbstractSpinBox::NoButtons);
        kernelBox33->setMinimum(-99.99);
        kernelBox33->setValue(0);
        kernelBox32 = new QDoubleSpinBox(LFilterForm);
        kernelBox32->setObjectName(QString::fromUtf8("kernelBox32"));
        kernelBox32->setGeometry(QRect(90, 120, 51, 41));
        kernelBox32->setAlignment(Qt::AlignCenter);
        kernelBox32->setButtonSymbols(QAbstractSpinBox::NoButtons);
        kernelBox32->setMinimum(-99.99);
        kernelBox32->setValue(0);
        kernelBox31 = new QDoubleSpinBox(LFilterForm);
        kernelBox31->setObjectName(QString::fromUtf8("kernelBox31"));
        kernelBox31->setGeometry(QRect(40, 120, 51, 41));
        kernelBox31->setAlignment(Qt::AlignCenter);
        kernelBox31->setButtonSymbols(QAbstractSpinBox::NoButtons);
        kernelBox31->setMinimum(-99.99);
        kernelBox31->setValue(0);
        kernelBox11 = new QDoubleSpinBox(LFilterForm);
        kernelBox11->setObjectName(QString::fromUtf8("kernelBox11"));
        kernelBox11->setGeometry(QRect(40, 40, 51, 41));
        kernelBox11->setAlignment(Qt::AlignCenter);
        kernelBox11->setButtonSymbols(QAbstractSpinBox::NoButtons);
        kernelBox11->setMinimum(-99.99);
        kernelBox11->setValue(0);
        label_2 = new QLabel(LFilterForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 50, 91, 16));
        addedVBox = new QSpinBox(LFilterForm);
        addedVBox->setObjectName(QString::fromUtf8("addedVBox"));
        addedVBox->setGeometry(QRect(230, 80, 61, 41));
        addedVBox->setMaximum(255);

        retranslateUi(LFilterForm);

        QMetaObject::connectSlotsByName(LFilterForm);
    } // setupUi

    void retranslateUi(QDialog *LFilterForm)
    {
        LFilterForm->setWindowTitle(QApplication::translate("LFilterForm", "Set kernel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("LFilterForm", "Ok", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LFilterForm", "<html><head/><body><p><span style=\" font-weight:600;\">Kernel</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("LFilterForm", "<html><head/><body><p><span style=\" font-weight:600;\">Added value</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LFilterForm: public Ui_LFilterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LFILTERFORM_H
