/****************************************************************************
** Meta object code from reading C++ file 'fieldmodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../final_final/fieldmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fieldmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FieldModel_t {
    const uint offsetsAndSize[46];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_FieldModel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_FieldModel_t qt_meta_stringdata_FieldModel = {
    {
QT_MOC_LITERAL(0, 10), // "FieldModel"
QT_MOC_LITERAL(11, 12), // "changePlayer"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 24), // "sendCoordsOfOccupiedArea"
QT_MOC_LITERAL(50, 15), // "repaintAllAreas"
QT_MOC_LITERAL(66, 10), // "repaintAll"
QT_MOC_LITERAL(77, 17), // "sendPointToServer"
QT_MOC_LITERAL(95, 5), // "index"
QT_MOC_LITERAL(101, 9), // "addPoints"
QT_MOC_LITERAL(111, 6), // "player"
QT_MOC_LITERAL(118, 6), // "points"
QT_MOC_LITERAL(125, 8), // "gameOver"
QT_MOC_LITERAL(134, 23), // "getCoordsOfOccupiedArea"
QT_MOC_LITERAL(158, 13), // "onDfsFinished"
QT_MOC_LITERAL(172, 8), // "dfsStart"
QT_MOC_LITERAL(181, 15), // "getAreaForPaint"
QT_MOC_LITERAL(197, 13), // "QList<QPoint>"
QT_MOC_LITERAL(211, 4), // "area"
QT_MOC_LITERAL(216, 12), // "getAreaOwner"
QT_MOC_LITERAL(229, 10), // "areasCount"
QT_MOC_LITERAL(240, 10), // "onlineGame"
QT_MOC_LITERAL(251, 7), // "columns"
QT_MOC_LITERAL(259, 4) // "rows"

    },
    "FieldModel\0changePlayer\0\0"
    "sendCoordsOfOccupiedArea\0repaintAllAreas\0"
    "repaintAll\0sendPointToServer\0index\0"
    "addPoints\0player\0points\0gameOver\0"
    "getCoordsOfOccupiedArea\0onDfsFinished\0"
    "dfsStart\0getAreaForPaint\0QList<QPoint>\0"
    "area\0getAreaOwner\0areasCount\0onlineGame\0"
    "columns\0rows"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FieldModel[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       4,  112, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    4 /* Public */,
       3,    0,   87,    2, 0x06,    5 /* Public */,
       4,    0,   88,    2, 0x06,    6 /* Public */,
       5,    0,   89,    2, 0x06,    7 /* Public */,
       6,    1,   90,    2, 0x06,    8 /* Public */,
       8,    2,   93,    2, 0x06,   10 /* Public */,
      11,    0,   98,    2, 0x06,   13 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    0,   99,    2, 0x0a,   14 /* Public */,
      13,    0,  100,    2, 0x0a,   15 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      14,    2,  101,    2, 0x02,   16 /* Public */,
      15,    1,  106,    2, 0x02,   19 /* Public */,
      18,    1,  109,    2, 0x02,   21 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    9,
    0x80000000 | 16, QMetaType::Int,   17,
    QMetaType::Int, QMetaType::Int,   17,

 // properties: name, type, flags
      19, QMetaType::Int, 0x00015401, uint(-1), 0,
      20, QMetaType::Int, 0x00015401, uint(-1), 0,
      21, QMetaType::Int, 0x00015401, uint(-1), 0,
      22, QMetaType::Int, 0x00015401, uint(-1), 0,

       0        // eod
};

void FieldModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FieldModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changePlayer(); break;
        case 1: _t->sendCoordsOfOccupiedArea(); break;
        case 2: _t->repaintAllAreas(); break;
        case 3: _t->repaintAll(); break;
        case 4: _t->sendPointToServer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->addPoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->gameOver(); break;
        case 7: _t->getCoordsOfOccupiedArea(); break;
        case 8: _t->onDfsFinished(); break;
        case 9: _t->dfsStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: { QList<QPoint> _r = _t->getAreaForPaint((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QPoint>*>(_a[0]) = std::move(_r); }  break;
        case 11: { int _r = _t->getAreaOwner((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FieldModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FieldModel::changePlayer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FieldModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FieldModel::sendCoordsOfOccupiedArea)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FieldModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FieldModel::repaintAllAreas)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FieldModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FieldModel::repaintAll)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FieldModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FieldModel::sendPointToServer)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FieldModel::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FieldModel::addPoints)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FieldModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FieldModel::gameOver)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FieldModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->areasCount(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->onlineGame(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->columnCountForQml(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->rowCountForQml(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject FieldModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_FieldModel.offsetsAndSize,
    qt_meta_data_FieldModel,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_FieldModel_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QVector<QPoint>, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *FieldModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FieldModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FieldModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int FieldModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FieldModel::changePlayer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FieldModel::sendCoordsOfOccupiedArea()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FieldModel::repaintAllAreas()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FieldModel::repaintAll()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void FieldModel::sendPointToServer(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FieldModel::addPoints(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FieldModel::gameOver()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
