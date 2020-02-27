#include "httpmanager.h"

HTTPManager::HTTPManager(QObject *parent) :
    QObject(parent),
    imageDownloadManager(new QNetworkAccessManager)
{
    connect(imageDownloadManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(imageDownloadHandler(QNetworkReply*)));
}

HTTPManager::~HTTPManager()
{
    delete imageDownloadManager;
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

    emit(imageReady(image));
}
