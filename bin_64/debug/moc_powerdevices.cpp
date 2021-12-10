/****************************************************************************
** Meta object code from reading C++ file 'powerdevices.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../work_with_powerSupply/powerdevices.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'powerdevices.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PowerDevices_t {
    QByteArrayData data[48];
    char stringdata0[1090];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PowerDevices_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PowerDevices_t qt_meta_stringdata_PowerDevices = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PowerDevices"
QT_MOC_LITERAL(1, 13, 13), // "write_Command"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "write_Udp_Volt_Limit"
QT_MOC_LITERAL(4, 49, 3), // "com"
QT_MOC_LITERAL(5, 53, 25), // "write_Udp_Volt_Limit_Read"
QT_MOC_LITERAL(6, 79, 20), // "write_Udp_Curr_Limit"
QT_MOC_LITERAL(7, 100, 25), // "write_Udp_Curr_Limit_Read"
QT_MOC_LITERAL(8, 126, 20), // "write_Udp_Out_On_Off"
QT_MOC_LITERAL(9, 147, 7), // "checked"
QT_MOC_LITERAL(10, 155, 22), // "write_Udp_Output_State"
QT_MOC_LITERAL(11, 178, 24), // "write_Udp_Volt_Measuring"
QT_MOC_LITERAL(12, 203, 24), // "write_Udp_Curr_Measuring"
QT_MOC_LITERAL(13, 228, 25), // "write_Udp_Cv_Cc_Measuring"
QT_MOC_LITERAL(14, 254, 17), // "write_Udp_LRM_Set"
QT_MOC_LITERAL(15, 272, 23), // "write_Udp_LRM_Measuring"
QT_MOC_LITERAL(16, 296, 23), // "write_Udp_Idntity_Query"
QT_MOC_LITERAL(17, 320, 22), // "write_Udp_System_Error"
QT_MOC_LITERAL(18, 343, 36), // "on_pushButton_Set_Volt_Limit_..."
QT_MOC_LITERAL(19, 380, 36), // "on_pushButton_Set_Curr_Limit_..."
QT_MOC_LITERAL(20, 417, 29), // "on_radioButton_On_Off_clicked"
QT_MOC_LITERAL(21, 447, 29), // "on_pushButton_Set_LRM_clicked"
QT_MOC_LITERAL(22, 477, 8), // "newState"
QT_MOC_LITERAL(23, 486, 8), // "strState"
QT_MOC_LITERAL(24, 495, 17), // "return_Volt_Limit"
QT_MOC_LITERAL(25, 513, 22), // "return_Volt_Limit_Read"
QT_MOC_LITERAL(26, 536, 17), // "return_Curr_Limit"
QT_MOC_LITERAL(27, 554, 22), // "return_Curr_Limit_Read"
QT_MOC_LITERAL(28, 577, 17), // "return_Out_On_Off"
QT_MOC_LITERAL(29, 595, 19), // "return_Output_State"
QT_MOC_LITERAL(30, 615, 21), // "return_Volt_Measuring"
QT_MOC_LITERAL(31, 637, 21), // "return_Curr_Measuring"
QT_MOC_LITERAL(32, 659, 22), // "return_Cv_Cc_Measuring"
QT_MOC_LITERAL(33, 682, 14), // "return_LRM_Set"
QT_MOC_LITERAL(34, 697, 20), // "return_LRM_Measuring"
QT_MOC_LITERAL(35, 718, 20), // "return_Idntity_Query"
QT_MOC_LITERAL(36, 739, 19), // "return_System_Error"
QT_MOC_LITERAL(37, 759, 5), // "error"
QT_MOC_LITERAL(38, 765, 11), // "source_Comm"
QT_MOC_LITERAL(39, 777, 36), // "on_pushButton_Get_Volt_Limit_..."
QT_MOC_LITERAL(40, 814, 39), // "on_pushButton_Get_Idntity_Que..."
QT_MOC_LITERAL(41, 854, 29), // "on_pushButton_Get_LRM_clicked"
QT_MOC_LITERAL(42, 884, 31), // "on_pushButton_Get_Cv_Cc_clicked"
QT_MOC_LITERAL(43, 916, 35), // "on_pushButton_Get_Curr_Meas_c..."
QT_MOC_LITERAL(44, 952, 35), // "on_pushButton_Get_Volt_Meas_c..."
QT_MOC_LITERAL(45, 988, 32), // "on_pushButton_Get_On_Off_clicked"
QT_MOC_LITERAL(46, 1021, 36), // "on_pushButton_Get_Curr_Limit_..."
QT_MOC_LITERAL(47, 1058, 31) // "on_pushButton_Get_Error_clicked"

    },
    "PowerDevices\0write_Command\0\0"
    "write_Udp_Volt_Limit\0com\0"
    "write_Udp_Volt_Limit_Read\0"
    "write_Udp_Curr_Limit\0write_Udp_Curr_Limit_Read\0"
    "write_Udp_Out_On_Off\0checked\0"
    "write_Udp_Output_State\0write_Udp_Volt_Measuring\0"
    "write_Udp_Curr_Measuring\0"
    "write_Udp_Cv_Cc_Measuring\0write_Udp_LRM_Set\0"
    "write_Udp_LRM_Measuring\0write_Udp_Idntity_Query\0"
    "write_Udp_System_Error\0"
    "on_pushButton_Set_Volt_Limit_clicked\0"
    "on_pushButton_Set_Curr_Limit_clicked\0"
    "on_radioButton_On_Off_clicked\0"
    "on_pushButton_Set_LRM_clicked\0newState\0"
    "strState\0return_Volt_Limit\0"
    "return_Volt_Limit_Read\0return_Curr_Limit\0"
    "return_Curr_Limit_Read\0return_Out_On_Off\0"
    "return_Output_State\0return_Volt_Measuring\0"
    "return_Curr_Measuring\0return_Cv_Cc_Measuring\0"
    "return_LRM_Set\0return_LRM_Measuring\0"
    "return_Idntity_Query\0return_System_Error\0"
    "error\0source_Comm\0"
    "on_pushButton_Get_Volt_Limit_clicked\0"
    "on_pushButton_Get_Idntity_Query_clicked\0"
    "on_pushButton_Get_LRM_clicked\0"
    "on_pushButton_Get_Cv_Cc_clicked\0"
    "on_pushButton_Get_Curr_Meas_clicked\0"
    "on_pushButton_Get_Volt_Meas_clicked\0"
    "on_pushButton_Get_On_Off_clicked\0"
    "on_pushButton_Get_Curr_Limit_clicked\0"
    "on_pushButton_Get_Error_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PowerDevices[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  219,    2, 0x06 /* Public */,
       3,    1,  222,    2, 0x06 /* Public */,
       5,    0,  225,    2, 0x06 /* Public */,
       6,    1,  226,    2, 0x06 /* Public */,
       7,    0,  229,    2, 0x06 /* Public */,
       8,    1,  230,    2, 0x06 /* Public */,
      10,    0,  233,    2, 0x06 /* Public */,
      11,    0,  234,    2, 0x06 /* Public */,
      12,    0,  235,    2, 0x06 /* Public */,
      13,    0,  236,    2, 0x06 /* Public */,
      14,    1,  237,    2, 0x06 /* Public */,
      15,    0,  240,    2, 0x06 /* Public */,
      16,    0,  241,    2, 0x06 /* Public */,
      17,    0,  242,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,  243,    2, 0x08 /* Private */,
      19,    0,  244,    2, 0x08 /* Private */,
      20,    1,  245,    2, 0x08 /* Private */,
      21,    0,  248,    2, 0x08 /* Private */,
      22,    1,  249,    2, 0x08 /* Private */,
      24,    1,  252,    2, 0x08 /* Private */,
      25,    1,  255,    2, 0x08 /* Private */,
      26,    1,  258,    2, 0x08 /* Private */,
      27,    1,  261,    2, 0x08 /* Private */,
      28,    1,  264,    2, 0x08 /* Private */,
      29,    1,  267,    2, 0x08 /* Private */,
      30,    1,  270,    2, 0x08 /* Private */,
      31,    1,  273,    2, 0x08 /* Private */,
      32,    1,  276,    2, 0x08 /* Private */,
      33,    1,  279,    2, 0x08 /* Private */,
      34,    1,  282,    2, 0x08 /* Private */,
      35,    1,  285,    2, 0x08 /* Private */,
      36,    3,  288,    2, 0x08 /* Private */,
      39,    0,  295,    2, 0x08 /* Private */,
      40,    0,  296,    2, 0x08 /* Private */,
      41,    0,  297,    2, 0x08 /* Private */,
      42,    0,  298,    2, 0x08 /* Private */,
      43,    0,  299,    2, 0x08 /* Private */,
      44,    0,  300,    2, 0x08 /* Private */,
      45,    0,  301,    2, 0x08 /* Private */,
      46,    0,  302,    2, 0x08 /* Private */,
      47,    0,  303,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int,   37,    2,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PowerDevices::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PowerDevices *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->write_Command((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->write_Udp_Volt_Limit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->write_Udp_Volt_Limit_Read(); break;
        case 3: _t->write_Udp_Curr_Limit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->write_Udp_Curr_Limit_Read(); break;
        case 5: _t->write_Udp_Out_On_Off((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->write_Udp_Output_State(); break;
        case 7: _t->write_Udp_Volt_Measuring(); break;
        case 8: _t->write_Udp_Curr_Measuring(); break;
        case 9: _t->write_Udp_Cv_Cc_Measuring(); break;
        case 10: _t->write_Udp_LRM_Set((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->write_Udp_LRM_Measuring(); break;
        case 12: _t->write_Udp_Idntity_Query(); break;
        case 13: _t->write_Udp_System_Error(); break;
        case 14: _t->on_pushButton_Set_Volt_Limit_clicked(); break;
        case 15: _t->on_pushButton_Set_Curr_Limit_clicked(); break;
        case 16: _t->on_radioButton_On_Off_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->on_pushButton_Set_LRM_clicked(); break;
        case 18: _t->newState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->return_Volt_Limit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->return_Volt_Limit_Read((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->return_Curr_Limit((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: _t->return_Curr_Limit_Read((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->return_Out_On_Off((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->return_Output_State((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->return_Volt_Measuring((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->return_Curr_Measuring((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 27: _t->return_Cv_Cc_Measuring((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->return_LRM_Set((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->return_LRM_Measuring((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->return_Idntity_Query((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: _t->return_System_Error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 32: _t->on_pushButton_Get_Volt_Limit_clicked(); break;
        case 33: _t->on_pushButton_Get_Idntity_Query_clicked(); break;
        case 34: _t->on_pushButton_Get_LRM_clicked(); break;
        case 35: _t->on_pushButton_Get_Cv_Cc_clicked(); break;
        case 36: _t->on_pushButton_Get_Curr_Meas_clicked(); break;
        case 37: _t->on_pushButton_Get_Volt_Meas_clicked(); break;
        case 38: _t->on_pushButton_Get_On_Off_clicked(); break;
        case 39: _t->on_pushButton_Get_Curr_Limit_clicked(); break;
        case 40: _t->on_pushButton_Get_Error_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PowerDevices::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Command)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Volt_Limit)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Volt_Limit_Read)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Curr_Limit)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Curr_Limit_Read)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Out_On_Off)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Output_State)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Volt_Measuring)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Curr_Measuring)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Cv_Cc_Measuring)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_LRM_Set)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_LRM_Measuring)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_Idntity_Query)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (PowerDevices::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PowerDevices::write_Udp_System_Error)) {
                *result = 13;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PowerDevices::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PowerDevices.data,
    qt_meta_data_PowerDevices,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PowerDevices::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PowerDevices::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PowerDevices.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PowerDevices::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 41;
    }
    return _id;
}

// SIGNAL 0
void PowerDevices::write_Command(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PowerDevices::write_Udp_Volt_Limit(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PowerDevices::write_Udp_Volt_Limit_Read()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PowerDevices::write_Udp_Curr_Limit(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PowerDevices::write_Udp_Curr_Limit_Read()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PowerDevices::write_Udp_Out_On_Off(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PowerDevices::write_Udp_Output_State()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void PowerDevices::write_Udp_Volt_Measuring()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void PowerDevices::write_Udp_Curr_Measuring()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void PowerDevices::write_Udp_Cv_Cc_Measuring()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void PowerDevices::write_Udp_LRM_Set(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void PowerDevices::write_Udp_LRM_Measuring()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void PowerDevices::write_Udp_Idntity_Query()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void PowerDevices::write_Udp_System_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
