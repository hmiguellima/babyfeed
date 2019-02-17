/****************************************************************************
** Meta object code from reading C++ file 'babyview.h'
**
** Created: Thu 28. Feb 11:49:34 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/view/babyview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'babyview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BabyView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      21,    9,    9,    9, 0x05,
      30,    9,    9,    9, 0x05,
      43,    9,    9,    9, 0x05,
      59,    9,    9,    9, 0x05,
      80,    9,    9,    9, 0x05,
     110,  102,    9,    9, 0x05,
     125,  102,    9,    9, 0x05,
     142,    9,    9,    9, 0x05,
     156,    9,    9,    9, 0x05,
     176,    9,    9,    9, 0x05,
     196,    9,    9,    9, 0x05,
     218,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     240,    9,    9,    9, 0x0a,
     259,    9,    9,    9, 0x08,
     274,    9,    9,    9, 0x08,
     287,    9,    9,    9, 0x08,
     308,    9,    9,    9, 0x08,
     329,    9,    9,    9, 0x08,
     356,    9,    9,    9, 0x08,
     371,  102,    9,    9, 0x08,
     392,  102,    9,    9, 0x08,
     415,    9,    9,    9, 0x08,
     431,    9,    9,    9, 0x08,
     455,    9,    9,    9, 0x08,
     479,    9,    9,    9, 0x08,
     504,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BabyView[] = {
    "BabyView\0\0saveBaby()\0cancel()\0"
    "deleteBaby()\0photoCaptured()\0"
    "registerTimerEvent()\0registerManualEvent()\0"
    "eventId\0editEvent(int)\0deleteEvent(int)\0"
    "showReports()\0prevDayBtnClicked()\0"
    "nextDayBtnClicked()\0prevMonthBtnClicked()\0"
    "nextMonthBtnClicked()\0handleActivation()\0"
    "handleDelete()\0handleSave()\0"
    "handlePhotoClicked()\0handleTimerClicked()\0"
    "handleManualEventClicked()\0handleCancel()\0"
    "handleEditEvent(int)\0handleDeleteEvent(int)\0"
    "handleReports()\0handlePrevDateClicked()\0"
    "handleNextDateClicked()\0"
    "handlePrevMonthClicked()\0"
    "handleNextMonthClicked()\0"
};

void BabyView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BabyView *_t = static_cast<BabyView *>(_o);
        switch (_id) {
        case 0: _t->saveBaby(); break;
        case 1: _t->cancel(); break;
        case 2: _t->deleteBaby(); break;
        case 3: _t->photoCaptured(); break;
        case 4: _t->registerTimerEvent(); break;
        case 5: _t->registerManualEvent(); break;
        case 6: _t->editEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->deleteEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->showReports(); break;
        case 9: _t->prevDayBtnClicked(); break;
        case 10: _t->nextDayBtnClicked(); break;
        case 11: _t->prevMonthBtnClicked(); break;
        case 12: _t->nextMonthBtnClicked(); break;
        case 13: _t->handleActivation(); break;
        case 14: _t->handleDelete(); break;
        case 15: _t->handleSave(); break;
        case 16: _t->handlePhotoClicked(); break;
        case 17: _t->handleTimerClicked(); break;
        case 18: _t->handleManualEventClicked(); break;
        case 19: _t->handleCancel(); break;
        case 20: _t->handleEditEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->handleDeleteEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->handleReports(); break;
        case 23: _t->handlePrevDateClicked(); break;
        case 24: _t->handleNextDateClicked(); break;
        case 25: _t->handlePrevMonthClicked(); break;
        case 26: _t->handleNextMonthClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BabyView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BabyView::staticMetaObject = {
    { &View::staticMetaObject, qt_meta_stringdata_BabyView,
      qt_meta_data_BabyView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BabyView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BabyView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BabyView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BabyView))
        return static_cast<void*>(const_cast< BabyView*>(this));
    return View::qt_metacast(_clname);
}

int BabyView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = View::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void BabyView::saveBaby()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BabyView::cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void BabyView::deleteBaby()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void BabyView::photoCaptured()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void BabyView::registerTimerEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void BabyView::registerManualEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void BabyView::editEvent(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void BabyView::deleteEvent(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void BabyView::showReports()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void BabyView::prevDayBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void BabyView::nextDayBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void BabyView::prevMonthBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void BabyView::nextMonthBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}
QT_END_MOC_NAMESPACE
