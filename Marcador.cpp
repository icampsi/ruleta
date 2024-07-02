#include "Marcador.h"
#include "MarcLbl.h"
#include <QRandomGenerator>

Marcador::Marcador(QWidget *parent) :
    QWidget(parent), ui(new Ui::Marcador), m_lbl()
{
    ui->setupUi(this);

    // Empty layout
    layout = new QVBoxLayout(this);
    ui->frame_board->setLayout(layout);


    // Random Color stylesheet
    QString widgetColorString = QString("QFrame#frame_board { background-color: rgba(%1, %2, %3, %4); }").arg(50)
                                    .arg(50)
                                    .arg(50)
                                    .arg(128);

    setStyleSheet(widgetColorString);
}

Marcador::~Marcador() {
    delete layout;
    for(MarcLbl *lbl : m_lbl) {
        delete lbl;
    }
    delete ui;
}

void Marcador::addLabel(const QString& name) {
    MarcLbl *newMarcLbl = new MarcLbl(this);
    layout->addWidget(newMarcLbl);
    newMarcLbl->setName(name);
    m_lbl.push_back(newMarcLbl);
}

void Marcador::deleteLbl() {
    if (!m_lbl.empty()) {
        layout->removeWidget(m_lbl.back());
        delete m_lbl.back();
        m_lbl.pop_back();
    }
}
