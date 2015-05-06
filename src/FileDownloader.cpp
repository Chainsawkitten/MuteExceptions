#include "FileDownloader.h"

FileDownloader::FileDownloader(QUrl url, QObject *parent) : QObject(parent) {
    connect(&webCtrl, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(url);
    webCtrl.get(request);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
    _downloadedData = pReply->readAll();
    // Emit a signal
    pReply->deleteLater();
    emit downloaded();
}

QByteArray FileDownloader::downloadedData() const {
    return _downloadedData;
}
