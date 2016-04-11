#include "algorithmfile.h"
#include "QDebug"

AlgorithmFile::AlgorithmFile()
{
}

QStringList AlgorithmFile::prepareContentToSet()
{
    return QStringList(this->fileContent);
}

QString AlgorithmFile::prepareContentToSave(DataManager &_dataManager, char c)
{
    if(c == 'a')
        this->fileContent = _dataManager.getCurrentAlgorithm()->getScript();
    return this->fileContent;
}
