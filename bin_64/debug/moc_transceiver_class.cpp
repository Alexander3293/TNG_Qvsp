/****************************************************************************
** Meta object code from reading C++ file 'transceiver_class.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../network/transceiver_class.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transceiver_class.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Transceiver_class_t {
    QByteArrayData data[14];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Transceiver_class_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Transceiver_class_t qt_meta_stringdata_Transceiver_class = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Transceiver_class"
QT_MOC_LITERAL(1, 18, 11), // "data_update"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "blk_cnt"
QT_MOC_LITERAL(4, 39, 18), // "pointFromDownHoles"
QT_MOC_LITERAL(5, 58, 5), // "point"
QT_MOC_LITERAL(6, 64, 16), // "connectionClosed"
QT_MOC_LITERAL(7, 81, 8), // "newDepth"
QT_MOC_LITERAL(8, 90, 5), // "depth"
QT_MOC_LITERAL(9, 96, 13), // "newOffsetpckt"
QT_MOC_LITERAL(10, 110, 14), // "on_udp_data_rx"
QT_MOC_LITERAL(11, 125, 5), // "start"
QT_MOC_LITERAL(12, 131, 10), // "send_start"
QT_MOC_LITERAL(13, 142, 17) // "on_tool_work_mode"

    },
    "Transceiver_class\0data_update\0\0blk_cnt\0"
    "pointFromDownHoles\0point\0connectionClosed\0"
    "newDepth\0depth\0newOffsetpckt\0"
    "on_udp_data_rx\0start\0send_start\0"
    "on_tool_work_mode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Transceiver_class[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    0,   59,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,
       9,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   66,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x0a /* Public */,
      12,    0,   68,    2, 0x0a /* Public */,
      13,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::UShort,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Transceiver_class::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Transceiver_class *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->data_update((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const pointFromDownHoles(*)>(_a[2]))); break;
        case 1: _t->connectionClosed(); break;
        case 2: _t->newDepth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->newOffsetpckt((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 4: _t->on_udp_data_rx(); break;
        case 5: _t->start(); break;
        case 6: _t->send_start(); break;
        case 7: _t->on_tool_work_mode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< pointFromDownHoles >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Transceiver_class::*)(const int , const pointFromDownHoles & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transceiver_class::data_update)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Transceiver_class::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transceiver_class::connectionClosed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Transceiver_class::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transceiver_class::newDepth)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Transceiver_class::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transceiver_class::newOffsetpckt)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Transceiver_class::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Transceiver_class.data,
    qt_meta_data_Transceiver_class,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Transceiver_class::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Transceiver_class::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Transceiver_class.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Transceiver_class::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Transceiver_class::data_update(const int _t1, const pointFromDownHoles & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Transceiver_class::connectionClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Transceiver_class::newDepth(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Transceiver_class::newOffsetpckt(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
