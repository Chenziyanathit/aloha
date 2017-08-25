#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T13:24:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aloha
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    net_topo_para.cpp \
    channel.cpp \
    Plot.cpp

HEADERS  += mainwindow.h \
    channel_para.h \
    net_topo_para.h \
    Plot.h

FORMS    += mainwindow.ui
# IT++
LIBS += `/usr/bin/itpp-config --static --libs`
LIBS += `/usr/local/bin/itpp-config --static --libs`

INCLUDEPATH += /usr/local/qwt-5.2.3/include
LIBS += -L"/usr/local/qwt-5.2.3/lib/" -lqwt
