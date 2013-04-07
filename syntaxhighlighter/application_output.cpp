#include "application_output.h"

Application_Output::Application_Output(QWidget *parent)
    :QTextEdit(parent)
{


   //log = new QTextEdit();
    setReadOnly(true);
    setAcceptRichText(true);
    pushText("<b style=\"color:#0000ff\">Press run to start...</b>");

}
void Application_Output::pushText(QString s){

    QTextCursor a;
    //a = this->textCursor();
    //a.setPosition(10);
    a = this->textCursor();
    a.setPosition(0);
    this->setTextCursor(a);
    insertHtml(s + "<br>");
}

void Application_Output::clear(){
    setPlainText("");
}
