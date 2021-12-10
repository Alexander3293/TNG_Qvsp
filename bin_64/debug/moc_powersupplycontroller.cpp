/****************************************************************************
** Meta object code from reading C++ file 'powersupplycontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../work_with_powerSupply/powersupplycontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'powersupplycontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PowerSupplyController_t {
    QByteArrayData data[27];
    char stringdata0[303];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PowerSupplyController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PowerSupplyController_t qt_meta_stringdata_PowerSupplyController = {
    {
QT_MOC_LITERAL(0, 0, 21), // "PowerSupplyController"
QT_MOC_LITERAL(1, 22, 4), // "curr"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "volt"
QT_MOC_LITERAL(4, 33, 9), // "voltLimit"
QT_MOC_LITERAL(5, 43, 9), // "currLimit"
QT_MOC_LITERAL(6, 53, 18), // "msgFromPowerSupply"
QT_MOC_LITERAL(7, 72, 17), // "updatePowerSupply"
QT_MOC_LITERAL(8, 90, 8), // "sendVolt"
QT_MOC_LITERAL(9, 99, 5), // "value"
QT_MOC_LITERAL(10, 105, 8), // "sendCurr"
QT_MOC_LITERAL(11, 114, 20), // "return_Idntity_Query"
QT_MOC_LITERAL(12, 135, 3), // "msg"
QT_MOC_LITERAL(13, 139, 6), // "setLRM"
QT_MOC_LITERAL(14, 146, 4), // "mode"
QT_MOC_LITERAL(15, 151, 12), // "stateUpdated"
QT_MOC_LITERAL(16, 164, 8), // "strState"
QT_MOC_LITERAL(17, 173, 17), // "setUpdateTimeData"
QT_MOC_LITERAL(18, 191, 16), // "timeUpdateDataMs"
QT_MOC_LITERAL(19, 208, 12), // "setCurrLimit"
QT_MOC_LITERAL(20, 221, 12), // "setVoltLimit"
QT_MOC_LITERAL(21, 234, 13), // "readVoltLimit"
QT_MOC_LITERAL(22, 248, 13), // "readCurrLimit"
QT_MOC_LITERAL(23, 262, 7), // "powerOn"
QT_MOC_LITERAL(24, 270, 8), // "powerOff"
QT_MOC_LITERAL(25, 279, 15), // "IdntityQueryMsg"
QT_MOC_LITERAL(26, 295, 7) // "setMode"

    },
    "PowerSupplyController\0curr\0\0volt\0"
    "voltLimit\0currLimit\0msgFromPowerSupply\0"
    "updatePowerSupply\0sendVolt\0value\0"
    "sendCurr\0return_Idntity_Query\0msg\0"
    "setLRM\0mode\0stateUpdated\0strState\0"
    "setUpdateTimeData\0timeUpdateDataMs\0"
    "setCurrLimit\0setVoltLimit\0readVoltLimit\0"
    "readCurrLimit\0powerOn\0powerOff\0"
    "IdntityQueryMsg\0setMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PowerSupplyController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x06 /* Public */,
       3,    1,  122,    2, 0x06 /* Public */,
       4,    1,  125,    2, 0x06 /* Public */,
       5,    1,  128,    2, 0x06 /* Public */,
       6,    1,  131,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  134,    2, 0x08 /* Private */,
       8,    1,  135,    2, 0x08 /* Private */,
      10,    1,  138,    2, 0x08 /* Private */,
      11,    1,  141,    2, 0x08 /* Private */,
      13,    1,  144,    2, 0x08 /* Private */,
      14,    0,  147,    2, 0x08 /* Private */,
      15,    1,  148,    2, 0x08 /* Private */,
      17,    1,  151,    2, 0x0a /* Public */,
      19,    1,  154,    2, 0x0a /* Public */,
      20,    1,  157,    2, 0x0a /* Public */,
      21,    1,  160,    2, 0x0a /* Public */,
      22,    1,  163,    2, 0x0a /* Public */,
      23,    0,  166,    2, 0x0a /* Public */,
      24,    0,  167,    2, 0x0a /* Public */,
      25,    0,  168,    2, 0x0a /* Public */,
      26,    1,  169,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::UChar,   14,
    QMetaType::SChar,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void, QMetaType::SChar,   14,

       0        // eod
};

void PowerSupplyController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PowerSupplyController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->curr((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->volt((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->voltLimit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->currLimit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->msgFromPowerSupply((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->updatePowerSupply(); break;
        case 6: _t->sendVolt((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->sendCurr((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->return_Idntity_Query((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->setLRM((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 10: { qint8 _r = _t->mode();
            if (_a[0]) *reinterpret_cast< qint8*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->stateUpdated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->setUpdateTimeData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->setCurrLimit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->setVoltLimit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->readVoltLimit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->readCurrLimit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->powerOn(); break;
        case 18: _t->powerOff(); break;
        case 19: { QString _r = _t->IdntityQueryMsg();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 20: _t->setMode((*reinterpret_cast< const qint8(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PowerSupplyController::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerSupplyController::curr)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PowerSupplyController::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerSupplyController::volt)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PowerSupplyController::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerSupplyController::voltLimit)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PowerSupplyController::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerSupplyController::currLimit)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PowerSupplyController::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerSupplyController::msgFromPowerSupply)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PowerSupplyController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PowerSupplyController.data,
    qt_meta_data_PowerSupplyController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PowerSupplyController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PowerSupplyController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PowerSupplyController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PowerSupplyController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void PowerSupplyController::curr(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PowerSupplyController::volt(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PowerSupplyController::voltLimit(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PowerSupplyController::currLimit(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PowerSupplyController::msgFromPowerSupply(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
