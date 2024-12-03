#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>

namespace Ui {
class testwindow;
}

class testwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit testwindow(QWidget *parent = nullptr);
    ~testwindow();

private:
    Ui::testwindow *ui;
};

#endif // TESTWINDOW_H
