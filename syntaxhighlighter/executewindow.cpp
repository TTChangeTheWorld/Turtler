#include "executewindow.h"


void ExecuteWindow::resizeEvent(QResizeEvent *){
    QRect a = geometry();
    mainLog->setGeometry(0, a.height()/2, a.width(), a.height()/2);
}

ExecuteWindow::ExecuteWindow(QWidget *parent) :
    QMainWindow(parent)
{

    mainLog = new Application_Output(this);
    mainLog->setAcceptRichText(true);
    mainLog->setGeometry(this->geometry());
    //setGeometry(10,10,500,500);
    //show();
}
