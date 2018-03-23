#pragma once

#include <QDialog>
#include "GeneratedFiles\ui_CalderonDialog.h"

class CalderonDialog : public QDialog
{
	Q_OBJECT

public:
	CalderonDialog(QWidget *parent = Q_NULLPTR);
	~CalderonDialog();

	int getFragmento();
	int getLongitud();
	void setMax(int maxi);

public slots:
	void on_pushButton_clicked();

private:
	Ui::CalderonDialog ui;
	int fragmento;
	int longitud;
};
