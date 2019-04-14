#ifndef ATMCLIENTVIEW_H
#define ATMCLIENTVIEW_H

#include <QMainWindow>
#include <QHostAddress>

namespace Ui {
class AtmClientView;
}

class AtmClientView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AtmClientView(QWidget *parent = 0);
    ~AtmClientView();

signals:
    void initConnection(const QHostAddress& host,quint16 port);
    /*!
     * \brief   用户输入好host和port并点击了某个表示“开始连接”的按钮后，
     *          后台的一切相关操作将由此开始...
     * \param   host是用户输入的主机ip，port是端口号
     * \return  void
     */
    void sendHelo(int userid);
    /*!
     * \brief   用户输入完userid后，向服务器问好，并找他索取密码输入框
     * \param   银行卡号？
     * \return  void
     */
    void sendPasswd(int passwd);
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

public slots:
    void recvPasswd();
    void recvOk();
    void recvErr(int code);
    void recvAmount(int amt);
    void recvBye();

private:
    Ui::AtmClientView *ui;
};

#endif // ATMCLIENTVIEW_H
