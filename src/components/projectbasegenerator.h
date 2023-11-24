#ifndef PROJECTBASEGENERATOR_H
#define PROJECTBASEGENERATOR_H

#include "utilfunctionclass.h"

namespace ProjectUtility
{

struct ProjectBaseConfiguration
{
    QString baseDir;
    QString projectName;
    bool hasGui {false};
    bool isLibrary {false};
    bool hasDeps {false};
    bool hasBuildPri {false};
};

class ProjectBaseGenerator
{
public:
    ProjectBaseGenerator(UtilFunctionClass & utilClass);
    ~ProjectBaseGenerator();

    bool generateProject(const ProjectBaseConfiguration & config);

private:
    UtilFunctionClass & m_utilClass;
};

}
#endif // PROJECTBASEGENERATOR_H
