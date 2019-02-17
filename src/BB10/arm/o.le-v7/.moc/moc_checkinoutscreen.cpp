/****************************************************************************
** Meta object code from reading C++ file 'checkinoutscreen.h'
**
** Created: Sun 20. Jan 23:27:34 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/checkinoutscreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkinoutscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CheckInOutScreen[] = {

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
      18,   17,   17,   17, 0x0a,
      42,   37,   17,   17, 0x08,
      72,   17,   17,   17, 0x08,
      86,   17,   17,   17, 0x08,
      99,   17,   17,   17, 0x08,
     113,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CheckInOutScreen[] = {
    "CheckInOutScreen\0\0viewReadyHandler()\0"
    "baby\0onShowCheckInOutScreen(Baby&)\0"
    "handleStart()\0handleStop()\0displayTime()\0"
    "handleInactive()\0"
};

void CheckInOutScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckInOutScreen *_t = static_cast<CheckInOutScreen *>(_o);
        switch (_id) {
        case 0: _t->viewReadyHandler(); break;
        case 1: _t->onShowCheckInOutScreen((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 2: _t->handleStart(); break;
        case 3: _t->handleStop(); break;
        case 4: _t->displayTime(); break;
        case 5: _t->handleInactive(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CheckInOutScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckInOutScreen::staticMetaObject = {
    { &Screen::staticMetaObject, qt_meta_stringdata_CheckInOutScreen,
      qt_meta_data_CheckInOutScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckInOutScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckInOutScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckInOutScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckInOutScreen))
        return static_cast<void*>(const_cast< CheckInOutScreen*>(this));
    return Screen::qt_metacast(_clname);
}

int CheckInOutScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
