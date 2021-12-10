/****************************************************************************
** Meta object code from reading C++ file 'syncmoduletranciever.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../network/syncmoduletranciever.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'syncmoduletranciever.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SyncModuleTranciever_t {
    QByteArrayData data[45];
    char stringdata0[543];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SyncModuleTranciever_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SyncModuleTranciever_t qt_meta_stringdata_SyncModuleTranciever = {
    {
QT_MOC_LITERAL(0, 0, 20), // "SyncModuleTranciever"
QT_MOC_LITERAL(1, 21, 14), // "connectReadAll"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 4), // "stat"
QT_MOC_LITERAL(4, 42, 10), // "dataUpdate"
QT_MOC_LITERAL(5, 53, 28), // "SyncModuleTranciever::pocket"
QT_MOC_LITERAL(6, 82, 13), // "finishReceive"
QT_MOC_LITERAL(7, 96, 4), // "flag"
QT_MOC_LITERAL(8, 101, 7), // "message"
QT_MOC_LITERAL(9, 109, 3), // "msg"
QT_MOC_LITERAL(10, 113, 11), // "sendMessage"
QT_MOC_LITERAL(11, 125, 11), // "globalStart"
QT_MOC_LITERAL(12, 137, 10), // "stopThread"
QT_MOC_LITERAL(13, 148, 15), // "stopGlobalTimer"
QT_MOC_LITERAL(14, 164, 12), // "bufferUpdate"
QT_MOC_LITERAL(15, 177, 21), // "disconnectFromHostSig"
QT_MOC_LITERAL(16, 199, 11), // "sendStopPck"
QT_MOC_LITERAL(17, 211, 15), // "deleteTcpClient"
QT_MOC_LITERAL(18, 227, 14), // "dataSyncUpdate"
QT_MOC_LITERAL(19, 242, 37), // "SyncModuleTranciever::pointsF..."
QT_MOC_LITERAL(20, 280, 12), // "onDataUpdate"
QT_MOC_LITERAL(21, 293, 4), // "time"
QT_MOC_LITERAL(22, 298, 3), // "arr"
QT_MOC_LITERAL(23, 302, 14), // "onBufferUpdate"
QT_MOC_LITERAL(24, 317, 10), // "finishRead"
QT_MOC_LITERAL(25, 328, 12), // "onNewMessage"
QT_MOC_LITERAL(26, 341, 13), // "onGlobalStart"
QT_MOC_LITERAL(27, 355, 9), // "startTime"
QT_MOC_LITERAL(28, 365, 10), // "onStopData"
QT_MOC_LITERAL(29, 376, 14), // "on_udp_data_rx"
QT_MOC_LITERAL(30, 391, 7), // "sendCmd"
QT_MOC_LITERAL(31, 399, 7), // "cmdText"
QT_MOC_LITERAL(32, 407, 11), // "channelText"
QT_MOC_LITERAL(33, 419, 8), // "timeText"
QT_MOC_LITERAL(34, 428, 3), // "run"
QT_MOC_LITERAL(35, 432, 4), // "stop"
QT_MOC_LITERAL(36, 437, 10), // "stopRecord"
QT_MOC_LITERAL(37, 448, 6), // "status"
QT_MOC_LITERAL(38, 455, 18), // "disconnectFromHost"
QT_MOC_LITERAL(39, 474, 10), // "send_Start"
QT_MOC_LITERAL(40, 485, 10), // "send_Reset"
QT_MOC_LITERAL(41, 496, 22), // "getDataOffsetDownHoles"
QT_MOC_LITERAL(42, 519, 7), // "numPckt"
QT_MOC_LITERAL(43, 527, 8), // "AddToLog"
QT_MOC_LITERAL(44, 536, 6) // "strLog"

    },
    "SyncModuleTranciever\0connectReadAll\0"
    "\0stat\0dataUpdate\0SyncModuleTranciever::pocket\0"
    "finishReceive\0flag\0message\0msg\0"
    "sendMessage\0globalStart\0stopThread\0"
    "stopGlobalTimer\0bufferUpdate\0"
    "disconnectFromHostSig\0sendStopPck\0"
    "deleteTcpClient\0dataSyncUpdate\0"
    "SyncModuleTranciever::pointsFromSync*\0"
    "onDataUpdate\0time\0arr\0onBufferUpdate\0"
    "finishRead\0onNewMessage\0onGlobalStart\0"
    "startTime\0onStopData\0on_udp_data_rx\0"
    "sendCmd\0cmdText\0channelText\0timeText\0"
    "run\0stop\0stopRecord\0status\0"
    "disconnectFromHost\0send_Start\0send_Reset\0"
    "getDataOffsetDownHoles\0numPckt\0AddToLog\0"
    "strLog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SyncModuleTranciever[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  159,    2, 0x06 /* Public */,
       4,    1,  162,    2, 0x06 /* Public */,
       6,    1,  165,    2, 0x06 /* Public */,
       8,    1,  168,    2, 0x06 /* Public */,
      10,    1,  171,    2, 0x06 /* Public */,
      11,    2,  174,    2, 0x06 /* Public */,
      12,    0,  179,    2, 0x06 /* Public */,
      13,    1,  180,    2, 0x06 /* Public */,
      14,    0,  183,    2, 0x06 /* Public */,
      15,    0,  184,    2, 0x06 /* Public */,
      16,    0,  185,    2, 0x06 /* Public */,
      17,    0,  186,    2, 0x06 /* Public */,
      18,    1,  187,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    2,  190,    2, 0x08 /* Private */,
      23,    0,  195,    2, 0x08 /* Private */,
      24,    0,  196,    2, 0x08 /* Private */,
      25,    1,  197,    2, 0x08 /* Private */,
      26,    1,  200,    2, 0x08 /* Private */,
      28,    0,  203,    2, 0x08 /* Private */,
      29,    0,  204,    2, 0x08 /* Private */,
      30,    3,  205,    2, 0x0a /* Public */,
      34,    0,  212,    2, 0x0a /* Public */,
      35,    0,  213,    2, 0x0a /* Public */,
      36,    1,  214,    2, 0x0a /* Public */,
      38,    0,  217,    2, 0x0a /* Public */,
      39,    2,  218,    2, 0x0a /* Public */,
      40,    0,  223,    2, 0x0a /* Public */,
      41,    1,  224,    2, 0x0a /* Public */,
      43,    1,  227,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QTime, QMetaType::QByteArray,   21,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QTime,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,   31,   32,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   37,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   31,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort,   42,
    QMetaType::Void, QMetaType::QString,   44,

       0        // eod
};

