#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
    class AboutDialog;
}

/**
 * @brief Dialog displaying information about the program.
 */
class AboutDialog : public QDialog {
        Q_OBJECT

    public:
        /**
         * @brief Create new AboutDialog.
         * @param parent Parent widget.
         */
        explicit AboutDialog(QWidget *parent = 0);

        /**
         * @brief Free allocated resources.
         */
        ~AboutDialog();

    public slots:
        /**
         * @brief Open website in default web browser.
         */
        void goToWebsite();

        /**
         * @brief Open GitHub repository in default web browser.
         */
        void goToGithub();

    private:
        Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
