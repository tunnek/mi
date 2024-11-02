/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Project_Serial_Port/untitled/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[19];
    char stringdata0[434];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 32), // "on_btn_CloseOrOpenSerial_clicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 7), // "checked"
QT_MOC_LITERAL(4, 49, 26), // "on_pushButton_send_clicked"
QT_MOC_LITERAL(5, 76, 20), // "on_SerialData_reched"
QT_MOC_LITERAL(6, 97, 26), // "on_pushButton_save_clicked"
QT_MOC_LITERAL(7, 124, 26), // "on_pushButton_load_clicked"
QT_MOC_LITERAL(8, 151, 27), // "on_pushButton_reset_clicked"
QT_MOC_LITERAL(9, 179, 29), // "on_pushButton_saveRev_clicked"
QT_MOC_LITERAL(10, 209, 28), // "on_checkBox_timeSend_clicked"
QT_MOC_LITERAL(11, 238, 10), // "getSysTime"
QT_MOC_LITERAL(12, 249, 30), // "on_checkBox_hexDisplay_clicked"
QT_MOC_LITERAL(13, 280, 31), // "on_pushButton_hidePanel_clicked"
QT_MOC_LITERAL(14, 312, 33), // "on_pushButton_hideHistory_cli..."
QT_MOC_LITERAL(15, 346, 17), // "refreshSerialName"
QT_MOC_LITERAL(16, 364, 25), // "on_command_button_clicked"
QT_MOC_LITERAL(17, 390, 27), // "on_checkBox_cirSend_clicked"
QT_MOC_LITERAL(18, 418, 15) // "buttons_handler"

    },
    "Widget\0on_btn_CloseOrOpenSerial_clicked\0"
    "\0checked\0on_pushButton_send_clicked\0"
    "on_SerialData_reched\0on_pushButton_save_clicked\0"
    "on_pushButton_load_clicked\0"
    "on_pushButton_reset_clicked\0"
    "on_pushButton_saveRev_clicked\0"
    "on_checkBox_timeSend_clicked\0getSysTime\0"
    "on_checkBox_hexDisplay_clicked\0"
    "on_pushButton_hidePanel_clicked\0"
    "on_pushButton_hideHistory_clicked\0"
    "refreshSerialName\0on_command_button_clicked\0"
    "on_checkBox_cirSend_clicked\0buttons_handler"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x08 /* Private */,
       4,    0,   97,    2, 0x08 /* Private */,
       5,    0,   98,    2, 0x08 /* Private */,
       6,    0,   99,    2, 0x08 /* Private */,
       7,    0,  100,    2, 0x08 /* Private */,
       8,    0,  101,    2, 0x08 /* Private */,
       9,    0,  102,    2, 0x08 /* Private */,
      10,    1,  103,    2, 0x08 /* Private */,
      11,    0,  106,    2, 0x08 /* Private */,
      12,    1,  107,    2, 0x08 /* Private */,
      13,    1,  110,    2, 0x08 /* Private */,
      14,    1,  113,    2, 0x08 /* Private */,
      15,    0,  116,    2, 0x08 /* Private */,
      16,    0,  117,    2, 0x08 /* Private */,
      17,    1,  118,    2, 0x08 /* Private */,
      18,    0,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn_CloseOrOpenSerial_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_send_clicked(); break;
        case 2: _t->on_SerialData_reched(); break;
        case 3: _t->on_pushButton_save_clicked(); break;
        case 4: _t->on_pushButton_load_clicked(); break;
        case 5: _t->on_pushButton_reset_clicked(); break;
        case 6: _t->on_pushButton_saveRev_clicked(); break;
        case 7: _t->on_checkBox_timeSend_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->getSysTime(); break;
        case 9: _t->on_checkBox_hexDisplay_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_pushButton_hidePanel_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_hideHistory_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->refreshSerialName(); break;
        case 13: _t->on_command_button_clicked(); break;
        case 14: _t->on_checkBox_cirSend_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->buttons_handler(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
