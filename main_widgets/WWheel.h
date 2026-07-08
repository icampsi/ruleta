/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#ifndef WWHEEL_H
#define WWHEEL_H

#include "Marcador.h"
#include <QWidget>

class QTimer;
class QPushButton;
class Qpixmap;
class QMediaPlayer;
class QAudioOutput;
class Marcador;

namespace Ui { class WWheel; }

class WWheel : public QWidget {
    Q_OBJECT

public:
    explicit WWheel(QWidget *parent = nullptr);
    ~WWheel();

    void paintEvent(QPaintEvent *event) override;
    void fadeOut(QAudioOutput *output, int fadeTickTime, double fadeDeccPerTick);

    void setMarcador(Marcador* marc) { m_marcador = marc; }
    void addNewLabel(const QString&& name) { m_marcador->addLabel(name); }

    void deleteLbl() { m_marcador->deleteLbl(); }

    void changeRouletteImage(const QString &imagePath);
    void changeSpinnAudio(const QString &spinnAudioPath);
    void changeEndAudio(const QString &endAudioPath);

    void drawWheel();
    void drawArrow();
    void stopWheel();

private slots:
    void spin();
    void updateRotation();

private:
    Ui::WWheel *ui;

    //Spin related
    QTimer* m_timer;
    int     m_rotationAngle;
    int     m_rotationDuration;
    int     m_slow           = 3;
    double  m_speed          = 35.;
    double  m_timerTime      = 30.;
    bool    m_stopping       = false;
    bool    m_forceStopping  = false;
    int     m_forceStopTicks = 0;

    // Audio Player
    QMediaPlayer* m_spinPlayer;
    QMediaPlayer* m_stopPlayer;
    QAudioOutput* m_spinAudioOut;
    QAudioOutput* m_stopAudioOut;

    // UI
    QPixmap      m_wheelImage;
    QPushButton* m_spinButton;
    Marcador*    m_marcador;

    // For Dynamic slices. Not used yet.
    QStringList     labels;
    QVector<QColor> colors;

public:
    // For Dynamic slices. Not used yet.
   void setLabels(const QStringList &newLabels) {
        labels = newLabels;
        update();
    }
    void addNewLabel(const QString &label) {
        labels.append(label);
        update();
    }

    QColor colorForIndex(int index) const {
        static const QVector<QColor> palette = {
            QColor("#0D47A1"), // blue
            QColor("#FF4B4B"), // red
            QColor("#7ED957"), // green
            QColor("#FFE66D"), // yellow
            QColor("#3AB7F0"), // light blue
            QColor("#B967FF"), // purple
            QColor("#FF9F1C")  // orange
        };

        return palette[index % palette.size()];
    }
};

#endif // WWHEEL_H
