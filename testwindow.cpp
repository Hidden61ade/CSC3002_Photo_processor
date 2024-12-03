#include "testwindow.h"
#include "ui_testwindow.h"
#include "agvview.h"
testwindow::testwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testwindow)
{
    ui->setupUi(this);
    AgvView *agvView(new AgvView());
    ui->verticalLayout->addWidget(agvView->scenePointDisPlay);
    ui->verticalLayout_2->addWidget(agvView);
}

testwindow::~testwindow()
{
    delete ui;
}
