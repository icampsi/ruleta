#ifndef MARCLBL_H
#define MARCLBL_H

#include <QWidget>

namespace Ui { class MarcLbl; }

class MarcLbl : public QWidget {
    Q_OBJECT
public:
    explicit MarcLbl(QWidget *parent = nullptr);
    void updateScore();
    void setName(const QString& name);
signals:

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_subs_clicked();

private:
    Ui::MarcLbl *ui;
    int m_score = 0;
};

#endif // MARCLBL_H
