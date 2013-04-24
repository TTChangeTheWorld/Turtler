#ifndef EXECUTEWINDOW_H
#define EXECUTEWINDOW_H

#include <QMainWindow>
#include "application_output.h"
class ExecuteWindow: public QMainWindow

{
    Q_OBJECT
private:
public:
    ExecuteWindow(QWidget *parent = 0);
    Application_Output *mainLog;
signals:
    
public slots:
    void resizeEvent(QResizeEvent *);
};

#endif // EXECUTEWINDOW_H
