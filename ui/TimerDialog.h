#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H

#include <QDialog>

namespace Ui {
class TimerDialog;
}

class TimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimerDialog(QWidget *parent = nullptr);
    ~TimerDialog();

private:
    Ui::TimerDialog *ui;

    void keyPressEvent(QKeyEvent *event) override;

};

#endif // TIMERDIALOG_H
