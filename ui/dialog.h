/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui { class Dialog; }

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    const QString getText();
private:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
