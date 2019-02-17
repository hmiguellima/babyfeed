HEADERS += xqalarms.h \
    xqalarms_p.h

SOURCES += xqalarms.cpp \
    xqalarms_p.cpp

symbian:LIBS += -lalarmclient \
    -lalarmshared
