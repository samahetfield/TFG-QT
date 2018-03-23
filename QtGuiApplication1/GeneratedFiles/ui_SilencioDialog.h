/********************************************************************************
** Form generated from reading UI file 'SilencioDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SILENCIODIALOG_H
#define UI_SILENCIODIALOG_H

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

class Ui_SilencioDialog
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QSpinBox *spinBox;

    void setupUi(QDialog *SilencioDialog)
    {
        if (SilencioDialog->objectName().isEmpty())
            SilencioDialog->setObjectName(QStringLiteral("SilencioDialog"));
        SilencioDialog->resize(400, 300);
        pushButton = new QPushButton(SilencioDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(160, 240, 75, 23));
        label = new QLabel(SilencioDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(176, 70, 51, 20));
        spinBox = new QSpinBox(SilencioDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(170, 110, 61, 22));

        retranslateUi(SilencioDialog);

        QMetaObject::connectSlotsByName(SilencioDialog);
    } // setupUi

    void retranslateUi(QDialog *SilencioDialog)
    {
        SilencioDialog->setWindowTitle(QApplication::translate("SilencioDialog", "SilencioDialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SilencioDialog", "Aceptar", Q_NULLPTR));
        label->setText(QApplication::translate("SilencioDialog", "Duraci\303\263n", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SilencioDialog: public Ui_SilencioDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SILENCIODIALOG_H
