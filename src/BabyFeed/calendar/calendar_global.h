#ifndef CALENDAR_GLOBAL_H
#define CALENDAR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XQCALENDAR_LIBRARY)
#  define XQCALENDAR_EXPORT Q_DECL_EXPORT
#else
#  if defined(XQCALENDAR_NO_LIBRARY)
#    define XQCALENDAR_EXPORT
#  else
#    define XQCALENDAR_EXPORT Q_DECL_IMPORT
#  endif
#endif

#endif // CALENDAR_GLOBAL_H
