#include "expressionsolver.h"

ExpressionSolver::ExpressionSolver()
{
    this->curLexem = "none";
    this->curPos = 0;
    this->currentString = "";
}

void ExpressionSolver::SolveExpression(QString s){
    this->curLexem = "none";
    this->curPos = 0;
    this->currentString = s;
    this->nextLexem();

}

void ExpressionSolver::nextLexem(void){
  return;
}

