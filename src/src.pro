include(../defaults.pri)
QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32 {
  TARGET = ../subtle-cosmic-moose
}
unix {
  TARGET = subtle-cosmic-moose
}
CONFIG -= testlib
TEMPLATE = lib

SOURCES += source/mainwindow.cpp \
    source/database.cpp
HEADERS  += header/mainwindow.h \
    header/database.h
FORMS    += form/mainwindow.ui

QTPLUGIN += qsqlmysql
