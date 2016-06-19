#-------------------------------------------------
#
# Project created by QtCreator 2016-06-13T13:35:27
#
# required Qt5.2
#
#-------------------------------------------------

QT += core gui widgets opengl xml xmlpatterns

CONFIG += c++11

TARGET = hestia
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    errormessagedialog.cpp \
    filenameeditdialog.cpp \
    glwindow.cpp \
    converter.cpp \
    highlighter.cpp \
    archive/container.cpp \
    archive/project.cpp \
    emulator/scene.cpp \
    extensions/ruby.cpp \
    extensions/scenariodirectionprocessor.cpp \
    extensions/scenarioparagraphtreeprocessor.cpp \
    extensions/textspantreeprocessor.cpp \
    extensions/wordlink.cpp \
    gl/base.cpp \
    gl/context.cpp \
    gl/environment.cpp \
    gl/font.cpp \
    gl/image.cpp \
    models/projecttreemodel.cpp \
    models/structurelistmodel.cpp \
    widgets/glwidget.cpp \
    widgets/plaintextedit.cpp

HEADERS += \
    mainwindow.h \
    errormessagedialog.h \
    filenameeditdialog.h \
    glwindow.h \
    converter.h \
    highlighter.h \
    version.h \
    archive/container.h \
    archive/project.h \
    emulator/scene.h \
    extensions/ruby.h \
    extensions/scenariodirectionprocessor.h \
    extensions/scenarioparagraphtreeprocessor.h \
    extensions/textspantreeprocessor.h \
    extensions/wordlink.h \
    gl/base.h \
    gl/context.h \
    gl/environment.h \
    gl/font.h \
    gl/image.h \
    models/projecttreemodel.h \
    models/structurelistmodel.h \
    widgets/glwidget.h \
    widgets/plaintextedit.h

FORMS += \
    mainwindow.ui \
    errormessagedialog.ui \
    filenameeditdialog.ui \
    glwindow.ui


# 3rd-party sources
INCLUDEPATH += $$PWD/3rdparty/QMarkdown-cd865b41ef6038d32d109bdb0eae830ed1eb14a3/include

unix {
    INCLUDEPATH += /usr/include/freetype2
    LIBS += -lftgl -lGL -lGLU -lQMarkdown
    LIBS += -L$$PWD/.lib
}

win32 {
    RC_FILE = $$PWD/windows/version.rc
    # MinGW with msys 1.0
    INCLUDEPATH += C:/MinGW/msys/1.0/local/include
    INCLUDEPATH += C:/MinGW/msys/1.0/local/include/freetype2
    LIBS += -LC:/MinGW/msys/1.0/local/lib
    LIBS += -lftgl -lopengl32 -lglu32 -lQMarkdown
    LIBS += -L$$PWD/.lib
}
