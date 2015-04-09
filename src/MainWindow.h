#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QList>

#include <objbase.h>
#include <mmdeviceapi.h>
#include <audiopolicy.h>

#include "AudioSession.h"
#include "AboutDialog.h"

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
         * @brief Show about dialog.
         * @see AboutDialog
         */
        void about();

    private:
        Ui::MainWindow *ui;
        QLabel* statusLabel;
        AboutDialog* aboutDialog;

        IMMDeviceEnumerator* deviceEnumerator = nullptr;
        IMMDevice* speakers = nullptr;
        IAudioSessionManager2* audioSessionManager = nullptr;

        QList<AudioSession*> mutedSessions;
        QList<AudioSession*> exceptedSessions;

        void createStatusBar();
        void initAudio();
        void getAudioSessions();
};

#endif // MAINWINDOW_H
