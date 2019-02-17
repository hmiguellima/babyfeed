HEADERS += xqcalendar.h \
    xqcalendar_p.h \
    xqcalendarentry.h \
    xqcalendarentry_p.h \

SOURCES += xqcalendar.cpp \
    xqcalendar_p.cpp \
    xqcalendarentry.cpp

symbian:LIBS += -lcalinterimapi \
    -lestor \
    -lefsrv
