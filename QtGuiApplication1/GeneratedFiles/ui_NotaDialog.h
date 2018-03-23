/********************************************************************************
** Form generated from reading UI file 'NotaDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTADIALOG_H
#define UI_NOTADIALOG_H

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

class Ui_NotaDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QPushButton *pushButton;

    void setupUi(QDialog *NotaDialog)
    {
        if (NotaDialog->objectName().isEmpty())
            NotaDialog->setObjectName(QStringLiteral("NotaDialog"));
        NotaDialog->resize(301, 233);
        label = new QLabel(NotaDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 51, 16));
        label_2 = new QLabel(NotaDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(180, 40, 47, 16));
        spinBox = new QSpinBox(NotaDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(60, 80, 61, 22));
        spinBox->setMaximum(127);
        spinBox_2 = new QSpinBox(NotaDialog);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(180, 80, 42, 22));
        spinBox_2->setMaximum(5);
        pushButton = new QPushButton(NotaDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 150, 75, 23));

        retranslateUi(NotaDialog);

        QMetaObject::connectSlotsByName(NotaDialog);
    } // setupUi

    void retranslateUi(QDialog *NotaDialog)
    {
        NotaDialog->setWindowTitle(QApplication::translate("NotaDialog", "NotaDialog", Q_NULLPTR));
        label->setText(QApplication::translate("NotaDialog", "Intensidad", Q_NULLPTR));
        label_2->setText(QApplication::translate("NotaDialog", "Nodo", Q_NULLPTR));
        pushButton->setText(QApplication::translate("NotaDialog", "Aceptar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NotaDialog: public Ui_NotaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTADIALOG_H
