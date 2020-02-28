/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLCDNumber *hourValue;
    QLCDNumber *secondValue;
    QLCDNumber *minuteValue;
    QPushButton *imageDisplay;
    QLabel *imageLabel;
    QLineEdit *zipCodeEdit;
    QPushButton *weatherDisplay;
    QLabel *weatherLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(871, 688);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        hourValue = new QLCDNumber(centralwidget);
        hourValue->setObjectName(QString::fromUtf8("hourValue"));
        hourValue->setGeometry(QRect(20, 10, 131, 111));
        hourValue->setDigitCount(2);
        hourValue->setProperty("value", QVariant(22.000000000000000));
        hourValue->setProperty("intValue", QVariant(22));
        secondValue = new QLCDNumber(centralwidget);
        secondValue->setObjectName(QString::fromUtf8("secondValue"));
        secondValue->setGeometry(QRect(300, 10, 141, 111));
        secondValue->setDigitCount(2);
        secondValue->setProperty("value", QVariant(22.000000000000000));
        secondValue->setProperty("intValue", QVariant(22));
        minuteValue = new QLCDNumber(centralwidget);
        minuteValue->setObjectName(QString::fromUtf8("minuteValue"));
        minuteValue->setGeometry(QRect(160, 10, 131, 111));
        minuteValue->setDigitCount(2);
        minuteValue->setProperty("value", QVariant(22.000000000000000));
        minuteValue->setProperty("intValue", QVariant(22));
        imageDisplay = new QPushButton(centralwidget);
        imageDisplay->setObjectName(QString::fromUtf8("imageDisplay"));
        imageDisplay->setGeometry(QRect(30, 140, 113, 32));
        imageLabel = new QLabel(centralwidget);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
        imageLabel->setGeometry(QRect(20, 170, 431, 321));
        zipCodeEdit = new QLineEdit(centralwidget);
        zipCodeEdit->setObjectName(QString::fromUtf8("zipCodeEdit"));
        zipCodeEdit->setGeometry(QRect(160, 140, 113, 21));
        weatherDisplay = new QPushButton(centralwidget);
        weatherDisplay->setObjectName(QString::fromUtf8("weatherDisplay"));
        weatherDisplay->setGeometry(QRect(490, 140, 113, 32));
        weatherLabel = new QLabel(centralwidget);
        weatherLabel->setObjectName(QString::fromUtf8("weatherLabel"));
        weatherLabel->setGeometry(QRect(490, 190, 331, 281));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 871, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        imageDisplay->setText(QApplication::translate("MainWindow", "Image Display", nullptr));
        imageLabel->setText(QString());
        zipCodeEdit->setText(QApplication::translate("MainWindow", "98105", nullptr));
        weatherDisplay->setText(QApplication::translate("MainWindow", "weather display", nullptr));
        weatherLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
