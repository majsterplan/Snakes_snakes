#include "file.h"

File::File()
{
    this->filePath = "";
    this->fileContent = "";
    this->fileName = "";
}

File::~File()
{
}

QString File::getName()
{
    return this->fileName;
}

void File::setName(QString _name)
{
    this->fileName = _name;
}

QString File::getFilePath()
{
    return this->filePath;
}

void File::setFilePath(QString _path)
{
    this->filePath = _path;
}

QString File::getContent()
{
    return this->fileContent;
}

void File::setContent(QString _content)
{
    this->fileContent = _content;
}
