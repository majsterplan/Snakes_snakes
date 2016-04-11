#include "filemanager.h"

FileManager::FileManager()
{
}

File * FileManager::getFile()
{
    return this->file;
}

void FileManager::setFile(File *_file)
{
    this->file = _file;
}

bool FileManager::openFile(char _whatToLoad, QString _path)
{
    if(_whatToLoad == 's')
        this->file = new SeriesFile;
    else if(_whatToLoad == 'a')
        this->file = new AlgorithmFile;
    this->file->setFilePath(_path);
    QStringList pathParts = _path.split("/");
    QStringList nameWithoutExtension = pathParts.last().split(".");
    this->file->setName(nameWithoutExtension.first());
    QFile realFile(_path);
    if(!realFile.open(QIODevice::ReadOnly | QIODevice::Text)) // ReadOnly - plik do czytania, Text - tlumaczy nowa linie na \n
        return false;
    else
    {
        QTextStream stream(&realFile);
        this->file->setContent(stream.readAll());
        realFile.close();
        return true;
    }
}

bool FileManager::saveFile(char _whatToSave, QString _path, DataManager &_dataManager)
{
    if((_whatToSave == 'i') || (_whatToSave == 'o'))
        this->file = new SeriesFile;
    else if(_whatToSave == 'a')
        this->file = new AlgorithmFile;
    this->file->setFilePath(_path);
    this->file->setContent(this->file->prepareContentToSave(_dataManager, _whatToSave));
    QFile realFile(_path);
    if(!realFile.open(QIODevice::WriteOnly | QIODevice::Text)) // WriteOnly - plik do pisania, Text - tlumaczy nowa linie na \n
        return false;
    else
    {
        QTextStream stream(&realFile);
        stream<<this->file->getContent();
        realFile.close();
        return true;
    }
}
