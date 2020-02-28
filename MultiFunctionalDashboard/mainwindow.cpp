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

void MainWindow::setCurrentTime()
{
    QTime time = QTime::currentTime();
    QString hour = time.toString("hh");
    QString minute = time.toString("mm");
    QString second = time.toString("ss");

    ui->hourValue->display(hour);
    ui->minuteValue->display(minute);
    ui->secondValue->display(second);
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
