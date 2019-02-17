/****************************************************************************
** Meta object code from reading C++ file 'BabyFeedApp.hpp'
**
** Created: Sun 27. Jan 18:19:18 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/BabyFeedApp.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BabyFeedApp.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BabyFeedApp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      20,   12,   12,   12, 0x0a,
      28,   12,   12,   12, 0x0a,
      35,   12,   12,   12, 0x08,
      52,   12,   12,   12, 0x08,
      64,   12,   12,   12, 0x08,
      79,   12,   12,   12, 0x08,
      88,   12,   12,   12, 0x08,
      98,   12,   12,   12, 0x08,
     109,   12,   12,   12, 0x08,
     130,  125,   12,   12, 0x08,
     153,  148,   12,   12, 0x08,
     191,  185,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BabyFeedApp[] = {
    "BabyFeedApp\0\0init()\0start()\0test()\0"
    "showMainScreen()\0showAbout()\0"
    "initDatabase()\0backup()\0restore()\0"
    "showHelp()\0updateVersion()\0lang\0"
    "initLang(QString)\0name\0"
    "handleScreenActivation(QString)\0email\0"
    "exportEventsToExcel(QString)\0"
};

void BabyFeedApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BabyFeedApp *_t = static_cast<BabyFeedApp *>(_o);
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->start(); break;
        case 2: _t->test(); break;
        case 3: _t->showMainScreen(); break;
        case 4: _t->showAbout(); break;
        case 5: _t->initDatabase(); break;
        case 6: _t->backup(); break;
        case 7: _t->restore(); break;
        case 8: _t->showHelp(); break;
        case 9: _t->updateVersion(); break;
        case 10: _t->initLang((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->handleScreenActivation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->exportEventsToExcel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BabyFeedApp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BabyFeedApp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BabyFeedApp,
      qt_meta_data_BabyFeedApp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BabyFeedApp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BabyFeedApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BabyFeedApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BabyFeedApp))
        return static_cast<void*>(const_cast< BabyFeedApp*>(this));
    return QObject::qt_metacast(_clname);
}

int BabyFeedApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
