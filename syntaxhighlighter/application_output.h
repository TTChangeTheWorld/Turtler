#ifndef APPLICATION_OUTPUT_H
#define APPLICATION_OUTPUT_H
#include <QtWidgets>
#include <QString>
#include <QTextEdit>
class Application_Output: public QTextEdit
{
public:
    Application_Output(QWidget *parent);
    void pushText(QString s);
    void clear();
};

#endif // APPLICATION_OUTPUT_H
