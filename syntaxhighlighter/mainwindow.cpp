/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include<fstream>
#include "mainwindow.h"
#include "StrangeFunctions.cpp"

//! [0]
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupFileMenu();
    setupHelpMenu();
    setupEditor();

    //setCentralWidget(editor);
    setWindowTitle(tr("Syntax Highlighter"));
}
//! [0]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Syntax Highlighter"),
                tr("<p>The <b>Syntax Highlighter</b> example shows how " \
                   "to perform simple syntax highlighting by subclassing " \
                   "the QSyntaxHighlighter class and describing " \
                   "highlighting rules using regular expressions.</p>" \
                   "I , Pavlov Ilya, has modified it..."));
}

void MainWindow::newFile()
{
    setWindowTitle("New document");
    editor->clear();
}

void MainWindow::saveFileAs(){
  QString nsavePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", "Turtler files (*.trt *.tur)");
  if (!nsavePath.isEmpty()) savePath = nsavePath;
  if (savePath.isNull()) return;
  saveFile();
}

void MainWindow::keyPressed(){
    positionText->setText(QString::fromStdString(inttostring(editor->textCursor().columnNumber()+1) + " " +  inttostring(editor->textCursor().blockNumber()+1)));
}

void MainWindow::saveFile()
{

    if (savePath.isNull()){
        savePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", "Turtler files (*.trt *.tur)");
    }
    if (!savePath.isEmpty()) {
            setWindowTitle(savePath);
            //QFile file(savePath);
            std::ofstream fout(savePath.toStdString().c_str());
            //file.write()
            //editor->toPlainText().toStdString().c_str()
            //std::freopen(savePath.toStdString().c_str(), "W", fout);
            fout<<(editor->toPlainText().toStdString());
    }
}

void MainWindow::options()
{
    //OptionsWindow.show();

}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Turtler (*.trt *.tur)");

    if (!fileName.isEmpty()) {
        setWindowTitle(fileName);
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            editor->setPlainText(file.readAll());
    }
}

//! [1]
void MainWindow::resizeEvent(QResizeEvent *){
    editor->setGeometry(2, this->menuBar()->height(), this->width() - 20, this->height()-40);
    positionText->setGeometry(2, this->height()-20, this->width()-20, this->height() -5);
}

void MainWindow::setupEditor()
{

    mainFont.setFamily("Courier");
    mainFont.setFixedPitch(true);
    mainFont.setPointSize(20);
    positionText = new QLabel;
    editor = new QTextEdit;
    editor->setParent(this);
    editor->setFont(mainFont);
    editor->setGeometry(2, this->menuBar()->height(), this->width() - 2, this->height());
    connect(editor, SIGNAL(cursorPositionChanged()), this, SLOT(keyPressed()));
    positionText->setParent(this);
    positionText->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    positionText->show();
    highlighter = new Highlighter(editor->document());
    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        editor->setPlainText(file.readAll());
}
//! [1]

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("File"), this);
    QMenu *toolsMenu = new QMenu(tr("Tools"), this);
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(toolsMenu);
    fileMenu->addAction(tr("New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("Exit"), qApp, SLOT(quit()), QKeySequence::Quit);
    fileMenu->addAction(tr("Save"), this, SLOT(saveFile()), QKeySequence::Save);
    fileMenu->addAction(tr("Save as..."), this, SLOT(saveFileAs()), QKeySequence::SaveAs);

    toolsMenu->addAction(tr("Options"), this, SLOT(options()));

}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);

    helpMenu->addAction(tr("&About"), this, SLOT(about()));
    helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
}
