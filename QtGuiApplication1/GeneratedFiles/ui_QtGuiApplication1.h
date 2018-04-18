/********************************************************************************
** Form generated from reading UI file 'QtGuiApplication1.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIAPPLICATION1_H
#define UI_QTGUIAPPLICATION1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiApplication1Class
{
public:
    QAction *actionAbrir_Partitura;
    QAction *actionSalir;
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QPushButton *button_nota;
    QPushButton *button_tremolo;
    QPushButton *button_silencio;
    QPushButton *button_calderon;
    QPushButton *play;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QTableWidget *tableWidget;
    QPushButton *nueva_voz;
    QSpinBox *tempoBox;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menuArchivo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiApplication1Class)
    {
        if (QtGuiApplication1Class->objectName().isEmpty())
            QtGuiApplication1Class->setObjectName(QStringLiteral("QtGuiApplication1Class"));
        QtGuiApplication1Class->resize(956, 669);
        actionAbrir_Partitura = new QAction(QtGuiApplication1Class);
        actionAbrir_Partitura->setObjectName(QStringLiteral("actionAbrir_Partitura"));
        actionSalir = new QAction(QtGuiApplication1Class);
        actionSalir->setObjectName(QStringLiteral("actionSalir"));
        centralWidget = new QWidget(QtGuiApplication1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(410, 160, 61, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(350, 230, 181, 51));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(260, 180, 361, 21));
        button_nota = new QPushButton(centralWidget);
        button_nota->setObjectName(QStringLiteral("button_nota"));
        button_nota->setGeometry(QRect(120, 40, 111, 91));
        button_tremolo = new QPushButton(centralWidget);
        button_tremolo->setObjectName(QStringLiteral("button_tremolo"));
        button_tremolo->setGeometry(QRect(310, 40, 101, 91));
        button_silencio = new QPushButton(centralWidget);
        button_silencio->setObjectName(QStringLiteral("button_silencio"));
        button_silencio->setGeometry(QRect(490, 40, 101, 91));
        button_calderon = new QPushButton(centralWidget);
        button_calderon->setObjectName(QStringLiteral("button_calderon"));
        button_calderon->setGeometry(QRect(680, 40, 101, 91));
        play = new QPushButton(centralWidget);
        play->setObjectName(QStringLiteral("play"));
        play->setGeometry(QRect(380, 550, 131, 51));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 280, 911, 271));
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tableWidget = new QTableWidget(tab_2);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 885, 230));
        tabWidget->addTab(tab_2, QString());
        nueva_voz = new QPushButton(centralWidget);
        nueva_voz->setObjectName(QStringLiteral("nueva_voz"));
        nueva_voz->setGeometry(QRect(10, 560, 75, 23));
        tempoBox = new QSpinBox(centralWidget);
        tempoBox->setObjectName(QStringLiteral("tempoBox"));
        tempoBox->setGeometry(QRect(750, 250, 81, 21));
        tempoBox->setMinimum(30);
        tempoBox->setMaximum(300);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(750, 230, 71, 16));
        QtGuiApplication1Class->setCentralWidget(centralWidget);
        tabWidget->raise();
        label->raise();
        pushButton->raise();
        comboBox->raise();
        button_nota->raise();
        button_tremolo->raise();
        button_silencio->raise();
        button_calderon->raise();
        play->raise();
        nueva_voz->raise();
        tempoBox->raise();
        label_2->raise();
        menuBar = new QMenuBar(QtGuiApplication1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 956, 21));
        menuArchivo = new QMenu(menuBar);
        menuArchivo->setObjectName(QStringLiteral("menuArchivo"));
        QtGuiApplication1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiApplication1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtGuiApplication1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiApplication1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtGuiApplication1Class->setStatusBar(statusBar);

        menuBar->addAction(menuArchivo->menuAction());
        menuArchivo->addAction(actionAbrir_Partitura);
        menuArchivo->addAction(actionSalir);

        retranslateUi(QtGuiApplication1Class);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QtGuiApplication1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiApplication1Class)
    {
        QtGuiApplication1Class->setWindowTitle(QApplication::translate("QtGuiApplication1Class", "QtGuiApplication1", Q_NULLPTR));
        actionAbrir_Partitura->setText(QApplication::translate("QtGuiApplication1Class", "Abrir Partitura", Q_NULLPTR));
        actionSalir->setText(QApplication::translate("QtGuiApplication1Class", "Salir", Q_NULLPTR));
        label->setText(QApplication::translate("QtGuiApplication1Class", "Instrumento", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QtGuiApplication1Class", "A\303\261adir", Q_NULLPTR));
        button_nota->setText(QApplication::translate("QtGuiApplication1Class", "Nota", Q_NULLPTR));
        button_tremolo->setText(QApplication::translate("QtGuiApplication1Class", "Tremolo", Q_NULLPTR));
        button_silencio->setText(QApplication::translate("QtGuiApplication1Class", "Silencio", Q_NULLPTR));
        button_calderon->setText(QApplication::translate("QtGuiApplication1Class", "Calder\303\263n", Q_NULLPTR));
        play->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QtGuiApplication1Class", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QtGuiApplication1Class", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QtGuiApplication1Class", "3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QtGuiApplication1Class", "4", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QtGuiApplication1Class", "5", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("QtGuiApplication1Class", "6", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QtGuiApplication1Class", "Voz", Q_NULLPTR));
        nueva_voz->setText(QApplication::translate("QtGuiApplication1Class", "Nueva voz", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtGuiApplication1Class", "Tempo (bpm)", Q_NULLPTR));
        menuArchivo->setTitle(QApplication::translate("QtGuiApplication1Class", "Archivo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiApplication1Class: public Ui_QtGuiApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPPLICATION1_H
