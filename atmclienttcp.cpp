#include "atmclienttcp.h"

AtmClientTcp::AtmClientTcp()
{
   socket = new QTcpSocket();
   QObject::connect(socket, &QTcpSocket::readyRead, this, &AtmClientTcp::recvMsg);
}
AtmClientTcp::~AtmClientTcp()
{
    delete this->socket;
}


bool AtmClientTcp::initConnection(const QHostAddress &host, quint16 port)
{
    /*!
     * \brief   与服务器建立连接
     * \param   host是服务器ip地址，port是端口号
     * \return  如果成功建立连接就返回true，否则返回false
     */
    //取消已有的连接
    socket->abort();
    //连接服务器
    socket->connectToHost(host, port);
    //等待连接成功
    if(!socket->waitForConnected(30000))
         return false;
    return true;
}
void AtmClientTcp::disconnected(){
    socket->disconnectFromHost();
}

void AtmClientTcp:: sendMsg(char *msg)
{
    /*!
     * \brief   将msg发送到服务器
     * \param   msg是要发送的内容
     * \return  void
     */
    ;
    client->write(msg);
    socket->flush();
}

void AtmClientTcp::recvMsg(char *msg)
{
    msg=socket->readAll();
}

