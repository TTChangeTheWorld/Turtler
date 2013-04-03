QT += widgets

HEADERS         = highlighter.h \
                  mainwindow.h \
    optionsclass.h
SOURCES         = highlighter.cpp \
                  mainwindow.cpp \
                  main.cpp \
                  StrangeFunctions.cpp \
    optionsclass.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/richtext/syntaxhighlighter
INSTALLS += target


wince*: {
   addFiles.files = main.cpp mainwindow.cpp
   addFiles.path = .
   DEPLOYMENT += addFiles
}
