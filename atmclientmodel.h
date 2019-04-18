#ifndef ATMCLIENTMODEL_H
#define ATMCLIENTMODEL_H

#include <QObject>
class AtmClientView;
class AtmClientTcp;
class QRegExp;
class QHostAddress;
/*
From Server:
    Msg name            Purpose
    PASSWD              Ask user for PIN (password)
    OK                  Requested operation (PASSWD, WITHDRAWL) OK
    ERR <code>          Requested operation (PASSWD, WITHDRAWL) in ERROR
    AMOUNT <amt>        Sent in response to BALANCE request
    BYE                 User done, display welcome screen at ATM

From Client:
    Msg name            Purpose
    HELO <userid>       Let server know that there is a card in the ATM machine
                        ATM card transmits user ID to Server
    PASSWD <passwd>     User enters PIN, which is sent to server
    BALANCE             User requests balance
    WITHDRAWL <amount>  User asks to withdraw money
    BYE                 user all done
*/
class AtmClientModel : public QObject
{
    Q_OBJECT
public:
    AtmClientModel(AtmClientView *v,AtmClientTcp *t);
    ~AtmClientModel();
    void run();
public slots:
    void test();
    void toConnect(const QHostAddress& host,quint16 port);
    void pullMsg(const char *msg);
    void toSendHelo(const char *userid);
    void toSendPasswd(const char *passwd);
    void toSendBalance();
    void toSendWithdrawl(int amount);
    void toSendBye();

signals:
    void pushMsg(const char *msg);
private:
    AtmClientView *view;
    AtmClientTcp *tcp;
    QRegExp *re;
    int nMsgType;
    QString delim;
};

#endif // ATMCLIENTMODEL_H
