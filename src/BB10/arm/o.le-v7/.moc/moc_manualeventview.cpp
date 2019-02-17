/****************************************************************************
** Meta object code from reading C++ file 'manualeventview.h'
**
** Created: Sun 27. Jan 17:56:51 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/view/manualeventview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'manualeventview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ManualEventView[] = {

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
      17,   16,   16,   16, 0x05,
      24,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   16,   16,   16, 0x0a,
      57,   16,   16,   16, 0x08,
      70,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ManualEventView[] = {
    "ManualEventView\0\0save()\0deleteEvent()\0"
    "handleActivation()\0handleSave()\0"
    "handleDelete()\0"
};

void ManualEventView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ManualEventView *_t = static_cast<ManualEventView *>(_o);
        switch (_id) {
        case 0: _t->save(); break;
        case 1: _t->deleteEvent(); break;
        case 2: _t->handleActivation(); break;
        case 3: _t->handleSave(); break;
        case 4: _t->handleDelete(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ManualEventView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ManualEventView::staticMetaObject = {
    { &View::staticMetaObject, qt_meta_stringdata_ManualEventView,
      qt_meta_data_ManualEventView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ManualEventView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ManualEventView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ManualEventView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManualEventView))
        return static_cast<void*>(const_cast< ManualEventView*>(this));
    return View::qt_metacast(_clname);
}

int ManualEventView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ManualEventView::save()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ManualEventView::deleteEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
