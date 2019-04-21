#include "atmclientview.h"
#include "ui_atmclientview.h"
#include <QRegExpValidator>
#include <QInputDialog>
#include <QMessageBox>

AtmClientView::AtmClientView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AtmClientView)
{
    qDebug()<<"<<  View  :: AtmClientView\t>>";
    ui->setupUi(this);
    ui->stackPanel->setCurrentIndex(0);
    ui->stackWindow->setCurrentIndex(0);
    QRegExpValidator *vldtHost=
        new QRegExpValidator(
        QRegExp(
            QString(R"(^((\d|\d\d|[0-1]\d\d|2[0-4]\d|25[0-5]))"
                    R"(\.){3})"
                    R"((\d|\d\d|[0-1]\d\d|2[0-4]\d|25[0-5]))"
                    R"($)")));
    QRegExpValidator *vldtPort=
        new QRegExpValidator(
        QRegExp(
            QString(R"(^\d+$)")));
    ui->lineEditHost->setValidator(vldtHost);
    ui->lineEditPort->setValidator(vldtPort);

    waitUi=new QWidget(nullptr,Qt::FramelessWindowHint);
    QLayout *layout=new QGridLayout(waitUi);
    QLabel *labelWait=new QLabel("Loading...");
    labelWait->setAlignment(Qt::AlignCenter);
    layout->addWidget(labelWait);
    layout->setAlignment(labelWait,Qt::AlignCenter);
    waitUi->resize(200,100);

    updateButtonConnect();
}

AtmClientView::~AtmClientView()
{
    qDebug()<<"<<  View  :: ~AtmClientView\t>>";
    delete ui;
}

void AtmClientView::testResult(bool valid)
{
    qDebug()<<"<<  View  :: testResult\t>>";
    if(valid)
        opState=true;
    else
        opState=false;
    stopWait();
}

void AtmClientView::connected()
{
    qDebug()<<"<<  View  :: connected\t>>";
    opState=true;
    stopWait();
}

void AtmClientView::recvPasswd()
{
    /*!
     * \brief   现在要开始输入密码了，输完后用sendPasswd发送出去
     * \param   void
     * \return  void
     */
    qDebug()<<"<<  View  :: recvPasswd\t>>";
    opState=true;
    stopWait();
}

void AtmClientView::recvOk()
{
    /*!
     * \brief   上一个操作正确地被执行完毕了，接下来自由操作吧，
     *          不过当然，记得要输出提示信息
     * \param   void
     * \return  void
     */
    qDebug()<<"<<  View  :: recvOk\t\t>>";
    opState=true;
    stopWait();
}

void AtmClientView::recvErr(int code)
{
    /*!
     * \brief   上一个操作的执行过程中发送了错误。再好好想想吧
     * \param   code是错误代码，不过其实并不用管啦，协议也没明确规定的说
     * \return  void
     */
    qDebug()<<"<<  View  :: recvErr\t\t>>";
    opState=false;
    bufferInt=code;
    qDebug()<<"Error"<<code;
    stopWait();
}

void AtmClientView::recvAmount(QString amt)
{
    /*!
     * \brief   你的查询余额请求得到正确回馈了！
     * \param   amt是你的余额
     * \return  void
     */
    qDebug()<<"<<  View  :: recvAmount\t>>";
    opState=true;
    bufferQString=amt;
    qDebug()<<"Amount: "<<amt;
    stopWait();
}

void AtmClientView::recvBye()
{
    /*!
     * \brief   服务器也对你说了bye。可以显示“连接已中断”之类字样了。
     * \param   void
     * \return  void
     */
    opState=true;
    qDebug()<<"<<  View  :: recvBye\t\t>>";
    stopWait();
}

void AtmClientView::updateButtonConnect()
{
    int stateHost,statePort;
    int pos=0;
    QString sHost(ui->lineEditHost->text());
    QString sPort(ui->lineEditPort->text());
    stateHost=ui->lineEditHost->validator()->validate(sHost,pos);
    pos=0;
    statePort=ui->lineEditPort->validator()->validate(sPort,pos);
    if(stateHost==QValidator::Acceptable &&
       statePort==QValidator::Acceptable) {
        ui->buttonConfigure->setEnabled(true);
        ui->buttonTest->setEnabled(true);
    } else {
        ui->buttonConfigure->setEnabled(false);
        ui->buttonTest->setEnabled(false);
    }
}

void AtmClientView::startWait(opType op)
{
    qDebug()<<"<<  View  :: startWait\t>>";
    ui->centralwidget->setEnabled(false);
    waitOp=op;
    qDebug()<<"New waitOp: "<<op;
//    waitUi->showFullScreen();
//    waitUi->show();
}

