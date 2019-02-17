TARGET = xqalarms
TEMPLATE = lib
QT = core

DEFINES += XQALARMS_LIBRARY
include(alarms.pri)

symbian:TARGET.CAPABILITY = All -TCB -AllFiles -DRM
symbian:TARGET.EPOCALLOWDLLDATA = 1
