#-------------------------------------------------
#
# Project created by QtCreator 2025-05-29T01:39:02
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gestion_Maisons
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    table_hachage.cpp \
    SeConnecter.cpp

HEADERS  += mainwindow.h \
    table_hachage.h \
    SeConnecter.h

FORMS    += mainwindow.ui
