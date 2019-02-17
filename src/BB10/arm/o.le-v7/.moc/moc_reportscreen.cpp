/****************************************************************************
** Meta object code from reading C++ file 'reportscreen.h'
**
** Created: Sun 27. Jan 17:56:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/reportscreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reportscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReportScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      38,   33,   13,   13, 0x08,
      62,   56,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ReportScreen[] = {
    "ReportScreen\0\0viewReadyHandler()\0baby\0"
    "showReport(Baby&)\0index\0handleHtmlLoaded(int)\0"
};

void ReportScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReportScreen *_t = static_cast<ReportScreen *>(_o);
        switch (_id) {
        case 0: _t->viewReadyHandler(); break;
        case 1: _t->showReport((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 2: _t->handleHtmlLoaded((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ReportScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReportScreen::staticMetaObject = {
    { &Screen::staticMetaObject, qt_meta_stringdata_ReportScreen,
      qt_meta_data_ReportScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReportScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReportScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReportScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReportScreen))
        return static_cast<void*>(const_cast< ReportScreen*>(this));
    return Screen::qt_metacast(_clname);
}

int ReportScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Screen::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
