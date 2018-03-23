/********************************************************************************
** Form generated from reading UI file 'CalderonDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALDERONDIALOG_H
#define UI_CALDERONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CalderonDialog
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;

    void setupUi(QDialog *CalderonDialog)
    {
        if (CalderonDialog->objectName().isEmpty())
            CalderonDialog->setObjectName(QStringLiteral("CalderonDialog"));
        CalderonDialog->resize(502, 359);
        pushButton = new QPushButton(CalderonDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(200, 280, 75, 23));
        label = new QLabel(CalderonDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 60, 161, 21));
        label_2 = new QLabel(CalderonDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(330, 60, 41, 21));
        spinBox = new QSpinBox(CalderonDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(110, 110, 81, 22));
        spinBox_2 = new QSpinBox(CalderonDialog);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(330, 110, 42, 22));

        retranslateUi(CalderonDialog);

        QMetaObject::connectSlotsByName(CalderonDialog);
    } // setupUi

    void retranslateUi(QDialog *CalderonDialog)
    {
        CalderonDialog->setWindowTitle(QApplication::translate("CalderonDialog", "CalderonDialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CalderonDialog", "Aceptar", Q_NULLPTR));
        label->setText(QApplication::translate("CalderonDialog", "Fragmento de partitura a repetir", Q_NULLPTR));
        label_2->setText(QApplication::translate("CalderonDialog", "Duraci\303\263n", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CalderonDialog: public Ui_CalderonDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALDERONDIALOG_H
