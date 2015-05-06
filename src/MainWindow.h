#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QList>

#include <objbase.h>
#include <mmdeviceapi.h>
#include <audiopolicy.h>

#include "AudioSession.h"
#include "SettingsDialog.h"
#include "AboutDialog.h"
#include "FileDownloader.h"

namespace Ui {
    class MainWindow;
}

/**
 * @brief Main window of the application.
 */
class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        /**
         * @brief Create new MainWindow.
         * @param parent Parent widget.
         */
        explicit MainWindow(QWidget *parent = 0);

        /**
         * @brief Free allocated resources.
         */
        ~MainWindow();

    public slots:
        /**
         * @brief Add selected audio session to the exceptions.
         */
        void addException();

        /**
         * @brief Remove selected audio session from the exceptions.
         */
        void removeException();

        /**
         * @brief Apply muting/unmuting.
         */
        void apply();

        /**
         * @brief Open settings dialog.
         * @see SettingsDialog
         */
        void settings();

        /**
         * @brief Check for updates.
         */
        void checkUpdates();

        /**
         * @brief Show about dialog.
         * @see AboutDialog
         */
        void about();

        /**
         * @brief Check if available version is newer than current version.
         */
        void versionDownloaded();

    private:
        Ui::MainWindow *ui;
        QLabel* statusLabel;
        SettingsDialog* settingsDialog;
        AboutDialog* aboutDialog;

        IMMDeviceEnumerator* deviceEnumerator = nullptr;
        IMMDevice* speakers = nullptr;
        IAudioSessionManager2* audioSessionManager = nullptr;

        QList<AudioSession*> mutedSessions;
        QList<AudioSession*> exceptedSessions;

        FileDownloader* fileDownloader;

        void createStatusBar();
        void initAudio();
        void getAudioSessions();
        void writeSettings();
        void readSettings();
};

#endif // MAINWINDOW_H
