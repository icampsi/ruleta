/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#include "WWheel.h"

#include "ui_WWheel.h"

#include <QEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QRandomGenerator>
#include <QAudioOutput>
#include <QPainterPath>
#include <QPushButton>
#include <QMediaplayer>
#include <QGridLayout>

WWheel::WWheel(QWidget *parent) :
    QWidget(parent), ui(new Ui::WWheel), m_rotationAngle(0), m_rotationDuration(50), m_wheelImage(":/images/r.png")
{
    ui->setupUi(this);

    // Timer
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &WWheel::updateRotation);


    {   // UI
        QGridLayout *mainLayout = new QGridLayout(this);
        mainLayout->setContentsMargins(24, 24, 24, 24);
        mainLayout->setSpacing(0);

        // Spin button
        m_spinButton = new QPushButton("GIRA LA RODA!", this);
        m_spinButton->setCursor(Qt::PointingHandCursor);
        m_spinButton->setMinimumSize(190, 54);

        QFont spinFont = m_spinButton->font();
        spinFont.setPointSize(15);
        spinFont.setBold(true);
        m_spinButton->setFont(spinFont);

        m_spinButton->setStyleSheet(R"(
            QPushButton {
                background-color: #FFD21F;
                color: #5A1200;

                border: 4px solid #B51616;
                border-radius: 16px;

                padding: 10px 22px;

                font-weight: bold;
                letter-spacing: 1px;
            }

            QPushButton:hover {
                background-color: #FFE45C;
                border: 4px solid #E02020;
            }

            QPushButton:pressed {
                background-color: #E8B900;
                border: 4px solid #7A0C0C;
                padding-top: 13px;
                padding-left: 24px;
            }

            QPushButton:disabled {
                background-color: #999999;
                color: #555555;
                border: 4px solid #666666;
            }
        )");

        connect(m_spinButton, &QPushButton::clicked, this, [this]() {
            if (!m_timer->isActive()) {
                spin();
            } else {
                stopWheel();
            }
        });

        mainLayout->addWidget(m_spinButton, 0, 0, Qt::AlignTop | Qt::AlignLeft);
        mainLayout->setRowStretch(1, 1);
        mainLayout->setColumnStretch(1, 1);

        setLayout(mainLayout);
    }

    { // Audio player
        m_spinPlayer = new QMediaPlayer(this);
        m_stopPlayer = new QMediaPlayer(this);

        m_spinAudioOut = new QAudioOutput;
        m_spinPlayer->setAudioOutput(m_spinAudioOut);
        m_spinPlayer->setSource(QUrl("qrc:/sound/circus.mp3"));
        m_spinAudioOut->setVolume(0.5f);

        m_stopAudioOut = new QAudioOutput;
        m_stopPlayer->setAudioOutput(m_stopAudioOut);
        m_stopPlayer->setSource(QUrl("qrc:/sound/end.mp3"));
        m_stopAudioOut->setVolume(0.5f);
    }
}


WWheel::~WWheel() {
    delete ui;
    delete m_spinAudioOut;
    delete m_timer;
}

void WWheel::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    /* BOOKMARK - This code slices the circle in equal parts to be able to dinamically decide the
     * ammount of sections and text for the roulette. However, since to make it beautifull might mean spending
     * a lot of time seeking to fit the text, maybe make it curved, etc. I've decided to leave it incomplete
     * and maybe come back some day. For now I simply load an image made with canva.
    */
    {
    //     labels = {
    //         "Mímica",
    //         "Desafiament",
    //         "Endevina\nla cançó",
    //         "Següent\nla cançó",
    //         "Pictionary"
    //     };
    //     QPointF center(w / 2.0, h / 2.0);

    //     QRectF wheelRect(
    //         center.x() - side / 2.0 + 20,
    //         center.y() - side / 2.0 + 20,
    //         side - 40,
    //         side - 40
    //         );

    //     int n = labels.size();
    //     if (n == 0)
    //         return;

    //     double sliceDegrees = 360.0 / n;

    //     for (int i = 0; i < n; ++i) {
    //         double startDegrees = i * sliceDegrees;
    //         double spanDegrees = sliceDegrees;

    //         painter.setBrush(colorForIndex(i));
    //         painter.setPen(QPen(Qt::white, 2));

    //         painter.drawPie(
    //             wheelRect,
    //             int(startDegrees * 16),
    //             int(spanDegrees * 16)
    //             );
    //     }

    //     // Outer border
    //     painter.setBrush(Qt::NoBrush);
    //     painter.setPen(QPen(QColor("#ffcc00"), 18));
    //     painter.drawEllipse(wheelRect);

    //     // Text
    //     painter.setPen(Qt::black);
    //     painter.setFont(QFont("Chewy", 20, QFont::Bold));

    //     painter.setPen(QPen(QColor("#d0d0d0"), 8));
    //     painter.setBrush(Qt::black);

    //     for (int i = 0; i < n; ++i) {
    //         double middleDegrees = i * sliceDegrees + sliceDegrees / 2.0;
    //         double radians = qDegreesToRadians(middleDegrees);

    //         painter.save();

    //         QPointF textCenter(
    //             center.x() + qCos(radians) * wheelRect.width() * 0.28,
    //             center.y() - qSin(radians) * wheelRect.height() * 0.28
    //             );

    //         painter.translate(textCenter);
    //         painter.rotate(-middleDegrees);

    //         QRectF textRect(-90, -25, 180, 60);

    //         painter.setPen(Qt::black);
    //         painter.drawText(textRect, Qt::AlignCenter | Qt::TextWordWrap, labels[i]);

    //         painter.restore();
    // }
    // Center circle
    // painter.setBrush(QColor("#ffcc00"));
    // painter.setPen(QPen(QColor("#b00000"), 4));
    // painter.drawEllipse(center, 45, 45);
    }
    // Draw wheel

    drawWheel();
    drawArrow();
}

