#-------------------------------------------------
#
# Project created by QtCreator 2025-06-03T18:45:17
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gestion_Maison
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    table_hachage.cpp \
    SeConnecter.cpp \
    displayhousedialog.cpp

HEADERS  += mainwindow.h \
    SeConnecter.h \
    table_hachage.h \
    displayhousedialog.h

FORMS    += mainwindow.ui
