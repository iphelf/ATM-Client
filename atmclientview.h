#ifndef ATMCLIENTVIEW_H
#define ATMCLIENTVIEW_H

#include <QMainWindow>
#include <QHostAddress>

namespace Ui
{
class AtmClientView;
}

class AtmClientView : public QMainWindow
{
    Q_OBJECT

    enum opType {
        opConnect,
        opHelo,
        opPasswd,
        opBalance,
        opWithdrawl,
        opBye
    };

public:
    explicit AtmClientView(QWidget *parent = 0);
    ~AtmClientView();

signals:
    void test();
    void connect(const QHostAddress& host,quint16 port);
    /*!
     * \brief   用户输入好host和port并点击了某个表示“开始连接”的按钮后，
     *          后台的一切相关操作将由此开始...
     * \param   host是用户输入的主机ip，port是端口号
     * \return  void
     */
    void sendHelo(const char *userid);
    /*!
     * \brief   用户输入完userid后，向服务器问好，并找他索取密码输入框
     * \param   银行卡号？
     * \return  void
     */
    void sendPasswd(const char *passwd);
    /*!
     * \brief   现在已经完成输入密码了，那么可以用sendPasswd发送出去了
     * \param   密码
     * \return  void
     */
    void sendBalance();
    /*!
     * \brief   用户说要查询余额，那么，查询余额吧
     * \param   void
     * \return  void
     */
    void sendWithdrawl(int amount);
    /*!
     * \brief   ATM存在的意义： 取钱。现在就开始吧
     * \param   要取的金额
     * \return  void
     */
    void sendBye();
    /*!
     * \brief   要办的办完了，现在就退出登录吧
     * \param   void
     * \return  void
     */
    void disconnect();

public slots:
    void connected();
    void recvPasswd();
    void recvOk();
    void recvErr(int code);
    void recvAmount(QString amt);
    void recvBye();

public:
    void updateButtonConnect();
    void startWait(opType op);
    void stopWait();

private slots:
    void on_buttonConnect_clicked();
    void on_buttonLogin_clicked();
    void on_buttonBalance_clicked();
    void on_buttonWithdrawl_clicked();
    void on_buttonLogout_clicked();
    void on_buttonDisconnect_clicked();
    void on_lineEditHost_textChanged(const QString);
    void on_lineEditPort_textChanged(const QString);

private:
    Ui::AtmClientView *ui;
    QWidget *waitUi;
    opType waitOp;
    int bufferInt;
    QString bufferQString;
    bool opState;
};

#endif // ATMCLIENTVIEW_H
