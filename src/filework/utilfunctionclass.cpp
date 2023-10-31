#include "utilfunctionclass.h"

using namespace FileWork;

UtilFunctionClass::UtilFunctionClass(QVector<Project> &initApps, QVector<Project> &initLibs) :
    apps(initApps),
    libs(initLibs)
{

}

UtilFunctionClass::~UtilFunctionClass()
{

}
