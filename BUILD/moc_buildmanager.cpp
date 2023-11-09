/****************************************************************************
** Meta object code from reading C++ file 'buildmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/filework/buildmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buildmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileWork__BuildManager_t {
    QByteArrayData data[5];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileWork__BuildManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileWork__BuildManager_t qt_meta_stringdata_FileWork__BuildManager = {
    {
QT_MOC_LITERAL(0, 0, 22), // "FileWork::BuildManager"
QT_MOC_LITERAL(1, 23, 13), // "buildComplete"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 11), // "projectName"
QT_MOC_LITERAL(4, 50, 11) // "buildResult"

    },
    "FileWork::BuildManager\0buildComplete\0"
    "\0projectName\0buildResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileWork__BuildManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,

       0        // eod
};

void FileWork::BuildManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BuildManager *_t = static_cast<BuildManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buildComplete((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BuildManager::*)(const QString & , const bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BuildManager::buildComplete)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FileWork::BuildManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FileWork__BuildManager.data,
      qt_meta_data_FileWork__BuildManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FileWork::BuildManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileWork::BuildManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileWork__BuildManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FileWork::BuildManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void FileWork::BuildManager::buildComplete(const QString & _t1, const bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
