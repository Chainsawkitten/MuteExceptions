#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::writeSettings() {
    QSettings settings;

    settings.beginGroup("AudioSession");
    settings.setValue("resetMute", ui->resetMuteCheckBox->isChecked());
    settings.endGroup();

    settings.beginGroup("Updates");
    settings.setValue("checkOnStart", ui->updateCheckBox->isChecked());
}

void SettingsDialog::readSettings() {
    QSettings settings;

    settings.beginGroup("AudioSession");
    ui->resetMuteCheckBox->setChecked(settings.value("resetMute", true).toBool());
    settings.endGroup();

    settings.beginGroup("Updates");
    ui->updateCheckBox->setChecked(settings.value("checkOnStart", true).toBool());
    settings.endGroup();
}
