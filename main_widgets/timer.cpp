/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#include "timer.h"
#include "ui/ui_timer.h"


Timer::Timer(QWidget *parent)
    : QWidget(parent), ui(new Ui::Timer), m_timer(this), m_duration{10000}, m_elapsedTime{0}
{
    ui->setupUi(this);

    setStyleSheet("background-color: #f0f0f0;");

    ui->lcdDisplay->setDigitCount(8);
    ui->lcdDisplay->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdDisplay->display("00:00:00:00");
    ui->lcdDisplay->setStyleSheet("background-color: black; color: green; padding: 10px;");

    // Push button styles with hover and click effects
    ui->frame->setStyleSheet("QPushButton {"
                                        "color: white;"
                                        "padding: 10px;"
                                        "font-size: 18px;"
                                        "border-radius: 5px;"
                                        "}"
                             );
    ui->pushButton_start->setStyleSheet("QPushButton { background-color: #4CAF50; }"
                                        "QPushButton:hover { background-color: #45a049; }"
                                        "QPushButton:pressed { background-color: #398438; }"
                                        );

    ui->pushButton_stop->setStyleSheet("QPushButton { background-color: #f44336; }"
                                       "QPushButton:hover { background-color: #d32f2f; }"
                                       "QPushButton:pressed { background-color: #b71c1c; }"
                                       );

    ui->pushButton_reset->setStyleSheet("QPushButton { background-color: #008CBA; }"
                                        "QPushButton:hover { background-color: #0077A3; }"
                                        "QPushButton:pressed { background-color: #005F87; }"
                                        );


    connect(&m_timer, &QTimer::timeout, this, &Timer::updateTime);
    connect(ui->pushButton_start, &QPushButton::clicked, this, &Timer::startTimer);
    connect(ui->pushButton_stop , &QPushButton::clicked, this, &Timer::stopTimer);
    connect(ui->pushButton_reset, &QPushButton::clicked, this, &Timer::resetTimer);
}

Timer::~Timer() {
    delete ui;
}


void Timer::resetTimer() {
    m_timer.stop();
    m_elapsedTime = 0;
    ui->lcdDisplay->display("00:00:00:00");
}

void Timer::updateTime() {
    m_elapsedTime++;
    int minutes = (m_elapsedTime % 360000) / 6000;
    int seconds = (m_elapsedTime % 6000) / 100;
    int mils    = m_elapsedTime % 100;

    ui->lcdDisplay->display(QString::asprintf("%02d:%02d:%02d", minutes, seconds, mils));
}
