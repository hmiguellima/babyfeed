#ifndef MESSAGING_GLOBAL_H
#define MESSAGING_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XQMESSAGING_LIBRARY)
#  define XQMESSAGING_EXPORT Q_DECL_EXPORT
#else
#  if defined(XQMESSAGING_NO_LIBRARY)
#    define XQMESSAGING_EXPORT
#  else
#    define XQMESSAGING_EXPORT Q_DECL_IMPORT
#  endif
#endif

#endif // MESSAGING_GLOBAL_H
