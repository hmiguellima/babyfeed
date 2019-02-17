/****************************************************************************
** Meta object code from reading C++ file 'baby.h'
**
** Created: Mon 21. Jan 03:54:08 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/model/baby.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'baby.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Baby[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       4,   19, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

 // properties: name, type, flags
      32,   24, 0x0a095001,
      37,   24, 0x0a095001,
      43,   24, 0x0a095001,
      47,   24, 0x0a095001,

       0        // eod
};

static const char qt_meta_stringdata_Baby[] = {
    "Baby\0\0birthdayChanged()\0QString\0name\0"
    "photo\0age\0measures\0"
};

void Baby::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Baby *_t = static_cast<Baby *>(_o);
        switch (_id) {
        case 0: _t->birthdayChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Baby::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Baby::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Baby,
      qt_meta_data_Baby, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Baby::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Baby::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Baby::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Baby))
        return static_cast<void*>(const_cast< Baby*>(this));
    return QObject::qt_metacast(_clname);
}

int Baby::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = getName(); break;
        case 1: *reinterpret_cast< QString*>(_v) = getPhoto(); break;
        case 2: *reinterpret_cast< QString*>(_v) = getAge(); break;
        case 3: *reinterpret_cast< QString*>(_v) = getLastMeasures(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Baby::birthdayChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
