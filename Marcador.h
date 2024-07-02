#ifndef MARCADOR_H
#define MARCADOR_H

#include <QWidget>
#include <QVBoxLayout>
#include "ui_Marcador.h"

class MarcLbl;

namespace Ui { class Marcador; }

class Marcador : public QWidget {
    Q_OBJECT

public:
    explicit Marcador(QWidget *parent = nullptr);
    ~Marcador();

    void setName(const QString& name);
    void deleteLbl();

public slots:
    void addLabel(const QString& name);

private:
    Ui::Marcador *ui;
    QVBoxLayout *layout;
    std::vector<MarcLbl*> m_lbl;
};

#endif // MARCADOR_H
