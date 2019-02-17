/****************************************************************************
** Meta object code from reading C++ file 'babyscreen.h'
**
** Created: Thu 28. Feb 11:49:12 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/babyscreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'babyscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BabyScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      36,   31,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,
      71,   11,   11,   11, 0x08,
      84,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     115,   11,   11,   11, 0x08,
     136,   11,   11,   11, 0x08,
     157,   11,   11,   11, 0x08,
     192,  184,   11,   11, 0x08,
     213,  184,   11,   11, 0x08,
     236,   11,   11,   11, 0x08,
     264,  256,   11,   11, 0x08,
     313,   11,   11,   11, 0x08,
     327,   11,   11,   11, 0x08,
     341,   11,   11,   11, 0x08,
     357,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BabyScreen[] = {
    "BabyScreen\0\0viewReadyHandler()\0baby\0"
    "onShowBabyScreen(Baby&)\0saveBaby()\0"
    "deleteBaby()\0updateTitle()\0updateBabyView()\0"
    "handlePhotoClicked()\0handleTimerClicked()\0"
    "handleManualEventClicked()\0eventId\0"
    "handleEditEvent(int)\0handleDeleteEvent(int)\0"
    "handleShowReports()\0message\0"
    "handleChildCardDone(bb::system::CardDoneMessage)\0"
    "showNextDay()\0showPrevDay()\0showNextMonth()\0"
    "showPrevMonth()\0"
};

void BabyScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BabyScreen *_t = static_cast<BabyScreen *>(_o);
        switch (_id) {
        case 0: _t->viewReadyHandler(); break;
        case 1: _t->onShowBabyScreen((*reinterpret_cast< Baby(*)>(_a[1]))); break;
        case 2: _t->saveBaby(); break;
        case 3: _t->deleteBaby(); break;
        case 4: _t->updateTitle(); break;
        case 5: _t->updateBabyView(); break;
        case 6: _t->handlePhotoClicked(); break;
        case 7: _t->handleTimerClicked(); break;
        case 8: _t->handleManualEventClicked(); break;
        case 9: _t->handleEditEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->handleDeleteEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->handleShowReports(); break;
        case 12: _t->handleChildCardDone((*reinterpret_cast< const bb::system::CardDoneMessage(*)>(_a[1]))); break;
        case 13: _t->showNextDay(); break;
        case 14: _t->showPrevDay(); break;
        case 15: _t->showNextMonth(); break;
        case 16: _t->showPrevMonth(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BabyScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BabyScreen::staticMetaObject = {
    { &Screen::staticMetaObject, qt_meta_stringdata_BabyScreen,
      qt_meta_data_BabyScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BabyScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BabyScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BabyScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BabyScreen))
        return static_cast<void*>(const_cast< BabyScreen*>(this));
    return Screen::qt_metacast(_clname);
}

int BabyScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Screen::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
