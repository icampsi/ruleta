/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TimerDialog;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event) override;

private:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    // MENU
    // App
    void on_actionProperties_triggered();
    void on_actionNewGroup_triggered();
    void on_actionDeleteGroup_triggered();

    // Window
    void on_actionFullScreen_triggered(bool checked);
    void on_actionTimer_triggered();

private:
    Ui::MainWindow *ui;
    QPixmap backgroundImage;
    TimerDialog *timerDialog;
};

#endif // MAINWINDOW_H
