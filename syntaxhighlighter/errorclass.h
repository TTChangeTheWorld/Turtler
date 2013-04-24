#ifndef ERRORCLASS_H
#define ERRORCLASS_H
#include <QString>

class ErrorClass
{
public:
    ErrorClass();
    int getCode();
    QString getComment();
    bool setCode(int code);
    bool setComment(QString comment);
private:
    int Code;
    QString Comment;
};

#endif // ERRORCLASS_H
