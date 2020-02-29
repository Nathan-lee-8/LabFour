#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      timer(new QTimer),
      httpManager(new HTTPManager)
{
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(setCurrentTime()));
    setCurrentTime();
    timer->start(1000);

    loadImage();

    connect(httpManager, SIGNAL(imageReady(QPixmap *)),
            this, SLOT(processImage(QPixmap *)));

    on_updateWeatherLocation_clicked();

    connect(httpManager,SIGNAL(weatherJsonReady(QJsonObject *)),
            this, SLOT(processWeatherJson(QJsonObject *)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage(){
    QString cowboyFilename = ":/images/cowboy.jpeg";
    if(imageCowboy.load(cowboyFilename)){
        qDebug() << "Image Loaded";
        imageCowboy = imageCowboy.scaled(ui->slideshow_images->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->slideshow_images->setPixmap(imageCowboy);
    QTimer::singleShot(10000,this,SLOT(loadKakashi()));
}

void MainWindow::loadKakashi(){
    QString kakashiFilename = ":/images/hypeKakashi.webp";
    if(imageKakashi.load(kakashiFilename)){
        qDebug() << "Image Loaded";
        imageKakashi = imageKakashi.scaled(ui->slideshow_images->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->slideshow_images->setPixmap(imageKakashi);
    QTimer::singleShot(10000,this,SLOT(loadKillua()));
}

void MainWindow::loadKillua(){
    QString killuaFilename = ":/images/killuaScreen.jpeg";
    if(imageKillua.load(killuaFilename)){
        qDebug() << "Image Loaded";
        imageKillua = imageKillua.scaled(ui->slideshow_images->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->slideshow_images->setPixmap(imageKillua);
    QTimer::singleShot(10000,this,SLOT(loadSteins()));
}

void MainWindow::loadSteins(){
    QString steinsFilename = ":/images/SteinsGate.jpg";
    if(imageSteins.load(steinsFilename)){
        qDebug() << "Image Loaded";
        imageSteins = imageSteins.scaled(ui->slideshow_images->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->slideshow_images->setPixmap(imageSteins);
    QTimer::singleShot(10000,this,SLOT(loadLuffy()));
}

void MainWindow::loadLuffy(){
    QString luffyFilename = ":/images/luffy.jpeg";
    if(imageLuffy.load(luffyFilename)){
        qDebug() << "Image Loaded";
        imageLuffy = imageLuffy.scaled(ui->slideshow_images->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->slideshow_images->setPixmap(imageLuffy);
    QTimer::singleShot(10000,this,SLOT(loadImage()));
}

void MainWindow::setCurrentTime()
{
    QTime time = QTime::currentTime();
    QString hour = time.toString("hh");
    QString minute = time.toString("mm");
    QString second = time.toString("ss");

    int worldHour = (time.hour() + 3) % 23;
    QString hourString = QString::number(worldHour);

    ui->hourValue->display(hour);
    ui->minuteValue->display(minute);
    ui->secondValue->display(second);

    ui->worldHourValue->display(hourString);
    ui->worldMinuteValue->display(minute);
    ui->worldSecondValue->display(second);
}

void MainWindow::processImage(QPixmap *image)
{
    ui->imageLabel->setPixmap(*image);
}

void MainWindow::processWeatherJson(QJsonObject *json)
{
    qDebug() << json->value("weather");
    QString weather = json->value("weather").toArray()[0].toObject()["main"].toString();
    double temp = json->value("main").toObject()["temp"].toDouble();
    double humid = json->value("main").toObject()["humidity"].toDouble();
    ui->weatherLabel->setText("Current Weather: "+ weather + " " + QString::number(temp) +"°F Humidity: " + QString::number(humid));
    if (weather=="Clouds"){
        if(imageClouds.load(":/images/cloud.png")){
            imageClouds = imageClouds.scaled(ui->weatherImages->size(), Qt::KeepAspectRatioByExpanding);
        }
        ui->weatherImages->setPixmap(imageClouds);
    }
    else if (weather=="Rain"){
        if(imageRain.load(":/images/rain.png")){
            imageRain = imageRain.scaled(ui->weatherImages->size(), Qt::KeepAspectRatioByExpanding);
        }
        ui->weatherImages->setPixmap(imageRain);
    }
    else if (weather=="Snow"){
        if(imageSnow.load(":/images/snow.png")){
            imageSnow = imageSnow.scaled(ui->weatherImages->size(), Qt::KeepAspectRatioByExpanding);
        }
        ui->weatherImages->setPixmap(imageSnow);
    }
    else if (weather=="Drizzle"){
        if(imageDrizzle.load(":/images/drizzle.png")){
            imageDrizzle = imageDrizzle.scaled(ui->weatherImages->size(), Qt::KeepAspectRatioByExpanding);
        }
        ui->weatherImages->setPixmap(imageDrizzle);
    }
    else if (weather=="Thunderstorm"){
        if(imageThunder.load(":/images/thunderstorm.png")){
            imageThunder = imageThunder.scaled(ui->weatherImages->size(), Qt::KeepAspectRatioByExpanding);
        }
        ui->weatherImages->setPixmap(imageThunder);
    }
    else {
        if(imageClear.load(":/images/sun.png")){
            imageClear = imageClear.scaled(ui->weatherImages->size(), Qt::KeepAspectRatioByExpanding);
        }
        ui->weatherImages->setPixmap(imageClear);
    }
}

void MainWindow::on_updateWeatherLocation_clicked()
{
    QString zip = ui->zipCodeEdit->text();
    qDebug() << zip;
    httpManager->sendImageRequest(zip);
    httpManager->sendWeatherRequest(zip);
}