void AtmClientView::stopWait()
{
    qDebug()<<"<<  View  :: stopWait\t\t>>";
//    waitUi->hide();
    qDebug()<<"Hided";
    ui->centralwidget->setEnabled(true);
    qDebug()<<"Enabled";
    switch (waitOp) {
    case opTest: {
        qDebug()<<"opTest";
        if(opState)
            QMessageBox::about(nullptr,"Test Server","Valid!");
        else
            QMessageBox::warning(nullptr,"Test Server","Invalid!");
        break;
    }
    case opConnect: {
        qDebug()<<"opConnect";
        if(opState) {
            startWait(opHelo);
            emit sendHelo(ui->lineEditUserid->text().toStdString().data());
        } else
            QMessageBox::critical(nullptr,"Error",
                                  "Connection can not be built.\n"
                                  "Please go to \"Configuration\" to make "
                                  "things right.");
        break;
    }
    case opHelo: {
        qDebug()<<"opHelo";
        if(opState) {
            startWait(opPasswd);
            emit sendPasswd(ui->lineEditPasswd->text().toStdString().data());
        } else {
            QMessageBox::critical(nullptr,"Error",
                                  "Access to User account failed.");
            emit disconnect();
        }
        break;
    }
    case opPasswd: {
        qDebug()<<"opPasswd";
        if(opState)
            ui->stackPanel->setCurrentIndex(1);
        else {
            QMessageBox::critical(nullptr,"Error",
                                  "Authentification failed.");
            emit disconnect();
        }
        break;
    }
    case opBalance: {
        qDebug()<<"opBalance";
        if(opState) {
            QMessageBox::about(nullptr,"Balance",
                               QString("%1").arg(bufferQString));
            ui->textEditLog->append(QString("Balance: %1")\
                                    .arg(bufferQString));
        } else {
            QMessageBox::critical(nullptr,"Error",
                                  "Query for balance failed.");
        }
        break;
    }
    case opWithdrawl: {
        qDebug()<<"opWithdrawl";
        if(opState) {
            QMessageBox::about(nullptr,"Withdraw","Withdraw succeeded.");
            ui->textEditLog->append(QString("Withdraw: %1")\
                                    .arg(bufferInt));
        } else {
            QMessageBox::critical(nullptr,"Error",
                                  "Withdraw failed.");
        }
        break;
    }
    case opBye: {
        qDebug()<<"opBye";
        if(opState) {
            ui->stackPanel->setCurrentIndex(0);
        } else {
            QMessageBox::critical(nullptr,"Error",
                                  "Logout failed.");
        }
        break;
    }
    default:
        break;
    }
}

void AtmClientView::on_buttonConfigure_clicked()
{
    qDebug()<<"<<  View  :: on_buttonConfigure_clicked\t>>";
    serverHost=QHostAddress(ui->lineEditHost->text());
    serverPort=quint16(ui->lineEditPort->text().toInt());
    ui->stackWindow->setCurrentIndex(1);
}

void AtmClientView::on_buttonLogin_clicked()
{
    qDebug()<<"<<  View  :: on_buttonLogin_clicked\t>>";
    startWait(opConnect);
    emit connect(serverHost,serverPort);
}

void AtmClientView::on_buttonBalance_clicked()
{
    qDebug()<<"<<  View  :: on_buttonBalance_clicked\t>>";
    startWait(opBalance);
    emit sendBalance();
}

void AtmClientView::on_buttonWithdrawl_clicked()
{
    qDebug()<<"<<  View  :: on_buttonWithdrawl_clicked\t>>";
    QInputDialog input;
    bufferInt=input.getInt(nullptr,"Input amount","Amount=",-1,0);
    if(bufferInt==-1) return;
    startWait(opWithdrawl);
    emit sendWithdrawl(bufferInt);
}

void AtmClientView::on_buttonLogout_clicked()
{
    qDebug()<<"<<  View  :: on_buttonLogout_clicked\t>>";
    startWait(opBye);
    emit sendBye();
}

void AtmClientView::on_buttonDisconnect_clicked()
{
    qDebug()<<"<<  View  :: on_buttonDisconnect_clicked\t>>";
    ui->stackWindow->setCurrentIndex(0);
    emit disconnect();
}

void AtmClientView::on_buttonTest_clicked()
{
    qDebug()<<"<<  View  :: on_buttonTest_clicked\t>>";
    startWait(opTest);
    emit test(QHostAddress(ui->lineEditHost->text()),
              quint16(ui->lineEditPort->text().toInt()));
}

void AtmClientView::on_lineEditHost_textChanged(const QString /*&text*/)
{
    qDebug()<<"<<  View  :: on_lineEditHost_textChanged\t>>";
    updateButtonConnect();
}

void AtmClientView::on_lineEditPort_textChanged(const QString /*&arg1*/)
{
    qDebug()<<"<<  View  :: on_lineEditPort_textChanged\t>>";
    updateButtonConnect();
}

void AtmClientView::on_buttonGoConfigure_clicked()
{
    qDebug()<<"<<  View  :: on_buttonGoConfigure_clicked\t>>";
    ui->stackWindow->setCurrentIndex(0);
}
