#include "executewindow.h"

void ExecuteWindow::resizeEvent(QResizeEvent *){
    QRect a = geometry();
    mainLog->setGeometry(0, a.height()/4*3, a.width(), a.height()/4);
    //field->setGeometry(0, 50, 0, a.height()/4*3-55);
}

ExecuteWindow::ExecuteWindow(QWidget *parent) :
    QMainWindow(parent)
{

    mainLog = new Application_Output(this);
    mainLog->setAcceptRichText(true);
    //setGeometry(10,10,500,500);
    //show();
}
