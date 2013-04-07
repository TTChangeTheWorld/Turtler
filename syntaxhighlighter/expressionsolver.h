#ifndef EXPRESSIONSOLVER_H
#define EXPRESSIONSOLVER_H
#include <QString>
class ExpressionSolver
{
public:
    ExpressionSolver();
    void SolveExpression(QString s);
    QString answer;
private:
    QString currentString;
    void nextLexem(void);
    int curPos;
    QString curLexem;
};

#endif // EXPRESSIONSOLVER_H
