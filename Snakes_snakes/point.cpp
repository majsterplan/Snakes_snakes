#include "point.h"

Point::Point()
{
}

QDateTime Point::getTime()
{
    return this->time;
}

void Point::setTime(QDateTime _time)
{
    this->time = _time;
}

double Point::getValue()
{
    return this->value;
}

void Point::setValue(double _value)
{
    this->value = _value;
}

double Point::getReliability()
{
    return this->reliability;
}

void Point::setReliability(double _reliability)
{
    this->reliability = _reliability;
}
