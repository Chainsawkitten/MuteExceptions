#ifndef AUDIOSESSION
#define AUDIOSESSION

#include <QString>

#include <Audioclient.h>
#include <audiopolicy.h>

/**
 * @brief An audio session that can be muted or excepted.
 */
class AudioSession {
    public:
        /**
         * @brief Create new audio session.
         * @param Session control object retrieved from the Core Audio API.
         */
        AudioSession(IAudioSessionControl* sessionControl);

        /**
         * @brief Free allocated resources.
         */
        ~AudioSession();

        /**
         * @brief Get display name.
         * @return Display name
         */
        QString displayName() const;

        /**
         * @brief Mute the audio session.
         */
        void mute() const;

        /**
         * @brief Unmute the audio session.
         */
        void unmute() const;

    private:
        ISimpleAudioVolume* audioVolume;
        QString _displayName;
};

#endif // AUDIOSESSION

