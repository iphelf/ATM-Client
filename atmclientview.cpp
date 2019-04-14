#include "atmclientview.h"
#include "ui_atmclientview.h"

AtmClientView::AtmClientView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AtmClientView)
{
    ui->setupUi(this);
}

AtmClientView::~AtmClientView()
{
    delete ui;
}
