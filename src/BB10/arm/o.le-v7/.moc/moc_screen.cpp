/****************************************************************************
** Meta object code from reading C++ file 'screen.h'
**
** Created: Sun 20. Jan 12:19:52 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/screen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Screen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,    7,    7,    7, 0x0a,
      32,    7,    7,    7, 0x0a,
      51,    7,    7,    7, 0x0a,
      66,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Screen[] = {
    "Screen\0\0screenInactive()\0show()\0"
    "viewReadyHandler()\0notifyActive()\0"
    "notifyInactive()\0"
};

void Screen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Screen *_t = static_cast<Screen *>(_o);
        switch (_id) {
        case 0: _t->screenInactive(); break;
        case 1: _t->show(); break;
        case 2: _t->viewReadyHandler(); break;
        case 3: _t->notifyActive(); break;
        case 4: _t->notifyInactive(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Screen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Screen::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Screen,
      qt_meta_data_Screen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Screen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Screen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Screen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Screen))
        return static_cast<void*>(const_cast< Screen*>(this));
    return QObject::qt_metacast(_clname);
}

int Screen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Screen::screenInactive()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
