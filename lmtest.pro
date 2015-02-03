TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
QT -= gui

HEADERS = gaussian_x.h gaussian_y.h lmmin.h lmcurve.h lmstruct.h zstack_x.h zstack_y.h
SOURCES = main.c lmmin.c lmcurve.c

