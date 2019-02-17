#ifndef ALARMS_GLOBAL_H
#define ALARMS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XQALARMS_LIBRARY)
#  define XQALARMS_EXPORT Q_DECL_EXPORT
#else
#  if defined(XQALARMS_NO_LIBRARY)
#    define XQALARMS_EXPORT
#  else
#    define XQALARMS_EXPORT Q_DECL_IMPORT
#  endif
#endif

#endif // ALARMS_GLOBAL_H
