#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T10:27:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCalculator
TEMPLATE = app


SOURCES += main.cpp\
    CalcOperations.cpp \
    CalculatorUI.cpp \
    ICCalculator.cpp

HEADERS  += \
    CalcOperations.h \
    CalculatorUI.h \
    ICCalculator.h
