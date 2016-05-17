include(../defaults.pri)
QT       += core gui sql multimedia
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
    source/database.cpp \
    source/stadiumdetails.cpp \
    source/homepage.cpp \
    source/plantrip.cpp \
    source/purchasewindow.cpp \
    source/editstadiuminfo.cpp \
    source/tripsummary.cpp \
    source/stadiumtablemodel.cpp \
    source/souvenirtablemodel.cpp \
    source/graph.cpp \
    source/adminlogin.cpp \
    source/addsouvenir.cpp

HEADERS  += header/mainwindow.h \
    header/stadiumdetails.h \
    header/homepage.h \
    header/plantrip.h \
    header/purchasewindow.h \
    header/editstadiuminfo.h \
    header/tripsummary.h \
    header/database.h \
    header/stadiumtablemodel.h \
    header/souvenirtablemodel.h \
    header/graph.h \
    header/adminlogin.h \
    header/Heap.h \
    header/Exceptions.h \
    header/addsouvenir.h \
    header/vertex.h \
    header/vertexqueue.h

FORMS    += form/mainwindow.ui \
    form/stadiumdetails.ui \
    form/homepage.ui \
    form/plantrip.ui \
    form/purchasewindow.ui \
    form/editstadiuminfo.ui \
    form/tripsummary.ui \
    form/adminlogin.ui \
    form/addsouvenir.ui

