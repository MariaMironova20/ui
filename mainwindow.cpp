#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QButtonGroup>
#include <QProgressBar>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Группы кнопок (без изменений)
    QButtonGroup *group1 = new QButtonGroup(this);
    group1->setExclusive(true);
    group1->addButton(ui->pushButton_1, 1);
    group1->addButton(ui->pushButton_2, 2);
    group1->addButton(ui->pushButton_3, 3);
    ui->pushButton_1->setChecked(true);

    QButtonGroup *group2 = new QButtonGroup(this);
    group2->setExclusive(true);
    group2->addButton(ui->pushButton_4, 1);
    group2->addButton(ui->pushButton_5, 2);
    group2->addButton(ui->pushButton_6, 3);
    ui->pushButton_4->setChecked(true);

    // Стиль кнопок (круглые с градиентом)
    setStyleSheet(
        "QPushButton {"
        "    border-radius: 10px;"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #f0f0f0, stop:1 #d0d0d0);"
        "    min-width: 90px;"
        "    min-height: 40px;"
        "    font: bold 16px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #e0e0e0, stop:1 #c0c0c0);"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #d0d0d0, stop:1 #b0b0b0);"
        "}"
        "QPushButton:checked {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #b0d0ff, stop:1 #6080ff);"
        "    color: white;"
        "}"
        );

    // Настройка ProgressBar (батарея)
    ui->progressBar->setRange(0, 10);
    ui->progressBar->setValue(5);

    // Таймер для автоматического обновления
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        static int val = 5;
        val = (val + 1) % 11; // 0..10
        updateBatteryIndicator(ui->progressBar, val);
    });
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBatteryIndicator(QProgressBar *bar, int value)
{
    bar->setValue(value);

    QString style;
    if (value < 3) {
        style = "QProgressBar {"
                "    border: 2px solid silver;"
                "    border-radius: 5px;"
                "    text-align: center;"
                "    color: black;"
                "    font-weight: bold;"
                "}"
                "QProgressBar::chunk {"
                "    background-color: red;"
                "    border-radius: 3px;"
                "}";
        bar->setFormat(" %p%  Замените батарею!");
    } else if (value <= 6) {
        style = "QProgressBar {"
                "    border: 2px solid silver;"
                "    border-radius: 5px;"
                "    text-align: center;"
                "    color: black;"
                "    font-weight: bold;"
                "}"
                "QProgressBar::chunk {"
                "    background-color: orange;"
                "    border-radius: 3px;"
                "}";
        bar->setFormat(" %p%");
    } else {
        style = "QProgressBar {"
                "    border: 2px solid silver;"
                "    border-radius: 5px;"
                "    text-align: center;"
                "    color: white;"
                "    font-weight: bold;"
                "}"
                "QProgressBar::chunk {"
                "    background-color: green;"
                "    border-radius: 3px;"
                "}";
        bar->setFormat(" %p%");
    }

    bar->setStyleSheet(style);
}
