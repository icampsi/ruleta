/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#include "MarcLbl.h"
#include "ui_MarcLbl.h"

#include <QFont>
#include <QRandomGenerator>
#include <QColor>

MarcLbl::MarcLbl(QWidget *parent)
    : QWidget{parent}, ui(new Ui::MarcLbl) {
    ui->setupUi(this);

    double luminance = 0;
    int red, green, blue;
    do {
        // Generate random colors
        red     = QRandomGenerator::global()->bounded(256);
        green   = QRandomGenerator::global()->bounded(256);
        blue    = QRandomGenerator::global()->bounded(256);

        luminance = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
    } while (luminance < 120);

    // Random Color stylesheet
    QString widgetColorString = QString("QFrame#frame_2 { background-color: rgba(%1, %2, %3, %4); }").arg(red)
              .arg(green)
              .arg(blue)
              .arg(128);

    setStyleSheet(widgetColorString);

    // Text color
    QString labelTextColor = QString("color: %1;").arg("white");
    ui->label_name->setStyleSheet(labelTextColor);
    ui->label_score->setStyleSheet(labelTextColor);

    // Font
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    ui->label_name->setFont(font);
    ui->label_score->setFont(font);

    // Color '+' and '-' buttons
    ui->pushButton_add->setStyleSheet("QPushButton { background-color: rgba(0, 255, 0, 255); }");
    ui->pushButton_subs->setStyleSheet("QPushButton { background-color: rgba(255, 0, 0, 255); }");
    updateScore();
}


void MarcLbl::updateScore() {
    ui->label_score->setText(QString::number(m_score));
}

void MarcLbl::on_pushButton_add_clicked() {
    ++m_score;
    updateScore();
}


void MarcLbl::on_pushButton_subs_clicked() {
    --m_score;
    updateScore();
}

void MarcLbl::setName(const QString& name) {
    ui->label_name->setText(name);
}

