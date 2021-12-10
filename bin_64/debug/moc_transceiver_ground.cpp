/****************************************************************************
** Meta object code from reading C++ file 'transceiver_ground.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../network/transceiver_ground.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transceiver_ground.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Transceiver_ground_t {
    QByteArrayData data[19];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Transceiver_ground_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Transceiver_ground_t qt_meta_stringdata_Transceiver_ground = {
    {
QT_MOC_LITERAL(0, 0, 18), // "Transceiver_ground"
QT_MOC_LITERAL(1, 19, 16), // "dataGroundUpdate"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 19), // "pointsFromWGrounds*"
QT_MOC_LITERAL(4, 57, 4), // "data"
QT_MOC_LITERAL(5, 62, 7), // "message"
QT_MOC_LITERAL(6, 70, 6), // "strLog"
QT_MOC_LITERAL(7, 77, 14), // "on_udp_data_rx"
QT_MOC_LITERAL(8, 92, 26), // "dataProcessingModuleGround"
QT_MOC_LITERAL(9, 119, 5), // "start"
QT_MOC_LITERAL(10, 125, 8), // "send_cmd"
QT_MOC_LITERAL(11, 134, 10), // "send_Start"
QT_MOC_LITERAL(12, 145, 9), // "send_Stop"
QT_MOC_LITERAL(13, 155, 16), // "send_Settings_KU"
QT_MOC_LITERAL(14, 172, 5), // "value"
QT_MOC_LITERAL(15, 178, 7), // "uint8_t"
QT_MOC_LITERAL(16, 186, 6), // "numDev"
QT_MOC_LITERAL(17, 193, 22), // "getDataOffsetDownHoles"
QT_MOC_LITERAL(18, 216, 7) // "numPckt"

    },
    "Transceiver_ground\0dataGroundUpdate\0"
    "\0pointsFromWGrounds*\0data\0message\0"
    "strLog\0on_udp_data_rx\0dataProcessingModuleGround\0"
    "start\0send_cmd\0send_Start\0send_Stop\0"
    "send_Settings_KU\0value\0uint8_t\0numDev\0"
    "getDataOffsetDownHoles\0numPckt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Transceiver_ground[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   70,    2, 0x0a /* Public */,
       8,    1,   71,    2, 0x0a /* Public */,
       9,    0,   74,    2, 0x0a /* Public */,
      10,    0,   75,    2, 0x0a /* Public */,
      11,    0,   76,    2, 0x0a /* Public */,
      12,    0,   77,    2, 0x0a /* Public */,
      13,    2,   78,    2, 0x0a /* Public */,
      17,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 15,   14,   16,
    QMetaType::Void, QMetaType::UShort,   18,

       0        // eod
};

void Transceiver_ground::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Transceiver_ground *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataGroundUpdate((*reinterpret_cast< pointsFromWGrounds*(*)>(_a[1]))); break;
        case 1: _t->message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_udp_data_rx(); break;
        case 3: _t->dataProcessingModuleGround((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->start(); break;
        case 5: _t->send_cmd(); break;
        case 6: _t->send_Start(); break;
        case 7: _t->send_Stop(); break;
        case 8: _t->send_Settings_KU((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 9: _t->getDataOffsetDownHoles((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Transceiver_ground::*)(pointsFromWGrounds * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transceiver_ground::dataGroundUpdate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Transceiver_ground::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transceiver_ground::message)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Transceiver_ground::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Transceiver_ground.data,
    qt_meta_data_Transceiver_ground,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Transceiver_ground::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Transceiver_ground::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Transceiver_ground.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Transceiver_ground::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Transceiver_ground::dataGroundUpdate(pointsFromWGrounds * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Transceiver_ground::message(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
