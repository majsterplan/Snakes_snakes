#include "series.h"

Series::Series()
{
}

Series *Series::copy(Series *_series)
{
    Series *s = new Series;
    s->setPoints(_series->getPoints());
    return s;
}

QString Series::getName()
{
    return this->name;
}

void Series::setName(QString _name)
{
    this->name = _name;
}

std::vector<Point> Series::getPoints()
{
    return this->points;
}

void Series::setPoints(std::vector<Point> _points)
{
    this->points = _points;
}

void Series::addPoint(QDateTime _time, double _value, double _reliability)
{
    Point point;
    point.setTime(_time);
    point.setValue(_value);
    point.setReliability(_reliability);
    this->points.push_back(point);
}
