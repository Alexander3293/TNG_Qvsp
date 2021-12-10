/****************************************************************************
** Meta object code from reading C++ file 'graphdownhole.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../qcustomplot/graphdownhole.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphdownhole.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_graphDownHole_t {
    QByteArrayData data[10];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_graphDownHole_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_graphDownHole_t qt_meta_stringdata_graphDownHole = {
    {
QT_MOC_LITERAL(0, 0, 13), // "graphDownHole"
QT_MOC_LITERAL(1, 14, 16), // "updateSceneWidth"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "plotData"
QT_MOC_LITERAL(4, 41, 16), // "slot_data_update"
QT_MOC_LITERAL(5, 58, 7), // "blk_cnt"
QT_MOC_LITERAL(6, 66, 18), // "pointFromDownHoles"
QT_MOC_LITERAL(7, 85, 5), // "point"
QT_MOC_LITERAL(8, 91, 26), // "on_relayModeButton_clicked"
QT_MOC_LITERAL(9, 118, 7) // "checked"

    },
    "graphDownHole\0updateSceneWidth\0\0"
    "plotData\0slot_data_update\0blk_cnt\0"
    "pointFromDownHoles\0point\0"
    "on_relayModeButton_clicked\0checked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_graphDownHole[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    2,   36,    2, 0x0a /* Public */,
       8,    1,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::Bool,    9,

       0        // eod
};

void graphDownHole::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<graphDownHole *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSceneWidth(); break;
        case 1: _t->plotData(); break;
        case 2: _t->slot_data_update((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const pointFromDownHoles(*)>(_a[2]))); break;
        case 3: _t->on_relayModeButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
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
            using _t = void (graphDownHole::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&graphDownHole::updateSceneWidth)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject graphDownHole::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_graphDownHole.data,
    qt_meta_data_graphDownHole,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *graphDownHole::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *graphDownHole::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_graphDownHole.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int graphDownHole::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void graphDownHole::updateSceneWidth()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
