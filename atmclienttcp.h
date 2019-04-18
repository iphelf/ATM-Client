#ifndef ATMCLIENTTCP_H
#define ATMCLIENTTCP_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>

class AtmClientTcp : public QObject
{
    Q_OBJECT
public:
    AtmClientTcp();
    ~AtmClientTcp();
    bool connect(const QHostAddress& host,quint16 port);
signals:
    void recvMsg(const char *msg);
    /*!
     * \brief   从服务器收到数据后就发出该信号
     * \param   msg是收到的数据内容
     * \return  void
     */
public slots:
    void read();
    void sendMsg(const char *msg);
    void disconnect();
private:
    QTcpSocket *socket;

};

#endif // ATMCLIENTTCP_H
