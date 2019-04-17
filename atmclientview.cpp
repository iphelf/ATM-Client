#include "atmclientview.h"
#include "ui_atmclientview.h"

AtmClientView::AtmClientView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AtmClientView)
{
    qDebug()<<"<<  View  :: AtmClientView\t>>";
    ui->setupUi(this);
}

AtmClientView::~AtmClientView()
{
    qDebug()<<"<<  View  :: ~AtmClientView\t>>";
    delete ui;
}

void AtmClientView::recvPasswd()
{
    /*!
     * \brief   现在要开始输入密码了，输完后用sendPasswd发送出去
     * \param   void
     * \return  void
     */
    qDebug()<<"<<  View  :: recvPasswd\t>>";
}

void AtmClientView::recvOk()
{
    /*!
     * \brief   上一个操作正确地被执行完毕了，接下来自由操作吧，
     *          不过当然，记得要输出提示信息
     * \param   void
     * \return  void
     */
    qDebug()<<"<<  View  :: recvOk\t>>";
}

void AtmClientView::recvErr(int code)
{
    /*!
     * \brief   上一个操作的执行过程中发送了错误。再好好想想吧
     * \param   code是错误代码，不过其实并不用管啦，协议也没明确规定的说
     * \return  void
     */
    qDebug()<<"<<  View  :: recvErr\t>>";
}

void AtmClientView::recvAmount(double amt)
{
    /*!
     * \brief   你的查询余额请求得到正确回馈了！
     * \param   amt是你的余额
     * \return  void
     */
    qDebug()<<"<<  View  :: recvAmount\t>>";
}

void AtmClientView::recvBye()
{
    /*!
     * \brief   服务器也对你说了bye。可以显示“连接已中断”之类字样了。
     * \param   void
     * \return  void
     */
    qDebug()<<"<<  View  :: recvBye\t>>";
}
