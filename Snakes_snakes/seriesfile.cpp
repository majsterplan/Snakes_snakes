#include "seriesfile.h"
#include <QDebug>

SeriesFile::SeriesFile()
{
}

QStringList SeriesFile::prepareContentToSet()
{
    QStringList rows = this->fileContent.split(QRegExp("\n"));
    QStringList cells;
    for(int i = 0; i < rows.size() - 1; i++)
    {
        QStringList cell = rows[i].split("|");
        cells = cells + cell;
    }
    return cells;
}

QString SeriesFile::prepareContentToSave(DataManager &_dataManger, char c)
{
    std::vector<Point> points;
    std::vector<Point>::iterator it;
    if(c == 'i')
    {
        points = _dataManger.getCurrentInputSeries()->getPoints();
    }
    else if(c == 'o')
    {
        points = _dataManger.getCurrentOutputSeries()->getPoints();
    }
    for(it = points.begin(); it != points.end(); it++)
    {
        this->fileContent.append((*it).getTime().toString(Qt::ISODate) +"|"+
                                 QString::number((*it).getValue()) +"|"+
                                 QString::number((*it).getReliability())+"\n");
    }
    return this->fileContent;
}
