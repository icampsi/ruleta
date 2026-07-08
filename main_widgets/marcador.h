/* =================================================== *
 * ====        Copyright (c) 2024 icampsi         ==== *
 * ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
 * =================================================== */

#ifndef MARCADOR_H
#define MARCADOR_H

#include "ui_marcador.h"

#include <QWidget>

class MarcLbl;
class QVboxLayout;

namespace Ui { class Marcador; }

class Marcador : public QWidget {
    Q_OBJECT

public:
    explicit Marcador(QWidget *parent = nullptr);
    ~Marcador();

    void setName(const QString& name);
    void deleteLbl();

public slots:
    MarcLbl* addLabel(const QString& name);

private:
    Ui::Marcador *ui;
    QVBoxLayout *layout;
    std::vector<MarcLbl*> m_lbl;
};

#endif // MARCADOR_H
