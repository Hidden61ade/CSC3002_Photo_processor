#ifndef IMAGEPROCESSORWINDOW_H
#define IMAGEPROCESSORWINDOW_H

#include <QWidget>

namespace Ui {
class ImageProcessorWindow;
}

class ImageProcessorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ImageProcessorWindow(QWidget *parent = nullptr);
    ~ImageProcessorWindow();

private slots:
    void on_LoadButton_clicked();

    void on_SaveButton_clicked();

    void on_pushButton_2_clicked();

    void SetParaValue(int value);

    void onBrightnessProc();
    void onSaturationProc();
    void onVibranceProc();
    void onContrastProc();
    void onClarityProc();
    void onHighlightShadowProc();
    void onTemperatureProc();
    void onHueProc();
    void featherEdgesProc();
    void addGainProc();
    void whiteBalanceProc();


    void on_pushButton_pressed();

private:
    void changeState(int i);
    Ui::ImageProcessorWindow *ui;
};

#endif // IMAGEPROCESSORWINDOW_H
