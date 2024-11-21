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

private:
    Ui::ImageProcessorWindow *ui;
};

#endif // IMAGEPROCESSORWINDOW_H
