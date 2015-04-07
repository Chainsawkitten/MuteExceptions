#ifndef AUDIOSESSION
#define AUDIOSESSION

#include <QString>

#include <Audioclient.h>
#include <audiopolicy.h>

class AudioSession {
    public:
        AudioSession(IAudioSessionControl* sessionControl);
        ~AudioSession();

        QString displayName() const;

        void mute() const;
        void unmute() const;

    private:
        ISimpleAudioVolume* audioVolume;
        QString _displayName;
};

#endif // AUDIOSESSION

