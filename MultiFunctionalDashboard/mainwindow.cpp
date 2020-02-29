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

    ui->weatherLabel->setText("Current Weather: "+ weather + " Temperature: " + QString::number(temp));
}

void MainWindow::on_updateWeatherLocation_clicked()
{
    QString zip = ui->zipCodeEdit->text();
    qDebug() << zip;
    httpManager->sendImageRequest(zip);
    httpManager->sendWeatherRequest(zip);
}
