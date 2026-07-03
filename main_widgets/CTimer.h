/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#ifndef CTIMER_H
#define CTIMER_H

#include <QTimer>
#include <QWidget>

namespace Ui { class CTimer; }

class CTimer : public QWidget {
    Q_OBJECT

public:
    explicit CTimer(QWidget *parent = nullptr);
    ~CTimer();

    void startTimer() { m_timer.start(10); }
    void stopTimer()  { m_timer.stop(); }
    void resetTimer();
    void updateTime();

    void setDuration(const size_t dur) { m_duration = dur; }
    const size_t& getDuration() const  { return m_duration; }

private:
    Ui::CTimer *ui;
    QTimer m_timer;
    size_t m_duration;
    size_t m_elapsedTime;
};

#endif // CTIMER_H
