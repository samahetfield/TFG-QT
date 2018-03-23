#include "CalderonDialog.h"

CalderonDialog::CalderonDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

}

CalderonDialog::~CalderonDialog()
{
}



void CalderonDialog::on_pushButton_clicked() {
	fragmento = ui.spinBox->value();
	longitud = ui.spinBox_2->value();

	close();
}


int CalderonDialog::getFragmento() {
	return fragmento;
}

int CalderonDialog::getLongitud() {
	return longitud;
}

void CalderonDialog::setMax(int maxi) {
	ui.spinBox->setMaximum(maxi);
}
