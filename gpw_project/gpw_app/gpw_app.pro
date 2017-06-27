#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T21:41:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = gpw_app
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp \
    login.cpp \
    additemwindow.cpp \
    stockitem.cpp \
    qcustomplot.cpp \
    adduser.cpp \
    buyitem.cpp \
    addname.cpp \
    func.cpp \
    newprice.cpp \
    sellitem.cpp

HEADERS  += mainwindow.h \
    user.h \
    login.h \
    additemwindow.h \
    stockitem.h \
    qcustomplot.h \
    adduser.h \
    buyitem.h \
    addname.h \
    func.h \
    newprice.h \
    sellitem.h

FORMS    += mainwindow.ui \
    login.ui \
    additemwindow.ui \
    adduser.ui \
    buyitem.ui \
    addname.ui \
    newprice.ui \
    sellitem.ui

RESOURCES += \
    resources.qrc
