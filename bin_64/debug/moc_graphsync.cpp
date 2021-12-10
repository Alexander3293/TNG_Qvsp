/****************************************************************************
** Meta object code from reading C++ file 'graphsync.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../qcustomplot/graphsync.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphsync.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_graphSync_t {
    QByteArrayData data[9];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_graphSync_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_graphSync_t qt_meta_stringdata_graphSync = {
    {
QT_MOC_LITERAL(0, 0, 9), // "graphSync"
QT_MOC_LITERAL(1, 10, 19), // "changeTimeBreakSlot"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "cmd"
QT_MOC_LITERAL(4, 35, 4), // "chnl"
QT_MOC_LITERAL(5, 40, 12), // "frstPlotData"
QT_MOC_LITERAL(6, 53, 37), // "SyncModuleTranciever::pointsF..."
QT_MOC_LITERAL(7, 91, 8), // "dataPckt"
QT_MOC_LITERAL(8, 100, 8) // "plotData"

    },
    "graphSync\0changeTimeBreakSlot\0\0cmd\0"
    "chnl\0frstPlotData\0"
    "SyncModuleTranciever::pointsFromSync*\0"
    "dataPckt\0plotData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_graphSync[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x0a /* Public */,
       5,    1,   34,    2, 0x08 /* Private */,
       8,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void graphSync::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<graphSync *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeTimeBreakSlot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->frstPlotData((*reinterpret_cast< SyncModuleTranciever::pointsFromSync*(*)>(_a[1]))); break;
        case 2: _t->plotData((*reinterpret_cast< SyncModuleTranciever::pointsFromSync*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject graphSync::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_graphSync.data,
    qt_meta_data_graphSync,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *graphSync::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *graphSync::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_graphSync.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int graphSync::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
