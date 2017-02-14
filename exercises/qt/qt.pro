
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
SOURCES += \
    window.cpp \
    main.cpp \
    qinvtablewidget.cpp

HEADERS += \
    window.h \
    qinvtablewidget.h
