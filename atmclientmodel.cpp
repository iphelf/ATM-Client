#include "atmclientmodel.h"
#include "atmclientview.h"
#include "atmclienttcp.h"
#include <QDebug>
#include <QRegExp>
#include <QHostAddress>
#include <windows.h>
using namespace std;

AtmClientModel::AtmClientModel(AtmClientView *v, AtmClientTcp *t)
{
    qDebug()<<"<<  Model :: AtmClientModel\t>>";
    this->view=v;
    this->tcp=t;
    nMsgType=5;
    re=new QRegExp[nMsgType] {QRegExp(R"(^PASSWD\n$)"),
                              QRegExp(R"(^OK\n$)"),
                              QRegExp(R"(^ERR (-?[0-9]*)\n$)"),
                              QRegExp(R"(^AMOUNT (-?\d*(\.\d*)?)\n$)"),
                              QRegExp(R"(^BYE\n$)")
                             };
    connect(this,SIGNAL(pushMsg(const char*)),tcp,SLOT(sendMsg(const char*)));
    connect(tcp,SIGNAL(recvMsg(const char*)),this,SLOT(pullMsg(const char*)));
    connect(view,SIGNAL(test()),this,SLOT(test()));
    connect(view,SIGNAL(connect(QHostAddress,quint16)),
            this,SLOT(toConnect(QHostAddress,quint16)));
    connect(view,SIGNAL(sendHelo(const char*)),
            this,SLOT(toSendHelo(const char*)));
    connect(view,SIGNAL(sendPasswd(const char*)),
            this,SLOT(toSendPasswd(const char*)));
    connect(view,SIGNAL(sendBalance()),this,SLOT(toSendBalance()));
    connect(view,SIGNAL(sendWithdrawl(int)),this,SLOT(toSendWithdrawl(int)));
    connect(view,SIGNAL(sendBye()),this,SLOT(toSendBye()));
    connect(view,SIGNAL(disconnect()),tcp,SLOT(disconnect()));
}

AtmClientModel::~AtmClientModel()
{
    qDebug()<<"<<  Model :: ~AtmClientModel\t>>";
    delete view;
    delete tcp;
    delete [] re;
}

void AtmClientModel::run()
{
    qDebug()<<"<<  Model :: run\t\t>>";
    view->show();
}

void AtmClientModel::test()
{
    qDebug()<<"<<  Model :: test\t\t>>";
}

void AtmClientModel::toConnect(const QHostAddress &host, quint16 port)
{
    qDebug()<<"<<  Model :: toConnect\t>>";
    if(!tcp->connect(host,port))
        view->recvErr(0);
}

void AtmClientModel::pullMsg(const char *msg)
{
    qDebug()<<"<<  Model :: pullMsg\t>>";
    QString raw(msg);
    for(int i=0; i<nMsgType; i++) if(re->exactMatch(raw)) {
            switch (i) {
            case 0:
                view->recvPasswd();
                break;
            case 1:
                view->recvOk();
                break;
            case 2: {
                int code=re[i].cap(1).toInt();
                view->recvErr(code);
                break;
            }
            case 3: {
                double amt=re[i].cap(1).toDouble();
                view->recvAmount(amt);
                break;
            }
            case 4:
                view->recvBye();
                break;
            default:
                break;
            }
            return;
        }
    view->recvErr(-1); //Invalid format of data from server
}

void AtmClientModel::toSendHelo(const char *userid)
{
    qDebug()<<"<<  Model :: toSendHelo\t>>";
    emit pushMsg(QString("HELO %1\n").arg(userid).toStdString().data());
}
void AtmClientModel::toSendPasswd(const char *passwd)
{
    qDebug()<<"<<  Model :: toSendPasswd\t>>";
    emit pushMsg(QString("PASSWD %1\n").arg(passwd).toStdString().data());
}
void AtmClientModel::toSendBalance()
{
    qDebug()<<"<<  Model :: toSendBalance\t>>";
    emit pushMsg("BALANCE\n");
}
void AtmClientModel::toSendWithdrawl(int amount)
{
    qDebug()<<"<<  Model :: toSendWithdrawl\t>>";
    emit pushMsg(QString("WITHDRAWL %1\n").arg(amount).toStdString().data());
}
void AtmClientModel::toSendBye()
{
    qDebug()<<"<<  Model :: toSendBye\t>>";
    emit pushMsg("BYE\n");
    tcp->disconnect();
}
