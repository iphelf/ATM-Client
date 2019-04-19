#include "atmclient.h"
#include "atmclientmodel.h"
#include "atmclientview.h"
#include "atmclienttcp.h"

AtmClient::AtmClient()
{
    qDebug()<<"<<  Client:: AtmClient\t>>";
    view=new AtmClientView;
    tcp=new AtmClientTcp;
    model=new AtmClientModel(view,tcp);
}

void AtmClient::run()
{
    qDebug()<<"<<  Client:: run\t\t>>";
    model->run();
}

void AtmClient::setDelimiter(const QString &delimiter)
{
    model->delim=delimiter;
}
