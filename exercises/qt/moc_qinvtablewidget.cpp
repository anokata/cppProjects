/****************************************************************************
** Meta object code from reading C++ file 'qinvtablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qinvtablewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qinvtablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QInvTableWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   17,   16,   16, 0x0a,
      44,   17,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QInvTableWidget[] = {
    "QInvTableWidget\0\0row,col\0cellStart(int,int)\0"
    "cellEnter(int,int)\0"
};

void QInvTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QInvTableWidget *_t = static_cast<QInvTableWidget *>(_o);
        switch (_id) {
        case 0: _t->cellStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->cellEnter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QInvTableWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QInvTableWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_QInvTableWidget,
      qt_meta_data_QInvTableWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QInvTableWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QInvTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QInvTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QInvTableWidget))
        return static_cast<void*>(const_cast< QInvTableWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int QInvTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
