#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class SettingsDialog;
}

/**
 * @brief Dialog allowing user to alter the application's settings.
 */
class SettingsDialog : public QDialog {
        Q_OBJECT

    public:
        /**
         * @brief Create new SettingsDialog.
         * @param parent Parent widget.
         */
        explicit SettingsDialog(QWidget *parent = 0);

        /**
         * @brief Free allocated resources.
         */
        ~SettingsDialog();

        /**
         * @brief Store settings.
         */
        void writeSettings();

        /**
         * @brief Read settings.
         */
        void readSettings();

    private:
        Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
