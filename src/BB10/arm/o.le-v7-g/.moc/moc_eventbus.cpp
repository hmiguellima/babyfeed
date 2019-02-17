/****************************************************************************
** Meta object code from reading C++ file 'eventbus.h'
**
** Created: Mon 21. Jan 03:54:09 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/model/eventbus.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eventbus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EventBus[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x05,
      36,   10,    9,    9, 0x05,
      63,   58,    9,    9, 0x05,
      80,   58,    9,    9, 0x05,
      99,    9,    9,    9, 0x05,
     116,   58,    9,    9, 0x05,
     138,   58,    9,    9, 0x05,
     166,   58,    9,    9, 0x05,
     195,    9,    9,    9, 0x05,
     215,    9,    9,    9, 0x05,
     239,  234,    9,    9, 0x05,
     269,    9,    9,    9, 0x05,
     288,   58,    9,    9, 0x05,
     308,   58,    9,    9, 0x05,
     327,    9,    9,    9, 0x05,
     339,   10,    9,    9, 0x05,
     362,   10,    9,    9, 0x05,
     384,   58,    9,    9, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_EventBus[] = {
    "EventBus\0\0event\0eventAdded(PEvent&)\0"
    "eventDeleted(PEvent&)\0baby\0babyAdded(Baby&)\0"
    "babyDeleted(Baby&)\0showMainScreen()\0"
    "showBabyScreen(Baby&)\0showCheckInOutScreen(Baby&)\0"
    "showManualEventScreen(Baby&)\0"
    "showOptionsScreen()\0showCameraScreen()\0"
    "data\0babyPhotoCaptured(QByteArray)\0"
    "babyPhotoAborted()\0babySelected(Baby&)\0"
    "babyUpdated(Baby&)\0dataReset()\0"
    "showEventInfo(PEvent&)\0eventUpdated(PEvent&)\0"
    "showReportScreen(Baby&)\0"
};

void EventBus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EventBus *_t = static_cast<EventBus *>(_o);
        switch (_id) {
        case 0: _t->eventAdded((*reinterpret_cast< PEvent(*)>(_a[1]))); break;
        case 1: _t->eventDeleted((*reinterpret_cast< PEvent(*)>(_a[1]))); break;
        case 2: _t->babyAdded((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 3: _t->babyDeleted((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 4: _t->showMainScreen(); break;
        case 5: _t->showBabyScreen((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 6: _t->showCheckInOutScreen((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 7: _t->showManualEventScreen((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 8: _t->showOptionsScreen(); break;
        case 9: _t->showCameraScreen(); break;
        case 10: _t->babyPhotoCaptured((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 11: _t->babyPhotoAborted(); break;
        case 12: _t->babySelected((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 13: _t->babyUpdated((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 14: _t->dataReset(); break;
        case 15: _t->showEventInfo((*reinterpret_cast< PEvent(*)>(_a[1]))); break;
        case 16: _t->eventUpdated((*reinterpret_cast< PEvent(*)>(_a[1]))); break;
        case 17: _t->showReportScreen((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EventBus::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EventBus::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EventBus,
      qt_meta_data_EventBus, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EventBus::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EventBus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EventBus::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EventBus))
        return static_cast<void*>(const_cast< EventBus*>(this));
    return QObject::qt_metacast(_clname);
}

int EventBus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void EventBus::eventAdded(PEvent & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EventBus::eventDeleted(PEvent & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void EventBus::babyAdded(Baby & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void EventBus::babyDeleted(Baby & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void EventBus::showMainScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void EventBus::showBabyScreen(Baby & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void EventBus::showCheckInOutScreen(Baby & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void EventBus::showManualEventScreen(Baby & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void EventBus::showOptionsScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void EventBus::showCameraScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void EventBus::babyPhotoCaptured(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void EventBus::babyPhotoAborted()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void EventBus::babySelected(Baby & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void EventBus::babyUpdated(Baby & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void EventBus::dataReset()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}

// SIGNAL 15
void EventBus::showEventInfo(PEvent & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void EventBus::eventUpdated(PEvent & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void EventBus::showReportScreen(Baby & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}
QT_END_MOC_NAMESPACE
