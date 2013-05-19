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

#include <mainwindow.h>

//! [0]
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ExWindow = new ExecuteWindow();
    setupFileMenu();
    setupHelpMenu();
    setupEditor();

    //setCentralWidget(editor);
    setWindowTitle(tr("Turtler"));
    this->ExWindow->mainLog->pushText("Everything is ready.","orange", "", true);
}
//! [0]

std::string inttostring(int a){
  std::stringstream b;
  b<<a;
  std::string help;
  b>>help;
  b.clear();
  return help;
}

void MainWindow::about()
{
    this->ExWindow->mainLog->pushText(tr("Window about opened."), "black", "<i>", true);
    QMessageBox::about(this, tr("About Turtler"),
                tr("<p>The <b>Turtler</b> is a project"\
                   "... but i wouldn't write about it..." \
                   "<h1> I am too lazy </h1>"
                   ));
}

void MainWindow::newFile()
{
    this->ExWindow->mainLog->pushText(tr("New file created."), "red", "");
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
    positionText->setText(QString::fromStdString(inttostring(editor->textCursor().columnNumber()+1) + " : " +  inttostring(editor->textCursor().blockNumber()+1) + "  " + isTextModified));
}



void MainWindow::saveFile()
{

    if (savePath.isNull()){
        savePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", "Turtler files (*.trt *.tur)");
    }
    if (!savePath.isEmpty()) {
            isTextModified = "";
            qDebug((inttostring(validFileName.lastIndexIn(savePath))+" "+savePath.toStdString()).c_str());
            if (validFileName.lastIndexIn(savePath)<0) savePath+=".trt";
            setWindowTitle(savePath);
            //QFile file(savePath);
            std::ofstream fout(savePath.toStdString().c_str());
            //file.write()
            //editor->toPlainText().toStdString().c_str()
            //std::freopen(savePath.toStdString().c_str(), "W", fout);
            fout<<(editor->toPlainText().toStdString());
            positionText->setText(QString::fromStdString(inttostring(editor->textCursor().columnNumber()+1) + " : " +  inttostring(editor->textCursor().blockNumber()+1) + "  " + isTextModified));
            this->ExWindow->mainLog->pushText("File saved as " + savePath, "red", "");
    }
}

void MainWindow::options()
{
    //OptionsWindow.show();

}

void MainWindow::textChanged()
{
    //Text for showing if text is modified
    if (isTextModified!="Modified"){
        isTextModified = "Modified";
        keyPressed();
    }
    //Add spaces in new string now ^^
    if (aiEnabled){
        if (editor->textCursor().blockNumber()<=0) return;
        SplitedText = editor->toPlainText().split("\n");
        if (SplitedText.size()!=PSize){
           PSize = SplitedText.size();
         if (true){
             //qDebug("Ok");
             int cur = 0;
             while ((cur<SplitedText[editor->textCursor().blockNumber() - 1].length())&&(SplitedText[editor->textCursor().blockNumber() - 1][cur]==' ')) {
                 cur++;
                 editor->textCursor().insertText(" ");
                 editor->textCursor().movePosition(QTextCursor::Right);
                 //qDebug(inttostring(cur).c_str());
             }
         }
        }
        PSize = SplitedText.size();
    }


}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Turtler files (*.trt *.tur) \n All files (*)");
    if (!fileName.isEmpty()) {
        setWindowTitle(fileName);
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)){
            editor->setPlainText(file.readAll());
            this->ExWindow->mainLog->pushText("Opened file: " + fileName , "black", "<b>");
        }
    }
}

//! [1]
void MainWindow::resizeEvent(QResizeEvent *){

    this->editor->setGeometry(2, this->menuBar()->height(), this->width() - 20, this->height()-40);
    positionText->setGeometry(2, this->height()-20, this->width()-20, this->height() -5);
}

void MainWindow::setupEditor()
{

    aiEnabled = true;
    mainFont.setFamily("Courier");
    mainFont.setFixedPitch(true);
    mainFont.setPointSize(20);
    validFileName.setPattern("[a-zA-Z/а-яА-Я]+\\.[a-zA-Z/а-яА-Я]+");
    positionText = new QLabel;
    editor = new QTextEdit;
    editor->setAcceptRichText(false);
    editor->setParent(this);
    editor->setFont(mainFont);
    editor->setGeometry(2, this->menuBar()->height(), this->width() - 2, this->height());
    //editor->setAutoFormatting(QTextEdit::AutoAll);
    connect(editor, SIGNAL(cursorPositionChanged()), this, SLOT(keyPressed()));
    connect(editor, SIGNAL(textChanged()), this, SLOT(textChanged()));
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
    toolsMenu->addAction(tr("Font config"), this, SLOT(changeFont()));
}

void MainWindow::changeFont(){
    bool ok;
    editor->setFont(QFontDialog::getFont(&ok, this));
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);

    helpMenu->addAction(tr("&About"), this, SLOT(about()));
    helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
}
