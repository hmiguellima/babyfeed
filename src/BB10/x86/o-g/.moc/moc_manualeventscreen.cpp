/****************************************************************************
** Meta object code from reading C++ file 'manualeventscreen.h'
**
** Created: Mon 21. Jan 04:15:00 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/manualeventscreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'manualeventscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ManualEventScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      43,   38,   18,   18, 0x08,
      80,   74,   18,   18, 0x08,
     105,   18,   18,   18, 0x08,
     112,   18,   18,   18, 0x08,
     126,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ManualEventScreen[] = {
    "ManualEventScreen\0\0viewReadyHandler()\0"
    "baby\0onShowManualEventScreen(Baby&)\0"
    "event\0onShowEventInfo(PEvent&)\0save()\0"
    "deleteEvent()\0testAlarm()\0"
};

void ManualEventScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ManualEventScreen *_t = static_cast<ManualEventScreen *>(_o);
        switch (_id) {
        case 0: _t->viewReadyHandler(); break;
        case 1: _t->onShowManualEventScreen((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 2: _t->onShowEventInfo((*reinterpret_cast< PEvent(*)>(_a[1]))); break;
        case 3: _t->save(); break;
        case 4: _t->deleteEvent(); break;
        case 5: _t->testAlarm(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ManualEventScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ManualEventScreen::staticMetaObject = {
    { &Screen::staticMetaObject, qt_meta_stringdata_ManualEventScreen,
      qt_meta_data_ManualEventScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ManualEventScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ManualEventScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ManualEventScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManualEventScreen))
        return static_cast<void*>(const_cast< ManualEventScreen*>(this));
    return Screen::qt_metacast(_clname);
}

int ManualEventScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Screen::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
