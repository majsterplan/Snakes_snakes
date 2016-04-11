#include "algorithm.h"

Algorithm::Algorithm()
{
}

QString Algorithm::getName()
{
    return this->name;
}

void Algorithm::setName(QString _name)
{
    this->name = _name;
}

QString Algorithm::getScript()
{
    return this->script;
}

void Algorithm::setScript(QString _script)
{
    this->script = _script;
}
