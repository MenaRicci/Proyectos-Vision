/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../proy4/mainwindow.h"
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
      17,   14, // methods
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
     102,   96,   11,   11, 0x0a,
     132,   11,   11,   11, 0x0a,
     169,  149,   11,   11, 0x0a,
     204,  184,   11,   11, 0x0a,
     240,  184,   11,   11, 0x0a,
     287,   11,   11,   11, 0x0a,
     302,   11,   11,   11, 0x0a,
     317,   11,   11,   11, 0x0a,
     348,  335,   11,   11, 0x0a,
     386,  384,  380,   11, 0x0a,
     413,  404,   11,   11, 0x0a,
     435,   11,   11,   11, 0x0a,
     459,  452,  380,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0compute()\0start\0"
    "start_stop_capture(bool)\0color\0"
    "change_color_gray(bool)\0load_Image()\0"
    "p,w,h\0selectWindow(QPointF,int,int)\0"
    "deselectWindow()\0Img_Source,Img_Dest\0"
    "Canny(Mat,Mat)\0pInicial,region,aux\0"
    "AnalisisRegion(Point,int,STRegion&)\0"
    "AnalisisRegionEstadistico(Point,int,STRegion&)\0"
    "Segmentacion()\0PuntosNegros()\0"
    "PuntosFronteras()\0p,region,ind\0"
    "AnalisisFrontera(Point,int,int)\0int\0"
    "p\0RegionAfin(Point)\0Img_Dest\0"
    "PintarSegmentado(Mat)\0PintarFrontera()\0"
    "id,ori\0IdRegiones(int,Point)\0"
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
        case 3: _t->load_Image(); break;
        case 4: _t->selectWindow((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->deselectWindow(); break;
        case 6: _t->Canny((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2]))); break;
        case 7: _t->AnalisisRegion((*reinterpret_cast< Point(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< STRegion(*)>(_a[3]))); break;
        case 8: _t->AnalisisRegionEstadistico((*reinterpret_cast< Point(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< STRegion(*)>(_a[3]))); break;
        case 9: _t->Segmentacion(); break;
        case 10: _t->PuntosNegros(); break;
        case 11: _t->PuntosFronteras(); break;
        case 12: _t->AnalisisFrontera((*reinterpret_cast< Point(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: { int _r = _t->RegionAfin((*reinterpret_cast< Point(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: _t->PintarSegmentado((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 15: _t->PintarFrontera(); break;
        case 16: { int _r = _t->IdRegiones((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Point(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
