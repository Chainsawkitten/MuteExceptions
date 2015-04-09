#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include "version.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog) {
    ui->setupUi(this);

    ui->versionLabel->setText(VERSION);
}

AboutDialog::~AboutDialog() {
    delete ui;
}
