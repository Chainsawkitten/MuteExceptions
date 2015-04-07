#include "AudioSession.h"
#include <objbase.h>

AudioSession::AudioSession(IAudioSessionControl* sessionControl) {
    // Get the extended session control interface pointer.
    IAudioSessionControl2* sessionControl2 = nullptr;
    sessionControl->QueryInterface(__uuidof(IAudioSessionControl2), (void**)&sessionControl2);

    // Get audio volume.
    sessionControl->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&audioVolume);

    // Get session identifier.
    LPWSTR sessionIdentifier;
    sessionControl2->GetSessionIdentifier(&sessionIdentifier);

    _displayName = QString::fromWCharArray(sessionIdentifier);

    CoTaskMemFree(sessionIdentifier);
    sessionControl2->Release();
}

AudioSession::~AudioSession() {
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
