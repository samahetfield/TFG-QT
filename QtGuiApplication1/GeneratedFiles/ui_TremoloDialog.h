/********************************************************************************
** Form generated from reading UI file 'TremoloDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREMOLODIALOG_H
#define UI_TREMOLODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_TremoloDialog
{
public:
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *pushButton;
    QSpinBox *spinBox;
    QGroupBox *groupBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QDialog *TremoloDialog)
    {
        if (TremoloDialog->objectName().isEmpty())
            TremoloDialog->setObjectName(QStringLiteral("TremoloDialog"));
        TremoloDialog->resize(533, 301);
        comboBox = new QComboBox(TremoloDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(180, 60, 171, 22));
        label = new QLabel(TremoloDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 30, 131, 16));
        pushButton = new QPushButton(TremoloDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 250, 75, 23));
        spinBox = new QSpinBox(TremoloDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(50, 160, 42, 22));
        groupBox = new QGroupBox(TremoloDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(140, 120, 141, 111));
        spinBox_2 = new QSpinBox(groupBox);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(10, 70, 42, 22));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(6);
        spinBox_3 = new QSpinBox(groupBox);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(80, 70, 42, 22));
        spinBox_3->setMinimum(1);
        spinBox_3->setMaximum(6);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 47, 13));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 40, 47, 13));
        groupBox_2 = new QGroupBox(TremoloDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(310, 120, 151, 111));
        spinBox_4 = new QSpinBox(groupBox_2);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setGeometry(QRect(10, 70, 42, 22));
        spinBox_4->setMinimum(1);
        spinBox_4->setMaximum(6);
        spinBox_5 = new QSpinBox(groupBox_2);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setGeometry(QRect(90, 70, 42, 22));
        spinBox_5->setMinimum(1);
        spinBox_5->setMaximum(6);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 40, 47, 13));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(90, 40, 47, 13));
        label_6 = new QLabel(TremoloDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(50, 130, 47, 13));
        groupBox_2->raise();
        groupBox->raise();
        comboBox->raise();
        label->raise();
        pushButton->raise();
        spinBox->raise();
        label_6->raise();

        retranslateUi(TremoloDialog);

        QMetaObject::connectSlotsByName(TremoloDialog);
    } // setupUi

    void retranslateUi(QDialog *TremoloDialog)
    {
        TremoloDialog->setWindowTitle(QApplication::translate("TremoloDialog", "TremoloDialog", Q_NULLPTR));
        label->setText(QApplication::translate("TremoloDialog", "Tipo de Tremolo", Q_NULLPTR));
        pushButton->setText(QApplication::translate("TremoloDialog", "A\303\261adir", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("TremoloDialog", "Velocidades", Q_NULLPTR));
        label_2->setText(QApplication::translate("TremoloDialog", "Inicio", Q_NULLPTR));
        label_3->setText(QApplication::translate("TremoloDialog", "Final", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("TremoloDialog", "Intensidades", Q_NULLPTR));
        label_4->setText(QApplication::translate("TremoloDialog", "Inicio", Q_NULLPTR));
        label_5->setText(QApplication::translate("TremoloDialog", "Final", Q_NULLPTR));
        label_6->setText(QApplication::translate("TremoloDialog", "Longitud", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TremoloDialog: public Ui_TremoloDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREMOLODIALOG_H
