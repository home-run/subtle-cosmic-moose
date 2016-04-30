include(../defaults.pri)

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += source/main.cpp

LIBS += -L../src -lsubtle-cosmic-moose
