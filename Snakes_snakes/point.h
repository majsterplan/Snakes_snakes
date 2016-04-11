#ifndef POINT_H
#define POINT_H

#include <QDateTime>

/**
 * @brief Klasa Point - obiekty tej klasy przechowują informacje o punkcie serii
 */
class Point
{
public:
    Point();

    /**
     * @brief getTime - metoda pobiera znacznik czasowy punktu
     * @return - znacznik czasowy punktu
     */
    QDateTime getTime();

    /**
     * @brief setTime - metoda ustawia znacznik czasowy punktu
     * @param _time - znacznik czasowy punktu do ustawienia
     */
    void setTime(QDateTime _time);

    /**
     * @brief getValue - metoda pobiera wartość punktu
     * @return - wartość punktu
     */
    double getValue();

    /**
     * @brief setValue - metoda ustawia wartość punktu
     * @param _value - wartość punktu do ustawienia
     */
    void setValue(double _value);

    /**
     * @brief getReliability - metoda pobiera wiarygodność punktu
     * @return - wiarygodność punktu
     */
    double getReliability();

    /**
     * @brief setReliability - metoda ustawia wiarygodność punktu
     * @param _reliability - wiarygodność punktu do ustawienia
     */
    void setReliability(double _reliability);

private:
    /**
     * @brief time - znacznik czasowy punktu
     */
    QDateTime time;

    /**
     * @brief value - wartość punktu
     */
    double value;

    /**
     * @brief reliability - wiarygodność punktu
     */
    double reliability;
};

#endif // POINT_H
