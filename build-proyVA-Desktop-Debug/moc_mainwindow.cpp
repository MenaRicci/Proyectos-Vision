/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../proy3/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      28,   22,   11,   11, 0x0a,
      59,   53,   11,   11, 0x0a,
      83,   11,   11,   11, 0x0a,
      95,   11,   11,   11, 0x0a,
     118,  112,   11,   11, 0x0a,
     148,   11,   11,   11, 0x0a,
     165,   11,   11,   11, 0x0a,
     179,   11,   11,   11, 0x0a,
     198,   11,   11,   11, 0x0a,
     210,   11,   11,   11, 0x0a,
     229,  226,  222,   11, 0x0a,
     247,   11,   11,   11, 0x0a,
     261,   11,   11,   11, 0x0a,
     276,  274,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0compute()\0start\0"
    "start_stop_capture(bool)\0color\0"
    "change_color_gray(bool)\0set_Image()\0"
    "saveImageInSet()\0p,w,h\0"
    "selectWindow(QPointF,int,int)\0"
    "deselectWindow()\0changeImage()\0"
    "deleteImageInSet()\0Match_ORB()\0"
    "Match_BFM()\0int\0id\0IndiceObjeto(int)\0"
    "BorrarLista()\0PintarRect()\0i\0"
    "DispersionPuntos(int)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->compute(); break;
        case 1: _t->start_stop_capture((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->change_color_gray((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->set_Image(); break;
        case 4: _t->saveImageInSet(); break;
        case 5: _t->selectWindow((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->deselectWindow(); break;
        case 7: _t->changeImage(); break;
        case 8: _t->deleteImageInSet(); break;
        case 9: _t->Match_ORB(); break;
        case 10: _t->Match_BFM(); break;
        case 11: { int _r = _t->IndiceObjeto((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: _t->BorrarLista(); break;
        case 13: _t->PintarRect(); break;
        case 14: _t->DispersionPuntos((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
