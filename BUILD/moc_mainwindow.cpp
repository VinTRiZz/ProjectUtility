/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/gui/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "addSelectedLibrary"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 21), // "removeSelectedLibrary"
QT_MOC_LITERAL(4, 53, 15), // "fillProjectList"
QT_MOC_LITERAL(5, 69, 18), // "loadDependencyList"
QT_MOC_LITERAL(6, 88, 11), // "projectName"
QT_MOC_LITERAL(7, 100, 11), // "saveChanges"
QT_MOC_LITERAL(8, 112, 12), // "createBackup"
QT_MOC_LITERAL(9, 125, 10), // "loadBackup"
QT_MOC_LITERAL(10, 136, 14), // "updateBasePath"
QT_MOC_LITERAL(11, 151, 11), // "removeFiles"
QT_MOC_LITERAL(12, 163, 16), // "searchForLibrary"
QT_MOC_LITERAL(13, 180, 11), // "changedText"
QT_MOC_LITERAL(14, 192, 16), // "searchForProject"
QT_MOC_LITERAL(15, 209, 11), // "changedMenu"
QT_MOC_LITERAL(16, 221, 8), // "QAction*"
QT_MOC_LITERAL(17, 230, 10), // "menuAction"
QT_MOC_LITERAL(18, 241, 5), // "build"
QT_MOC_LITERAL(19, 247, 7) // "rebuild"

    },
    "MainWindow\0addSelectedLibrary\0\0"
    "removeSelectedLibrary\0fillProjectList\0"
    "loadDependencyList\0projectName\0"
    "saveChanges\0createBackup\0loadBackup\0"
    "updateBasePath\0removeFiles\0searchForLibrary\0"
    "changedText\0searchForProject\0changedMenu\0"
    "QAction*\0menuAction\0build\0rebuild"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    1,   87,    2, 0x0a /* Public */,
       7,    0,   90,    2, 0x0a /* Public */,
       8,    0,   91,    2, 0x0a /* Public */,
       9,    0,   92,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      11,    0,   94,    2, 0x0a /* Public */,
      12,    1,   95,    2, 0x0a /* Public */,
      14,    1,   98,    2, 0x0a /* Public */,
      15,    1,  101,    2, 0x0a /* Public */,
      18,    0,  104,    2, 0x0a /* Public */,
      19,    0,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addSelectedLibrary(); break;
        case 1: _t->removeSelectedLibrary(); break;
        case 2: _t->fillProjectList(); break;
        case 3: _t->loadDependencyList((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->saveChanges(); break;
        case 5: _t->createBackup(); break;
        case 6: _t->loadBackup(); break;
        case 7: _t->updateBasePath(); break;
        case 8: _t->removeFiles(); break;
        case 9: _t->searchForLibrary((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->searchForProject((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->changedMenu((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 12: _t->build(); break;
        case 13: _t->rebuild(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
