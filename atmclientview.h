#ifndef ATMCLIENTVIEW_H
#define ATMCLIENTVIEW_H

#include <QMainWindow>

namespace Ui {
class AtmClientView;
}

class AtmClientView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AtmClientView(QWidget *parent = 0);
    ~AtmClientView();

private:
    Ui::AtmClientView *ui;
};

#endif // ATMCLIENTVIEW_H
