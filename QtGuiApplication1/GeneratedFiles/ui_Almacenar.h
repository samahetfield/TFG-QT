/********************************************************************************
** Form generated from reading UI file 'Almacenar.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALMACENAR_H
#define UI_ALMACENAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Almacenar
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *Almacenar)
    {
        if (Almacenar->objectName().isEmpty())
            Almacenar->setObjectName(QStringLiteral("Almacenar"));
        Almacenar->resize(390, 213);
        label = new QLabel(Almacenar);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 50, 251, 16));
        lineEdit = new QLineEdit(Almacenar);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 90, 221, 21));
        pushButton = new QPushButton(Almacenar);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 140, 75, 23));

        retranslateUi(Almacenar);

        QMetaObject::connectSlotsByName(Almacenar);
    } // setupUi

    void retranslateUi(QWidget *Almacenar)
    {
        Almacenar->setWindowTitle(QApplication::translate("Almacenar", "Almacenar", Q_NULLPTR));
        label->setText(QApplication::translate("Almacenar", "Elegir ubicaci\303\263n para almacenar el archivo MIDI", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Almacenar", "Guardar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Almacenar: public Ui_Almacenar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALMACENAR_H
