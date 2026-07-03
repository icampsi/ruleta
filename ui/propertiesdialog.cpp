#include "propertiesdialog.h"
#include "ui_propertiesdialog.h"

#include <QFileDialog>

PropertiesDialog::PropertiesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PropertiesDialog)
{
    ui->setupUi(this);
}

PropertiesDialog::~PropertiesDialog()
{
    delete ui;
}

const QString PropertiesDialog::getBackgroundImagePath()
{
    return ui->bgImage_lineEdit->text();
}

const QString PropertiesDialog::getRoulettImagePath()
{
    return ui->rouletteImage_lineEdit->text();
}

const QString PropertiesDialog::getSpinningAudioPath()
{
    return ui->spinningAudio_lineEdit->text();
}

const QString PropertiesDialog::getEndingAudioPath()
{
    return ui->endingAudio_lineEdit->text();
}


const QString PropertiesDialog::browseImageFile()
{
    return QFileDialog::getOpenFileName(
        this,
        "Open file",
        "",
        "Images (*.png *.jpg *.jpeg);;All files (*.*)"
        );
}

const QString PropertiesDialog::browseAudioFile()
{
    return QFileDialog::getOpenFileName(
        this,
        "Open file",
        "",
        "Audio (*.mp3 *.wav *.flac *.m4a *.aac *.aiff *.aif);;All files (*.*)"
        );
}

void PropertiesDialog::on_bgImage_browsePushButton_clicked()
{
    ui->bgImage_lineEdit->setText(browseImageFile());
}


void PropertiesDialog::on_rouletteImage_browsePushButton_clicked()
{
    ui->rouletteImage_lineEdit->setText(browseImageFile());

}

void PropertiesDialog::on_spinningAudio_brosePushButton_clicked()
{
    ui->spinningAudio_lineEdit->setText(browseAudioFile());

}

void PropertiesDialog::on_endingAudio_browsePushButton_clicked()
{
    ui->endingAudio_lineEdit->setText(browseAudioFile());

}