void WWheel::drawWheel()
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w       = width();
    int h       = height();
    double side = static_cast<double>(qMin(w, h));

    painter.translate(w / 2, h / 2);
    painter.scale(side / static_cast<double>(m_wheelImage.width()), side / static_cast<double>(m_wheelImage.height()));
    painter.rotate(m_rotationAngle);
    painter.drawPixmap(-m_wheelImage.width() / 2, -m_wheelImage.height() / 2, m_wheelImage);
    painter.resetTransform();
}

void WWheel::drawArrow() {
    QPainter painter(this);
    int w    = width();
    int h    = height();
    int side = qMin(w, h);

    painter.translate(w / 2, h / 2);
    painter.setBrush(Qt::red);

    QPolygon arrow;
    arrow << QPoint(35, -side / 2) << QPoint(-35, -side / 2) << QPoint(0, -side / 2 + 95);
    painter.drawPolygon(arrow);
}

void WWheel::spin()
{
    m_forceStopping  = false;
    m_forceStopTicks = 0;
    m_slow = 0;

    m_timerTime = QRandomGenerator::global()->bounded(22, 50);
    m_timer->start(m_timerTime);

    m_spinPlayer->stop();
    m_stopPlayer->stop();

    m_spinAudioOut->setVolume(0.8f);
    m_spinPlayer->play();

    m_speed = QRandomGenerator::global()->bounded(40, 145);

    m_spinButton->setText("STOP!");
}

void WWheel::updateRotation()
{
    m_rotationAngle += m_speed;

    if (m_rotationAngle >= 360.0)
        m_rotationAngle = std::fmod(m_rotationAngle, 360.0);

    if (m_forceStopping) {
        m_speed -= 1.0;   // faster forced stop
    } else {
        if (m_speed >= 50.0)
            m_speed -= 1.0;
        else if (m_speed >= 30.0)
            m_speed -= 0.4;
        else if (m_speed >= 20.0)
            m_speed -= 0.25;
        else if (m_speed >= 5.0)
            m_speed -= 0.15;
        else
            m_speed -= 0.07;
    }

    if (m_speed <= 2.0) {
        fadeOut(m_spinAudioOut, 20, 0.01);
    }

    if (m_speed <= 0.0) {
        m_speed = 0.0;
        m_forceStopping = false;

        m_timer->stop();
        m_stopPlayer->play();
        m_spinButton->setText("GIRA LA RODA!");
    }

    update();
}

void WWheel::fadeOut(QAudioOutput *output, int fadeTickTime, double fadeDeccPerTick) {
    double vol = output->volume();
    QTimer *t = new QTimer(this);

    connect(t, &QTimer::timeout, this, [=]() mutable {
        // Decrease volume
        vol -= fadeDeccPerTick;
        if (vol <= 0) {
            vol = 0;
            t->stop();
            m_spinPlayer->stop();
            t->deleteLater();
        }

        output->setVolume(vol);
    });

    t->start(fadeTickTime);
}

void WWheel::changeRouletteImage(const QString &imagePath)
{
    m_wheelImage.load(imagePath);
    update();
}

void WWheel::changeSpinnAudio(const QString &spinnAudioPath)
{
    m_spinPlayer->setSource(QUrl::fromLocalFile(spinnAudioPath));

}

void WWheel::changeEndAudio(const QString &endAudioPath)
{
    m_stopPlayer->setSource(QUrl::fromLocalFile(endAudioPath));
}

void WWheel::stopWheel()
{
    if (!m_timer->isActive())
        return;

    m_forceStopping  = true;
    m_forceStopTicks = 0;
}
