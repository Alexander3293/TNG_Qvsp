/****************************************************************************
** Meta object code from reading C++ file 'tcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../network/tcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TcpClient_t {
    QByteArrayData data[31];
    char stringdata0[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpClient_t qt_meta_stringdata_TcpClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TcpClient"
QT_MOC_LITERAL(1, 10, 10), // "newMessage"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "message"
QT_MOC_LITERAL(4, 30, 9), // "connected"
QT_MOC_LITERAL(5, 40, 11), // "isConnected"
QT_MOC_LITERAL(6, 52, 10), // "stopThread"
QT_MOC_LITERAL(7, 63, 3), // "ack"
QT_MOC_LITERAL(8, 67, 10), // "dataUpdate"
QT_MOC_LITERAL(9, 78, 13), // "finishRecieve"
QT_MOC_LITERAL(10, 92, 11), // "globalStart"
QT_MOC_LITERAL(11, 104, 12), // "bufferUpdate"
QT_MOC_LITERAL(12, 117, 8), // "dataRead"
QT_MOC_LITERAL(13, 126, 6), // "status"
QT_MOC_LITERAL(14, 133, 6), // "parser"
QT_MOC_LITERAL(15, 140, 13), // "connectToHost"
QT_MOC_LITERAL(16, 154, 10), // "startTimer"
QT_MOC_LITERAL(17, 165, 3), // "run"
QT_MOC_LITERAL(18, 169, 4), // "stop"
QT_MOC_LITERAL(19, 174, 11), // "sendMessage"
QT_MOC_LITERAL(20, 186, 4), // "data"
QT_MOC_LITERAL(21, 191, 9), // "stopTimer"
QT_MOC_LITERAL(22, 201, 14), // "connectReadAll"
QT_MOC_LITERAL(23, 216, 4), // "stat"
QT_MOC_LITERAL(24, 221, 15), // "recieveMessage1"
QT_MOC_LITERAL(25, 237, 15), // "recieveMessage2"
QT_MOC_LITERAL(26, 253, 11), // "QByteArray*"
QT_MOC_LITERAL(27, 265, 11), // "outputArray"
QT_MOC_LITERAL(28, 277, 3), // "len"
QT_MOC_LITERAL(29, 281, 18), // "disconnectFromHost"
QT_MOC_LITERAL(30, 300, 17) // "sendDicconnectPck"

    },
    "TcpClient\0newMessage\0\0message\0connected\0"
    "isConnected\0stopThread\0ack\0dataUpdate\0"
    "finishRecieve\0globalStart\0bufferUpdate\0"
    "dataRead\0status\0parser\0connectToHost\0"
    "startTimer\0run\0stop\0sendMessage\0data\0"
    "stopTimer\0connectReadAll\0stat\0"
    "recieveMessage1\0recieveMessage2\0"
    "QByteArray*\0outputArray\0len\0"
    "disconnectFromHost\0sendDicconnectPck"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x06 /* Public */,
       4,    1,  122,    2, 0x06 /* Public */,
       6,    0,  125,    2, 0x06 /* Public */,
       7,    1,  126,    2, 0x06 /* Public */,
       8,    2,  129,    2, 0x06 /* Public */,
       9,    0,  134,    2, 0x06 /* Public */,
      10,    1,  135,    2, 0x06 /* Public */,
      11,    0,  138,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  139,    2, 0x08 /* Private */,
      14,    0,  142,    2, 0x08 /* Private */,
      15,    0,  143,    2, 0x0a /* Public */,
      16,    0,  144,    2, 0x0a /* Public */,
      17,    0,  145,    2, 0x0a /* Public */,
      18,    0,  146,    2, 0x0a /* Public */,
      19,    1,  147,    2, 0x0a /* Public */,
      21,    0,  150,    2, 0x0a /* Public */,
      22,    1,  151,    2, 0x0a /* Public */,
      24,    0,  154,    2, 0x0a /* Public */,
      25,    2,  155,    2, 0x0a /* Public */,
      29,    0,  160,    2, 0x0a /* Public */,
      30,    0,  161,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QTime, QMetaType::QByteArray,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QTime,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   23,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 26, QMetaType::Int,   27,   28,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TcpClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->connected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->stopThread(); break;
        case 3: _t->ack((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->dataUpdate((*reinterpret_cast< QTime(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 5: _t->finishRecieve(); break;
        case 6: _t->globalStart((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 7: _t->bufferUpdate(); break;
        case 8: _t->dataRead((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->parser(); break;
        case 10: _t->connectToHost(); break;
        case 11: _t->startTimer(); break;
        case 12: _t->run(); break;
        case 13: _t->stop(); break;
        case 14: _t->sendMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 15: _t->stopTimer(); break;
        case 16: _t->connectReadAll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->recieveMessage1(); break;
        case 18: { bool _r = _t->recieveMessage2((*reinterpret_cast< QByteArray*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: _t->disconnectFromHost(); break;
        case 20: _t->sendDicconnectPck(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TcpClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::newMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::connected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::stopThread)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::ack)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)(QTime , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::dataUpdate)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::finishRecieve)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)(const QTime );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::globalStart)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::bufferUpdate)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TcpClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TcpClient.data,
    qt_meta_data_TcpClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TcpClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TcpClient::newMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpClient::connected(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TcpClient::stopThread()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TcpClient::ack(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TcpClient::dataUpdate(QTime _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TcpClient::finishRecieve()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TcpClient::globalStart(const QTime _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void TcpClient::bufferUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
