/****************************************************************************
** Meta object code from reading C++ file 'dfsthread.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../final_final/dfsthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dfsthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DfsThread_t {
    const uint offsetsAndSize[10];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DfsThread_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DfsThread_t qt_meta_stringdata_DfsThread = {
    {
QT_MOC_LITERAL(0, 9), // "DfsThread"
QT_MOC_LITERAL(10, 11), // "dfsFinished"
QT_MOC_LITERAL(22, 0), // ""
QT_MOC_LITERAL(23, 22), // "cycleIsReadyForRepaint"
QT_MOC_LITERAL(46, 4) // "area"

    },
    "DfsThread\0dfsFinished\0\0cycleIsReadyForRepaint\0"
    "area"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DfsThread[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x06,    0 /* Public */,
       3,    1,   27,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void DfsThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DfsThread *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dfsFinished(); break;
        case 1: _t->cycleIsReadyForRepaint((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DfsThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DfsThread::dfsFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DfsThread::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DfsThread::cycleIsReadyForRepaint)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DfsThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_DfsThread.offsetsAndSize,
    qt_meta_data_DfsThread,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DfsThread_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>



>,
    nullptr
} };


const QMetaObject *DfsThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DfsThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DfsThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int DfsThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DfsThread::dfsFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DfsThread::cycleIsReadyForRepaint(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
