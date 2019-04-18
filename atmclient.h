#ifndef ATMCLIENT_H
#define ATMCLIENT_H

#include <QObject>
class AtmClientModel;
class AtmClientView;
class AtmClientTcp;

class AtmClient : public QObject
{
    Q_OBJECT
public:
    AtmClient();
    void run();
private:
    AtmClientModel  *model;
    AtmClientView   *view;
    AtmClientTcp    *tcp;
};

#endif // ATMCLIENT_H