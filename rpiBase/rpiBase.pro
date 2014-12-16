#-------------------------------------------------
#
# Project created by QtCreator 2014-10-28T20:19:28
#
#-------------------------------------------------

VERSION = 1.0.0


QT += core
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rpiBase
TEMPLATE = lib

SOURCES += exception.cpp

HEADERS += command_defs.h exception.h name_defs.h rpibase_global.h

include($$lower($$join(CONFIGNAME,,,.pro)))

DEFINES += RPIBASE_LIBRARY
DEFINES += QTJSONSETTINGS_EXPORTS

include(../../qtjsonsettings/qtjsonsettings.pri)
include(../../Qt-Solutions/QtService/src/QtService.pri)

QMAKE_CFLAGS 	+= $$COMMONFLAGS
QMAKE_CXXFLAGS 	+= $$COMMONFLAGS
QMAKE_LFLAGS 	+= $$COMMONFLAGS

OBJECTS_DIR = $$DESTDIR
MOC_DIR     = $$DESTDIR
RCC_DIR     = $$DESTDIR
UI_DIR      = $$DESTDIR
