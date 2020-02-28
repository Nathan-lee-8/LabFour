#include "httpmanager.h"
#include <QJsonDocument>
#include <QJsonObject>

HTTPManager::HTTPManager(QObject *parent) :
    QObject(parent),
    imageDownloadManager(new QNetworkAccessManager),
    weatherAPIManager(new QNetworkAccessManager)
{
    connect(imageDownloadManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(imageDownloadHandler(QNetworkReply*)));
    connect(weatherAPIManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(weatherDownloadHandler(QNetworkReply*)));
}

HTTPManager::~HTTPManager()
{
    delete imageDownloadManager;
    delete weatherAPIManager;
}

void HTTPManager::sendImageRequest(QString zip)
{
    QNetworkRequest request;
    QString address = "https://dev.virtualearth.net/REST/V1/Imagery/Map/AerialWithLabels/"
            + zip + "/5?mapSize=600,300&mapLayer=TrafficFlow&format=png&key=Aqsbh-mlBoEhcpDYZe5VgE9PVOzFxXa9jU6uTY1gICTdslwrmLvCIN_yFdRrbWMO";

    request.setUrl(QUrl(address));
    imageDownloadManager->get(request);
    qDebug() << "Image request sent" << request.url();
}

void HTTPManager::sendWeatherRequest(QString zip)
{
    QNetworkRequest request;
    QString address = "https://api.openweathermap.org/data/2.5/weather?zip="
            + zip + ",us&units=imperial&appid=7ce34c6516c32b240f11f71392af7fd3";
    request.setUrl(QUrl(address));
    weatherAPIManager->get(request);
    qDebug() << "Weather request sent" << request.url();
}

void HTTPManager::imageDownloadHandler(QNetworkReply *reply)
{
    qDebug() << "Image reply arrived";
    if(reply->error()){
        qDebug() << reply->errorString();
        return;
    }
    qDebug() << "Download was successful";
    QPixmap *image = new QPixmap();
    image->loadFromData(reply->readAll());
    reply->deleteLater();

    emit(imageReady(image));
}

void HTTPManager::weatherDownloadHandler(QNetworkReply *reply)
{
    qDebug() << "Weather reply arrived";
    if(reply->error()){
        qDebug() << reply->errorString();
        return;
    }
    qDebug() <<"YEEEEET";
    QString answer = reply->readAll();
    reply->deleteLater();

    QJsonDocument JsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject *jsonObj = new QJsonObject(JsonResponse.object());

    emit weatherJsonReady(jsonObj);
}
