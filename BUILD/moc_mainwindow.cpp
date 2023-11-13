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
    QByteArrayData data[30];
    char stringdata0[408];
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
QT_MOC_LITERAL(8, 112, 11), // "removeFiles"
QT_MOC_LITERAL(9, 124, 16), // "searchForLibrary"
QT_MOC_LITERAL(10, 141, 11), // "changedText"
QT_MOC_LITERAL(11, 153, 16), // "searchForProject"
QT_MOC_LITERAL(12, 170, 11), // "changedMenu"
QT_MOC_LITERAL(13, 182, 8), // "QAction*"
QT_MOC_LITERAL(14, 191, 10), // "menuAction"
QT_MOC_LITERAL(15, 202, 5), // "build"
QT_MOC_LITERAL(16, 208, 7), // "rebuild"
QT_MOC_LITERAL(17, 216, 9), // "printInfo"
QT_MOC_LITERAL(18, 226, 4), // "what"
QT_MOC_LITERAL(19, 231, 15), // "archiveComplete"
QT_MOC_LITERAL(20, 247, 7), // "archive"
QT_MOC_LITERAL(21, 255, 15), // "projectSelected"
QT_MOC_LITERAL(22, 271, 13), // "buildComplete"
QT_MOC_LITERAL(23, 285, 6), // "result"
QT_MOC_LITERAL(24, 292, 25), // "recursiveDependencySearch"
QT_MOC_LITERAL(25, 318, 14), // "settingClicked"
QT_MOC_LITERAL(26, 333, 21), // "updateSelectedSetting"
QT_MOC_LITERAL(27, 355, 18), // "saveSettingsToFile"
QT_MOC_LITERAL(28, 374, 18), // "restoreSettingsAll"
QT_MOC_LITERAL(29, 393, 14) // "restoreSetting"

    },
    "MainWindow\0addSelectedLibrary\0\0"
    "removeSelectedLibrary\0fillProjectList\0"
    "loadDependencyList\0projectName\0"
    "saveChanges\0removeFiles\0searchForLibrary\0"
    "changedText\0searchForProject\0changedMenu\0"
    "QAction*\0menuAction\0build\0rebuild\0"
    "printInfo\0what\0archiveComplete\0archive\0"
    "projectSelected\0buildComplete\0result\0"
    "recursiveDependencySearch\0settingClicked\0"
    "updateSelectedSetting\0saveSettingsToFile\0"
    "restoreSettingsAll\0restoreSetting"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x0a /* Public */,
       3,    0,  125,    2, 0x0a /* Public */,
       4,    0,  126,    2, 0x0a /* Public */,
       5,    1,  127,    2, 0x0a /* Public */,
       7,    0,  130,    2, 0x0a /* Public */,
       8,    0,  131,    2, 0x0a /* Public */,
       9,    1,  132,    2, 0x0a /* Public */,
      11,    1,  135,    2, 0x0a /* Public */,
      12,    1,  138,    2, 0x0a /* Public */,
      15,    0,  141,    2, 0x0a /* Public */,
      16,    0,  142,    2, 0x0a /* Public */,
      17,    1,  143,    2, 0x0a /* Public */,
      19,    0,  146,    2, 0x0a /* Public */,
      20,    0,  147,    2, 0x0a /* Public */,
      21,    0,  148,    2, 0x0a /* Public */,
      22,    2,  149,    2, 0x0a /* Public */,
      24,    0,  154,    2, 0x0a /* Public */,
      25,    0,  155,    2, 0x0a /* Public */,
      26,    0,  156,    2, 0x0a /* Public */,
      27,    0,  157,    2, 0x0a /* Public */,
      28,    0,  158,    2, 0x0a /* Public */,
      29,    0,  159,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    6,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 5: _t->removeFiles(); break;
        case 6: _t->searchForLibrary((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->searchForProject((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->changedMenu((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 9: _t->build(); break;
        case 10: _t->rebuild(); break;
        case 11: _t->printInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->archiveComplete(); break;
        case 13: _t->archive(); break;
        case 14: _t->projectSelected(); break;
        case 15: _t->buildComplete((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 16: _t->recursiveDependencySearch(); break;
        case 17: _t->settingClicked(); break;
        case 18: _t->updateSelectedSetting(); break;
        case 19: _t->saveSettingsToFile(); break;
        case 20: _t->restoreSettingsAll(); break;
        case 21: _t->restoreSetting(); break;
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
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
