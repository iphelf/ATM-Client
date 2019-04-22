#include <QApplication>
#include <QDebug>
#include "main.h"
#define QT_NO_DEBUG_OUTPUT
/*
 * 45.77.152.88 : 444
 * 用户名          密码
 * DL444            123456
 * Test             654321
 * 4444444444444444 444444
 */
/*
 * 119.29.117.67 : 3333
 * 用户名          密码
 * 998877665544     1122334455
 */
int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    AtmClient client;
    client.setDelimiter("\n");
    client.run();
    return app.exec();
}
