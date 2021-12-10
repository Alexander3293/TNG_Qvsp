/****************************************************************************
** Meta object code from reading C++ file 'plotdoublegraph.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../qcustomplot/plotdoublegraph.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotdoublegraph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_plotDoubleGraph_t {
    QByteArrayData data[10];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_plotDoubleGraph_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_plotDoubleGraph_t qt_meta_stringdata_plotDoubleGraph = {
    {
QT_MOC_LITERAL(0, 0, 15), // "plotDoubleGraph"
QT_MOC_LITERAL(1, 16, 8), // "plotData"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 19), // "pointsFromWGrounds*"
QT_MOC_LITERAL(4, 46, 8), // "dataPckt"
QT_MOC_LITERAL(5, 55, 16), // "slot_data_update"
QT_MOC_LITERAL(6, 72, 7), // "blk_cnt"
QT_MOC_LITERAL(7, 80, 18), // "pointFromDownHoles"
QT_MOC_LITERAL(8, 99, 5), // "point"
QT_MOC_LITERAL(9, 105, 18) // "frstPlotDataGround"

    },
    "plotDoubleGraph\0plotData\0\0pointsFromWGrounds*\0"
    "dataPckt\0slot_data_update\0blk_cnt\0"
    "pointFromDownHoles\0point\0frstPlotDataGround"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_plotDoubleGraph[] = {

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
       1,    1,   29,    2, 0x0a /* Public */,
       5,    2,   32,    2, 0x0a /* Public */,
       9,    1,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void plotDoubleGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<plotDoubleGraph *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->plotData((*reinterpret_cast< pointsFromWGrounds*(*)>(_a[1]))); break;
        case 1: _t->slot_data_update((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const pointFromDownHoles(*)>(_a[2]))); break;
        case 2: _t->frstPlotDataGround((*reinterpret_cast< pointsFromWGrounds*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< pointFromDownHoles >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject plotDoubleGraph::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_plotDoubleGraph.data,
    qt_meta_data_plotDoubleGraph,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *plotDoubleGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *plotDoubleGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_plotDoubleGraph.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int plotDoubleGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
