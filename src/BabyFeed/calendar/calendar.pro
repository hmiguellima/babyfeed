TARGET = xqcalendar
TEMPLATE = lib
QT = core gui

DEFINES += XQCALENDAR_LIBRARY
include(calendar.pri)

symbian:TARGET.CAPABILITY = All -TCB -AllFiles -DRM
symbian:TARGET.EPOCALLOWDLLDATA = 1
