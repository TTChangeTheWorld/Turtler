#include "errorclass.h"

ErrorClass::ErrorClass()
{
    if (!this->setCode(0)){
        qDebug("Something went wrong while initializing ErrorClass.");
    }
    if (!this->setComment("Everything is OK")){
        qDebug("Something went wrong while initializing ErrorClass.");
    }
}

int ErrorClass::getCode()
{
    return this->Code;
}

QString ErrorClass::getComment()
{
    return this->Comment;
}

bool ErrorClass::setCode(int code)
{
    this->Code = code;
    return true;
}

bool ErrorClass::setComment(QString comment)
{
    this->Comment = comment;
    return true;
}
