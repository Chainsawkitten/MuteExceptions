#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include "version.h"
#include <QDesktopServices>
#include <QUrl>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog) {
    ui->setupUi(this);

    ui->versionLabel->setText(VERSION);

    connect(ui->websiteButton, SIGNAL(released()), SLOT(goToWebsite()));
}

AboutDialog::~AboutDialog() {
    delete ui;
}

void AboutDialog::goToWebsite() {
    QDesktopServices::openUrl(QUrl("http://muteexceptions.chainsawkitten.net/"));
}
