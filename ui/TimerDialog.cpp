#include "TimerDialog.h"
#include "ui/ui_TimerDialog.h"

#include <QKeyEvent>

TimerDialog::TimerDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TimerDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);

    // Remove frame and make it blend in
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

TimerDialog::~TimerDialog()
{
    delete ui;
}

void TimerDialog::keyPressEvent(QKeyEvent *event) {
if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_T) {
        close();
    } else {
        QWidget::keyPressEvent(event);
    }
}
