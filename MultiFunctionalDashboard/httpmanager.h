#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

class HTTPManager : public QObject
{
    Q_OBJECT
public:
    explicit HTTPManager(QObject *parent = nullptr);
    ~HTTPManager();

    void sendImageRequest(QString zip);
    void sendWeatherRequest(QString zip);

signals:
    void imageReady(QPixmap *image);
    void weatherJsonReady(QJsonObject *json);

private slots:
    void imageDownloadHandler(QNetworkReply *reply);
    void weatherDownloadHandler(QNetworkReply *reply);

private:
    QNetworkAccessManager *imageDownloadManager;
    QNetworkAccessManager *weatherAPIManager;
    QByteArray downloadedData;
};

#endif // HTTPMANAGER_H
