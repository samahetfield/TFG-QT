#include <QDialog>
#include "GeneratedFiles\\ui_NotaDialog.h"

class NotaDialog : public QDialog
{
	Q_OBJECT

public:
	NotaDialog(QWidget *parent = Q_NULLPTR);
	~NotaDialog();

	int getIntensidad();

	int getNodo();

public slots:
	void on_pushButton_clicked();

private:
	Ui::NotaDialog ui;
	int intensidad;
	int nodo;
};
