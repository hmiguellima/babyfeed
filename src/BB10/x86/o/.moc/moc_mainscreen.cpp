/****************************************************************************
** Meta object code from reading C++ file 'mainscreen.h'
**
** Created: Fri 1. Mar 00:13:26 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/mainscreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      38,   31,   11,   11, 0x08,
      62,   31,   11,   11, 0x08,
      84,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainScreen[] = {
    "MainScreen\0\0viewReadyHandler()\0babyId\0"
    "handleShowBabyPage(int)\0handleDeleteBaby(int)\0"
    "updateMainView()\0"
};

void MainScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainScreen *_t = static_cast<MainScreen *>(_o);
        switch (_id) {
        case 0: _t->viewReadyHandler(); break;
        case 1: _t->handleShowBabyPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->handleDeleteBaby((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateMainView(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainScreen::staticMetaObject = {
    { &Screen::staticMetaObject, qt_meta_stringdata_MainScreen,
      qt_meta_data_MainScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainScreen))
        return static_cast<void*>(const_cast< MainScreen*>(this));
    return Screen::qt_metacast(_clname);
}

int MainScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Screen::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
