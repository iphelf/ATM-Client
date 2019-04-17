#include "atmclienttcp.h"

AtmClientTcp::AtmClientTcp()
{
    qDebug()<<"<<  Tcp   :: AtmClientTcp\t>>";
    socket = new QTcpSocket();
    QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(read()));
}

AtmClientTcp::~AtmClientTcp()
{
    qDebug()<<"<<  Tcp   :: ~AtmClientTcp\t>>";
    delete this->socket;
}

bool AtmClientTcp::connect(const QHostAddress &host, quint16 port)
{
    /*!
     * \brief   与服务器建立连接
     * \param   host是服务器ip地址，port是端口号
     * \return  如果成功建立连接就返回true，否则返回false
     */
    qDebug()<<"<<  Tcp   :: connect\t>>";
    //取消已有的连接
    socket->abort();
    //连接服务器
    socket->connectToHost(host, port);
    //等待连接成功
    if(!socket->waitForConnected(30000)) {
        qDebug()<<"Connection failed!";
        return false;
    }
    qDebug()<<"Connection succeeded!";
    return true;
}

void AtmClientTcp::disconnect()
{
    qDebug()<<"<<  Tcp   :: disconnect\t>>";
    socket->disconnectFromHost();
}

void AtmClientTcp:: sendMsg(const char *msg)
{
    /*!
     * \brief   将msg发送到服务器
     * \param   msg是要发送的内容
     * \return  void
     */
    qDebug()<<"<<  Tcp   :: sendMsg\t>>";
    socket->write(msg);
    socket->flush();
    qDebug() << "Sent: "<<msg;
}

void AtmClientTcp::read()
{
    qDebug()<<"<<  Tcp   :: read\t>>";
    while(socket->bytesAvailable()>0) {
        QByteArray buffer=socket->readAll();
        buffer.data();
        qDebug() << "Received: "<<buffer.data();
    }
}