void SyncModuleTranciever::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SyncModuleTranciever *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectReadAll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->dataUpdate((*reinterpret_cast< SyncModuleTranciever::pocket(*)>(_a[1]))); break;
        case 2: _t->finishReceive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sendMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->globalStart((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 6: _t->stopThread(); break;
        case 7: _t->stopGlobalTimer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->bufferUpdate(); break;
        case 9: _t->disconnectFromHostSig(); break;
        case 10: _t->sendStopPck(); break;
        case 11: _t->deleteTcpClient(); break;
        case 12: _t->dataSyncUpdate((*reinterpret_cast< SyncModuleTranciever::pointsFromSync*(*)>(_a[1]))); break;
        case 13: _t->onDataUpdate((*reinterpret_cast< QTime(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 14: _t->onBufferUpdate(); break;
        case 15: _t->finishRead(); break;
        case 16: _t->onNewMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->onGlobalStart((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 18: _t->onStopData(); break;
        case 19: _t->on_udp_data_rx(); break;
        case 20: _t->sendCmd((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 21: _t->run(); break;
        case 22: _t->stop(); break;
        case 23: _t->stopRecord((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->disconnectFromHost(); break;
        case 25: _t->send_Start((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 26: _t->send_Reset(); break;
        case 27: _t->getDataOffsetDownHoles((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 28: _t->AddToLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SyncModuleTranciever::pocket >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SyncModuleTranciever::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::connectReadAll)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)(SyncModuleTranciever::pocket );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::dataUpdate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::finishReceive)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::message)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::sendMessage)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)(const int , const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::globalStart)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::stopThread)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::stopGlobalTimer)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::bufferUpdate)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::disconnectFromHostSig)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::sendStopPck)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::deleteTcpClient)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SyncModuleTranciever::*)(SyncModuleTranciever::pointsFromSync * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncModuleTranciever::dataSyncUpdate)) {
                *result = 12;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SyncModuleTranciever::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SyncModuleTranciever.data,
    qt_meta_data_SyncModuleTranciever,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SyncModuleTranciever::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SyncModuleTranciever::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SyncModuleTranciever.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SyncModuleTranciever::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void SyncModuleTranciever::connectReadAll(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SyncModuleTranciever::dataUpdate(SyncModuleTranciever::pocket _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SyncModuleTranciever::finishReceive(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SyncModuleTranciever::message(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SyncModuleTranciever::sendMessage(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SyncModuleTranciever::globalStart(const int _t1, const int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SyncModuleTranciever::stopThread()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void SyncModuleTranciever::stopGlobalTimer(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SyncModuleTranciever::bufferUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void SyncModuleTranciever::disconnectFromHostSig()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void SyncModuleTranciever::sendStopPck()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void SyncModuleTranciever::deleteTcpClient()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void SyncModuleTranciever::dataSyncUpdate(SyncModuleTranciever::pointsFromSync * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
