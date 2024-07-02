#include "MainWindow.h"
#include "qpainter.h"
#include "ui_MainWindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), backgroundImage("b.jpg") {
    ui->setupUi(this);
    ui->wheel->setMarcador(ui->marcador);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw background
    painter.drawPixmap(0, 0, width(), height(), backgroundImage);
}

