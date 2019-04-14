#include "atmclient.h"
#include "atmclientmodel.h"
#include "atmclientview.h"
#include "atmclienttcp.h"

AtmClient::AtmClient()
{
    model=new AtmClientModel;
    view=new AtmClientView;
    tcp=new AtmClientTcp;
}
