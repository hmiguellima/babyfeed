#ifndef CONTACTS_GLOBAL_H
#define CONTACTS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XQCONTACTS_LIBRARY)
#  define XQCONTACTS_EXPORT Q_DECL_EXPORT
#else
#  if defined(XQCONTACTS_NO_LIBRARY)
#    define XQCONTACTS_EXPORT
#  else
#    define XQCONTACTS_EXPORT Q_DECL_IMPORT
#  endif
#endif

#endif // CONTACTS_GLOBAL_H
