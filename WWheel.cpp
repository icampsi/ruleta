#include "WWheel.h"
#include "qevent.h"
#include "ui_WWheel.h"
#include "dialog.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include <QRandomGenerator>

#include <QAudioOutput>

WWheel::WWheel(QWidget *parent) :
    QWidget(parent), ui(new Ui::WWheel), rotationAngle(0), rotationDuration(50), wheelImage("r.png")
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WWheel::updateRotation);

    spinButton = new QPushButton("GIRA LA RODA!", this);
    connect(spinButton, &QPushButton::clicked, this, &WWheel::spin);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // spacer
    mainLayout->addStretch();
    mainLayout->addWidget(spinButton);
    setLayout(mainLayout);

    spinPlayer = new QMediaPlayer(this);
    stopPlayer = new QMediaPlayer(this);


    m_spinAudioOut = new QAudioOutput;
    spinPlayer->setAudioOutput(m_spinAudioOut);
    spinPlayer->setSource(QUrl::fromLocalFile("circus.mp3"));
    m_spinAudioOut->setVolume(80);

    m_stopAudioOut = new QAudioOutput;
    stopPlayer->setAudioOutput(m_stopAudioOut);
    stopPlayer->setSource(QUrl::fromLocalFile("end.mp3"));
    m_stopAudioOut->setVolume(80);

}

void WWheel::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_M) {
        Dialog dialog;  // Create an instance of your dialog
        dialog.setModal(true);  // Set the dialog to modal mode
        connect(&dialog, &Dialog::accepted, this, [&dialog, this] { marcador->addLabel(dialog.getText()); } );
        dialog.exec();  // Show the dialog modally
    }else if(event->key() == Qt::Key_R) {
        marcador->deleteLbl();
    } else {
        QWidget::keyPressEvent(event);  // Handle other key events normally
    }
}


WWheel::~WWheel() {
    delete ui;
    delete m_spinAudioOut;
}

void WWheel::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();
    int side = qMin(w, h);

    // Draw wheel
    painter.translate(w / 2, h / 2);
    painter.scale(side / static_cast<double>(wheelImage.width()), side / static_cast<double>(wheelImage.height()));
    painter.rotate(rotationAngle);
    painter.drawPixmap(-wheelImage.width() / 2, -wheelImage.height() / 2, wheelImage);

    // Reset transformation for drawing the arrow
    painter.resetTransform();
    drawArrow(painter);
}

void WWheel::drawArrow(QPainter &painter) {
    int w = width();
    int h = height();
    int side = qMin(w, h);

    painter.translate(w / 2, h / 2);
    painter.setBrush(Qt::red);
    QPolygon arrow;
    arrow << QPoint(15, -side / 2) << QPoint(-15, -side / 2) << QPoint(0, -side / 2 + 80);
    painter.drawPolygon(arrow);
}

void WWheel::spin() {
    timerTime = QRandomGenerator::global()->bounded(22, 50);
    qDebug() << "duration: " << timerTime;
    timer->start(timerTime);
    m_spinAudioOut->setVolume(80);
    spinPlayer->play();
    speed = QRandomGenerator::global()->bounded(40, 145);
    qDebug() << "speed: " << speed;
}

void WWheel::updateRotation() {
    rotationAngle += speed;

    if(speed == 2) {
        fadeOut(m_spinAudioOut);
    }
    if (speed > 0) {
        if (speed < 50 && speed >= 30) {
            if(slow == 0) {
                speed -= 1;
                slow = 2;
            }
            else {
                slow--;
            }
        }else if (speed < 30 && speed >= 20) {
            if(slow == 0) {
                speed -= 1;
                slow = 4;
            }
            else {
                slow--;
            }
        } else if (speed < 20 && speed >= 5) {
            if(slow == 0) {
                speed -= 1;
                slow = 6;
            }
            else {
                slow--;
            }
        } else if (speed < 5 && speed > 0) {
            if(slow == 0) {
                speed -= 1;
                slow = 12;
            }
            else {
                slow--;
            }
        }
        else {
            speed--;
        }
    } else {
        stopPlayer->play();
        timer->stop();
    }
    update();
}

void WWheel::fadeOut(QAudioOutput *output) {
    double vol = output->volume();
    QTimer *t = new QTimer(this);

    connect(t, &QTimer::timeout, this, [=]() mutable {
        // Decrease volume
        vol -= 0.01;
        if (vol <= 0) {
            vol = 0;
            t->stop();
            output->setVolume(vol);
            spinPlayer->stop();
            t->deleteLater();
        } else {
            output->setVolume(vol);
        }
    });

    t->start(25);
}

