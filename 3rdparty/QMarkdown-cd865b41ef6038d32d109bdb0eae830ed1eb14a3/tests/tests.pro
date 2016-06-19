TARGET = QMarkdownTest
CONFIG += console
CONFIG -= app_bundle
QT += testlib

TEMPLATE = app

SOURCES += \
    main.cpp \
    test_apis.cpp \
    test_etree.cpp \
    test_pypp.cpp \
    test_basic.cpp \
    test_misc.cpp \
    test_safemode.cpp \
    test_options.cpp \
    test_extensions.cpp

HEADERS += \
    test_apis.h \
    test_etree.h \
    test_pypp.h \
    test_basic.h \
    test_misc.h \
    test_safemode.h \
    test_options.h \
    test_extensions.h

INCLUDEPATH += ../src/

include($$PWD/../src/src.pri)
