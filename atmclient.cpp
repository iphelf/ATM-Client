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
    model->run();
}