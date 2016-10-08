/****************************************************************************
** Meta object code from reading C++ file 'GUI4.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GUI4.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI4.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI4[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      57,   31,    5,    5, 0x0a,
     105,    5,    5,    5, 0x0a,
     122,    5,    5,    5, 0x0a,
     139,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI4[] = {
    "GUI4\0\0updateCoords(vtkObject*)\0"
    "obj,,client_data,,command\0"
    "popup(vtkObject*,ulong,void*,void*,vtkCommand*)\0"
    "color1(QAction*)\0color2(QAction*)\0"
    "on_pushButton_clicked()\0"
};

void GUI4::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUI4 *_t = static_cast<GUI4 *>(_o);
        switch (_id) {
        case 0: _t->updateCoords((*reinterpret_cast< vtkObject*(*)>(_a[1]))); break;
        case 1: _t->popup((*reinterpret_cast< vtkObject*(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3])),(*reinterpret_cast< void*(*)>(_a[4])),(*reinterpret_cast< vtkCommand*(*)>(_a[5]))); break;
        case 2: _t->color1((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->color2((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GUI4::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUI4::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUI4,
      qt_meta_data_GUI4, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI4::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI4::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI4::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI4))
        return static_cast<void*>(const_cast< GUI4*>(this));
    if (!strcmp(_clname, "Ui::GUI"))
        return static_cast< Ui::GUI*>(const_cast< GUI4*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUI4::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
