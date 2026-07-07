/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#include "dialog.h"
#include "ui_dialog.h"
#include <qevent.h>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Afegir grup nou");
    setFixedSize(460, 240);

    setStyleSheet(R"(
        QDialog {
            background-color: #fff1a8;
        }

        QLabel {
            color: #2b1600;
            font-size: 18px;
            font-weight: bold;
        }

        QLineEdit {
            background-color: white;
            color: #222;
            border: 3px solid #b00000;
            border-radius: 12px;
            padding: 8px 12px;
            font-size: 20px;
        }

        QLineEdit:focus {
            border: 3px solid #ffcc00;
        }

        QPushButton {
            background-color: #ffcc00;
            color: #2b1600;
            border: 3px solid #b00000;
            border-radius: 14px;
            padding: 8px 24px;
            font-size: 17px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #ffe066;
        }

        QPushButton:pressed {
            background-color: #f77f00;
        }
    )");

    ui->lineEdit->setFocus();
}

Dialog::~Dialog() { delete ui; }

const QString Dialog::getText() { return ui->lineEdit->text(); }

void Dialog::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) { // Close dialog
        reject();
    }
    else QDialog::keyPressEvent(event);

}

