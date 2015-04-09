#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    createStatusBar();
    connect(ui->addExceptionButton, SIGNAL(released()), SLOT(addException()));
    connect(ui->removeExceptionButton, SIGNAL(released()), SLOT(removeException()));
    connect(ui->applyButton, SIGNAL(released()), SLOT(apply()));
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(about()));

    aboutDialog = new AboutDialog(this);

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    initAudio();
    getAudioSessions();
}

MainWindow::~MainWindow() {
    delete ui;
    delete statusLabel;
    delete aboutDialog;

    for (AudioSession* audioSession : mutedSessions) {
        delete audioSession;
    }

    for (AudioSession* audioSession : exceptedSessions) {
        delete audioSession;
    }

    audioSessionManager->Release();
    speakers->Release();
    deviceEnumerator->Release();
    CoUninitialize();
}

void MainWindow::addException() {
    if (!mutedSessions.empty()) {
        int index = ui->mutedListWidget->currentRow();
        if (index >= 0) {
            AudioSession* session = mutedSessions.at(index);
            exceptedSessions.push_back(session);
            ui->exceptionsListWidget->addItem(session->displayName());
            mutedSessions.removeAt(index);
            delete ui->mutedListWidget->currentItem();
            statusLabel->setText("Added exception.");
        }
    }
}

void MainWindow::removeException() {
    if (!exceptedSessions.empty()) {
        int index = ui->exceptionsListWidget->currentRow();
        if (index >= 0) {
            AudioSession* session = exceptedSessions.at(index);
            mutedSessions.push_back(session);
            ui->mutedListWidget->addItem(session->displayName());
            exceptedSessions.removeAt(index);
            delete ui->exceptionsListWidget->currentItem();
            statusLabel->setText("Removed exception.");
        }
    }
}

void MainWindow::apply() {
    // Mute all muted.
    for (AudioSession* session : mutedSessions) {
        session->mute();
    }

    // Unmute all exceptions.
    for (AudioSession* session : exceptedSessions) {
        session->unmute();
    }

    statusLabel->setText("Muting applied.");
}

void MainWindow::about() {
    aboutDialog->show();
}

void MainWindow::createStatusBar() {
    statusLabel = new QLabel("Started.");
    statusBar()->addWidget(statusLabel);
}

void MainWindow::initAudio() {
    // Create device enumerator.
    HRESULT result = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&deviceEnumerator);
    if (result != S_OK) {
        statusLabel->setText("Couldn't create device enumerator.");
        return;
    }

    // Get speakers.
    result = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &speakers);
    if (result != S_OK) {
        statusLabel->setText("Couldn't get default audio endpoint.");
        return;
    }

    // Get session manager.
    result = speakers->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, nullptr, (void**)&audioSessionManager);
    if (result != S_OK) {
        statusLabel->setText("Couldn't activate audio session manager.");
        return;
    }
}

void MainWindow::getAudioSessions() {
    // Get session enumerator.
    IAudioSessionEnumerator* sessionEnumerator = nullptr;
    HRESULT result = audioSessionManager->GetSessionEnumerator(&sessionEnumerator);
    if (result != S_OK) {
        statusLabel->setText("Couldn't get audio session enumerator.");
        return;
    }

    // Get sessions.
    int sessionCount;
    sessionEnumerator->GetCount(&sessionCount);
    for (int i=0; i<sessionCount; i++) {
        IAudioSessionControl* sessionControl = nullptr;
        sessionEnumerator->GetSession(i, &sessionControl);

        AudioSession* audioSession = new AudioSession(sessionControl);
        mutedSessions.push_back(audioSession);
        ui->mutedListWidget->addItem(audioSession->displayName());

        sessionControl->Release();
    }

    sessionEnumerator->Release();
}
