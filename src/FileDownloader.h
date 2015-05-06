#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

/**
 * @brief Downloads files from the Internet.
 */
class FileDownloader : public QObject {
        Q_OBJECT

    public:
        /**
         * @brief Create new file download.
         * @param url URL to the file to download.
         * @param parent Parent widget.
         */
        explicit FileDownloader(QUrl url, QObject *parent = 0);

        /**
         * @brief Get the downloaded data.
         * @return The downloaded data
         */
        QByteArray downloadedData() const;

    signals:
        /**
         * @brief Signal sent when the download has finished.
         */
        void downloaded();

    private slots:
        void fileDownloaded(QNetworkReply* pReply);

    private:
        QNetworkAccessManager webCtrl;
        QByteArray _downloadedData;
};

#endif // FILEDOWNLOADER_H
