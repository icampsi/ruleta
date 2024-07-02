#ifndef WWHEEL_H
#define WWHEEL_H

#include "Marcador.h"
#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QPixmap>
#include <QtMultimedia/QMediaPlayer>

namespace Ui { class WWheel; }

class WWheel : public QWidget {
    Q_OBJECT

public:
    explicit WWheel(QWidget *parent = nullptr);
    ~WWheel();

    void paintEvent(QPaintEvent *event) override;
    void fadeOut(QAudioOutput *output);

    void setMarcador(Marcador* marc) { marcador = marc; }

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void spin();
    void updateRotation();

private:
    Ui::WWheel *ui;

    QTimer *timer;
    int rotationAngle;
    int rotationDuration;
    QPushButton *spinButton;
    QPixmap wheelImage;
    QMediaPlayer *spinPlayer;
    QMediaPlayer *stopPlayer;
    QAudioOutput *m_spinAudioOut;
    QAudioOutput *m_stopAudioOut;

    double timerTime = 30;
    int speed = 35;
    int slow = 3;

    void drawArrow(QPainter &painter);
    Marcador *marcador;
};

#endif // WWHEEL_H
