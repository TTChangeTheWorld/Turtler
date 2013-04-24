QT += widgets

HEADERS         = highlighter.h \
                  mainwindow.h \
    optionsclass.h \
    expressionsolver.h \
    application_output.h \
    executewindow.h \
    turtle.h \
    errorclass.h \
    GlobalVars.h
SOURCES         = highlighter.cpp \
                  mainwindow.cpp \
                  main.cpp \
                  StrangeFunctions.cpp \
    optionsclass.cpp \
    expressionsolver.cpp \
    application_output.cpp \
    executewindow.cpp \
    turtle.cpp \
    errorclass.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/richtext/syntaxhighlighter
INSTALLS += target


wince*: {
   addFiles.files = main.cpp mainwindow.cpp
   addFiles.path = .
   DEPLOYMENT += addFiles
}
