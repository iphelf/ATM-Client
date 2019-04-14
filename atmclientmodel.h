#ifndef ATMCLIENTMODEL_H
#define ATMCLIENTMODEL_H

#include <QObject>

class AtmClientModel : public QObject
{
    Q_OBJECT
public:
    AtmClientModel();
public slots:
    void pullMsg(char *msg);
signals:
    void pushMsg(char *msg);
};

#endif // ATMCLIENTMODEL_H
