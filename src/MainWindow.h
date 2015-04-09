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

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void addException();
        void removeException();
        void apply();
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
