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

void HTTPManager::sendImageRequest()
{
    QNetworkRequest request;
    request.setUrl(QUrl(""));
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
