/****************************************************************************
** Meta object code from reading C++ file 'checkinoutview.h'
**
** Created: Sat 26. Jan 17:22:33 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/view/checkinoutview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkinoutview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CheckInOutView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      31,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   15,   15,   15, 0x0a,
      64,   15,   15,   15, 0x0a,
      85,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CheckInOutView[] = {
    "CheckInOutView\0\0startClicked()\0"
    "stopClicked()\0handleActivation()\0"
    "handleStartClicked()\0handleStopClicked()\0"
};

void CheckInOutView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckInOutView *_t = static_cast<CheckInOutView *>(_o);
        switch (_id) {
        case 0: _t->startClicked(); break;
        case 1: _t->stopClicked(); break;
        case 2: _t->handleActivation(); break;
        case 3: _t->handleStartClicked(); break;
        case 4: _t->handleStopClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CheckInOutView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckInOutView::staticMetaObject = {
    { &View::staticMetaObject, qt_meta_stringdata_CheckInOutView,
      qt_meta_data_CheckInOutView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckInOutView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckInOutView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckInOutView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckInOutView))
        return static_cast<void*>(const_cast< CheckInOutView*>(this));
    return View::qt_metacast(_clname);
}

int CheckInOutView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = View::qt_metacall(_c, _id, _a);
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
void CheckInOutView::startClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CheckInOutView::stopClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
