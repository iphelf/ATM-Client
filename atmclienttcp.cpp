#include "atmclienttcp.h"

AtmClientTcp::AtmClientTcp()
{

}

bool AtmClientTcp::initConnection(const QHostAddress &host, quint16 port)
{
    /*!
     * \brief   与服务器建立连接
     * \param   host是服务器ip地址，port是端口号
     * \return  如果成功建立连接就返回true，否则返回false
     */
    return true;
}

void AtmClientTcp::sendMsg(char *msg)
{
    /*!
     * \brief   将msg发送到服务器
     * \param   msg是要发送的内容
     * \return  void
     */
    ;
}
