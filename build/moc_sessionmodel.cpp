/****************************************************************************
** Meta object code from reading C++ file 'sessionmodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../final_final/sessionmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sessionmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SessionModel_t {
    const uint offsetsAndSize[54];
    char stringdata0[301];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_SessionModel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_SessionModel_t qt_meta_stringdata_SessionModel = {
    {
QT_MOC_LITERAL(0, 12), // "SessionModel"
QT_MOC_LITERAL(13, 11), // "addedPoints"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 10), // "sendWinner"
QT_MOC_LITERAL(37, 12), // "modelChanged"
QT_MOC_LITERAL(50, 11), // "readyToMove"
QT_MOC_LITERAL(62, 9), // "addPoints"
QT_MOC_LITERAL(72, 6), // "player"
QT_MOC_LITERAL(79, 6), // "points"
QT_MOC_LITERAL(86, 7), // "endGame"
QT_MOC_LITERAL(94, 17), // "sendPointToServer"
QT_MOC_LITERAL(112, 5), // "index"
QT_MOC_LITERAL(118, 11), // "onReadyRead"
QT_MOC_LITERAL(130, 16), // "changeFieldModel"
QT_MOC_LITERAL(147, 9), // "saveModel"
QT_MOC_LITERAL(157, 8), // "QString&"
QT_MOC_LITERAL(166, 8), // "fileName"
QT_MOC_LITERAL(175, 9), // "loadModel"
QT_MOC_LITERAL(185, 11), // "playerColor"
QT_MOC_LITERAL(197, 18), // "playerColorForArea"
QT_MOC_LITERAL(216, 14), // "connectRequest"
QT_MOC_LITERAL(231, 10), // "nextPlayer"
QT_MOC_LITERAL(242, 18), // "showSettingsDialog"
QT_MOC_LITERAL(261, 5), // "model"
QT_MOC_LITERAL(267, 11), // "FieldModel*"
QT_MOC_LITERAL(279, 6), // "winner"
QT_MOC_LITERAL(286, 14) // "onlineMoveFlag"

    },
    "SessionModel\0addedPoints\0\0sendWinner\0"
    "modelChanged\0readyToMove\0addPoints\0"
    "player\0points\0endGame\0sendPointToServer\0"
    "index\0onReadyRead\0changeFieldModel\0"
    "saveModel\0QString&\0fileName\0loadModel\0"
    "playerColor\0playerColorForArea\0"
    "connectRequest\0nextPlayer\0showSettingsDialog\0"
    "model\0FieldModel*\0winner\0onlineMoveFlag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SessionModel[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       4,  144, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x06,    4 /* Public */,
       3,    2,  111,    2, 0x06,    5 /* Public */,
       4,    0,  116,    2, 0x06,    8 /* Public */,
       5,    0,  117,    2, 0x06,    9 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    2,  118,    2, 0x08,   10 /* Private */,
       9,    0,  123,    2, 0x08,   13 /* Private */,
      10,    1,  124,    2, 0x08,   14 /* Private */,
      12,    0,  127,    2, 0x08,   16 /* Private */,
      13,    0,  128,    2, 0x08,   17 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      14,    1,  129,    2, 0x02,   18 /* Public */,
      17,    1,  132,    2, 0x02,   20 /* Public */,
      18,    1,  135,    2, 0x02,   22 /* Public */,
      19,    1,  138,    2, 0x02,   24 /* Public */,
      20,    0,  141,    2, 0x02,   26 /* Public */,
      21,    0,  142,    2, 0x02,   27 /* Public */,
      22,    0,  143,    2, 0x02,   28 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::QColor, QMetaType::Int,    2,
    QMetaType::QColor, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::Int, 0x00015401, uint(-1), 0,
      23, 0x80000000 | 24, 0x0001500b, uint(2), 0,
      25, QMetaType::Int, 0x00015401, uint(-1), 0,
      26, QMetaType::Int, 0x00015401, uint(-1), 0,

       0        // eod
};

void SessionModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SessionModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addedPoints(); break;
        case 1: _t->sendWinner((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->modelChanged(); break;
        case 3: _t->readyToMove(); break;
        case 4: _t->addPoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->endGame(); break;
        case 6: _t->sendPointToServer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onReadyRead(); break;
        case 8: _t->changeFieldModel(); break;
        case 9: _t->saveModel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->loadModel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: { QColor _r = _t->playerColor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 12: { QColor _r = _t->playerColorForArea((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->connectRequest(); break;
        case 14: _t->nextPlayer(); break;
        case 15: _t->showSettingsDialog(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SessionModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SessionModel::addedPoints)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SessionModel::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SessionModel::sendWinner)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SessionModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SessionModel::modelChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SessionModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SessionModel::readyToMove)) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FieldModel* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SessionModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->player(); break;
        case 1: *reinterpret_cast< FieldModel**>(_v) = _t->pModel(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->winner(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->abilityToMakeMoveInOnline(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SessionModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setPModel(*reinterpret_cast< FieldModel**>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject SessionModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_SessionModel.offsetsAndSize,
    qt_meta_data_SessionModel,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_SessionModel_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<FieldModel*, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

>,
    nullptr
} };


const QMetaObject *SessionModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SessionModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SessionModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int SessionModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
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
void SessionModel::addedPoints()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SessionModel::sendWinner(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SessionModel::modelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SessionModel::readyToMove()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
