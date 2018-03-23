#pragma once

#include <QDialog>
#include "ui_SilencioDialog.h"

class SilencioDialog : public QDialog
{
	Q_OBJECT

public:
	SilencioDialog(QWidget *parent = Q_NULLPTR);
	~SilencioDialog();

	int getLongitud();

public slots:
	void on_pushButton_clicked();


private:
	Ui::SilencioDialog ui;
	int longitud;
};
