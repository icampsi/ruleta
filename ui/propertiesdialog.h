#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>

namespace Ui {
class PropertiesDialog;
}

class PropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropertiesDialog(QWidget *parent = nullptr);
    ~PropertiesDialog();
    const QString getBackgroundImagePath();
    const QString getRoulettImagePath();
    const QString getSpinningAudioPath();
    const QString getEndingAudioPath();

private slots:
    void on_bgImage_browsePushButton_clicked();
    const QString browseImageFile();
    const QString browseAudioFile();

    void on_rouletteImage_browsePushButton_clicked();
    void on_spinningAudio_brosePushButton_clicked();
    void on_endingAudio_browsePushButton_clicked();

private:
    Ui::PropertiesDialog *ui;
};

#endif // PROPERTIESDIALOG_H
