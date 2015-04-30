#include "AudioSession.h"
#include <objbase.h>
#include <QSettings>
#include <psapi.h>
#include <QtDebug>

AudioSession::AudioSession(IAudioSessionControl* sessionControl) {
    // Get the extended session control interface pointer.
    IAudioSessionControl2* sessionControl2 = nullptr;
    sessionControl->QueryInterface(__uuidof(IAudioSessionControl2), (void**)&sessionControl2);

    // Get audio volume.
    sessionControl->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&audioVolume);
    audioVolume->GetMute(&wasMuted);

    // Get session identifier.
    LPWSTR displayName;
    sessionControl2->GetDisplayName(&displayName);
    _displayName = QString::fromWCharArray(displayName);

    // Get process id.
    DWORD processId;
    sessionControl2->GetProcessId(&processId);

    // Get process handle.
    HANDLE processHandle;
    processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (processHandle == NULL) {
        qDebug() << "Couldn't open process. Error code: " << GetLastError();
    }

    LPWSTR moduleBaseName = new WCHAR[1000];
    DWORD result = GetModuleBaseNameW(processHandle, NULL, moduleBaseName, 1000);
    if (result == 0) {
        qDebug() << "Couldn't get module base name. Error code: " << GetLastError();
    } else {
        if (_displayName.isEmpty())
            _displayName = QString::fromWCharArray(moduleBaseName);
        else
            _displayName += " (" + QString::fromWCharArray(moduleBaseName) + ")";
    }

    delete[] moduleBaseName;

    CoTaskMemFree(displayName);
    sessionControl2->Release();
}

AudioSession::~AudioSession() {
    QSettings settings;
    settings.beginGroup("AudioSession");

    if (settings.value("resetMute", true).toBool())
        audioVolume->SetMute(wasMuted, NULL);

    settings.endGroup();

    audioVolume->Release();
}

QString AudioSession::displayName() const {
    return _displayName;
}

void AudioSession::mute() const {
    audioVolume->SetMute(TRUE, NULL);
}

void AudioSession::unmute() const {
    audioVolume->SetMute(FALSE, NULL);
}
