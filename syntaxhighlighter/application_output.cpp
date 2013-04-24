#include "application_output.h"
Application_Output::Application_Output(QWidget *parent)
    :QTextEdit(parent)
{
    setReadOnly(true);
    setAcceptRichText(true);
    pushText(lolTest+ "1", "#ff00ff", "", true);
    pushText("Press run to start...", "#0000ff" , "<b>", true);

}

QString closeTags(QString s){
    QString ans = "";
    for (int i = 0; i < s.length(); i++){
        if (s[i]=='>') ans+='/';
        ans+=s[i];
    }
    return ans;
}

void Application_Output::pushText(QString s, QString color, QString tags, bool newLine){

    QTextCursor a;
    a = this->textCursor();
    a.setPosition(0);
    this->setTextCursor(a);
    QString additionTags = "";
    if (newLine) additionTags = "<br>";
    insertHtml(tags + "<div style=\"color:" + color + "\">" + s + closeTags(tags) +"</div>" + additionTags);
}

void Application_Output::clear(){
    this->setPlainText("");
}
