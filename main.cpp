#include <QApplication>
#include "main.h"

int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    AtmClient *client=new AtmClient;
//    app.exec();
    return 0;
}
