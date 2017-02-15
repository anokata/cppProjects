
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
QT += sql
# QT += multimedia
QT += phonon

# Input
SOURCES += \
    window.cpp \
    main.cpp \
    qinvtablewidget.cpp \
    item.cpp \
    inventory.cpp \
    qonecellwidget.cpp

HEADERS += \
    window.h \
    qinvtablewidget.h \
    item.h \
    inventory.h \
    qonecellwidget.h
