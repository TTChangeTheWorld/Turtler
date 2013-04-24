#ifndef APPLICATION_OUTPUT_H
#define APPLICATION_OUTPUT_H
#include <QString>
#include <QTextEdit>
class Application_Output: public QTextEdit
{
public:
    Application_Output(QWidget *parent);
    void pushText(QString s, QString color, QString tags, bool newLine = true);
    void clear();
private:

};

#endif // APPLICATION_OUTPUT_H
