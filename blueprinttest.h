#ifndef BLUEPRINTTEST_H
#define BLUEPRINTTEST_H

#include <QMainWindow>

namespace Ui {
class BluePrintTest;
}

class BluePrintTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit BluePrintTest(QWidget *parent = nullptr);
    ~BluePrintTest();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::BluePrintTest *ui;
};

#endif // BLUEPRINTTEST_H
