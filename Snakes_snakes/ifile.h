#ifndef IFILE_H
#define IFILE_H

#include <QStringList>

class DataManager;

/**
 * @brief Klasa IFile - interfejs dla różnych plików
 */
class IFile
{
public:
    IFile();
    virtual ~IFile();
    virtual QString getName() = 0;
    virtual QStringList prepareContentToSet() = 0;
    virtual QString prepareContentToSave(DataManager &_dataManger, char c) = 0;
};

#endif // IFILE_H
