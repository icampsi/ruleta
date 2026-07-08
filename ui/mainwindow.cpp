/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#include "mainwindow.h"
#include "ui/timerdialog.h"
#include "ui/dialog.h"
#include "ui/propertiesdialog.h"
#include "ui_mainwindow.h"

#include <QPainter.h>
#include <QKeyEvent>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), backgroundImage(":/images/b.jpg"), timerDialog{nullptr} {
    ui->setupUi(this);
    ui->wheel->setMarcador(ui->marcador);

    this->setWindowTitle("Ruleta");

    // Setup menu actions
    ui->actionFullScreen->setShortcut(QKeySequence(Qt::Key_F11));

    auto timerShortcut = new QShortcut(QKeySequence(Qt::Key_T), this);
    timerShortcut->setContext(Qt::ApplicationShortcut);
    connect(timerShortcut, &QShortcut::activated, ui->actionTimer, &QAction::trigger);

    auto newGroupShortcut = new QShortcut(QKeySequence(Qt::Key_M), this);
    newGroupShortcut->setContext(Qt::ApplicationShortcut);
    connect(newGroupShortcut, &QShortcut::activated, ui->actionNewGroup, &QAction::trigger);

    auto deleteGroupShortcut = new QShortcut(QKeySequence(Qt::Key_R), this);
    deleteGroupShortcut->setContext(Qt::ApplicationShortcut);
    connect(deleteGroupShortcut, &QShortcut::activated, ui->actionDeleteGroup, &QAction::trigger);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // Draw background
    QPainter painter(this);
    painter.drawPixmap(rect(), backgroundImage);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) { // Exit full screen
        if(isFullScreen()) {
            showMaximized();
            menuBar()->show();
        }
    }
    if (event->key() == Qt::Key_F11) { // Go full screen
        if(!isFullScreen()) {
            showFullScreen();
            menuBar()->hide();
            ui->actionFullScreen->setChecked(true);
        } else {
            showMaximized();
            menuBar()->show();
            ui->actionFullScreen->setChecked(false);
        }
    }
    else QWidget::keyPressEvent(event);

}

void MainWindow::on_actionProperties_triggered()
{
    PropertiesDialog propertiesDlg(this);

    if(propertiesDlg.exec() == QDialog::Accepted) {
        QString bgImage = propertiesDlg.getBackgroundImagePath();
        if(!bgImage.isEmpty()) {
            backgroundImage.load(bgImage);
            update();
        }
        QString rouletteImage = propertiesDlg.getRoulettImagePath();
        if(!rouletteImage.isEmpty()) {
            ui->wheel->changeRouletteImage(rouletteImage);
        }
        QString spinAudio = propertiesDlg.getSpinningAudioPath();
        if(!spinAudio.isEmpty()) {
            ui->wheel->changeSpinnAudio(spinAudio);
        }
        QString endAudio = propertiesDlg.getEndingAudioPath();
        if(!endAudio.isEmpty()) {
            ui->wheel->changeEndAudio(endAudio);
        }
    }
}

void MainWindow::on_actionNewGroup_triggered()
{
    Dialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        ui->wheel->addNewLabel(dialog.getText());
    }
}

void MainWindow::on_actionDeleteGroup_triggered()
{
     ui->wheel->deleteLbl();
}

void MainWindow::on_actionFullScreen_triggered(bool checked)
{
    menuBar()->setVisible(!checked);

    if (checked)
        showFullScreen();
    else
        showMaximized();
}

void MainWindow::on_actionTimer_triggered()
{
    if (timerDialog) {
        timerDialog->close();
        return;
    }

    timerDialog = new TimerDialog(this);
    timerDialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(timerDialog, &QObject::destroyed, this, [this]() {
        timerDialog = nullptr;
    });

    timerDialog->show();
}

