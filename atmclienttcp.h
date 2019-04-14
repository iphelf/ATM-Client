#ifndef ATMCLIENTTCP_H
#define ATMCLIENTTCP_H

#include <QObject>
#include <QHostAddress>

class AtmClientTcp : public QObject
{
    Q_OBJECT
public:
    AtmClientTcp();
    bool initConnection(const QHostAddress& host,quint16 port);
signals:
    void recvMsg(char *msg);
    /*!
     * \brief   从服务器收到数据后就发出该信号
     * \param   msg是收到的数据内容
     * \return  void
     */
public slots:
    void sendMsg(char *msg);
};

#endif // ATMCLIENTTCP_H
