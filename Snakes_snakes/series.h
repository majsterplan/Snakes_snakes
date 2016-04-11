#ifndef SERIES_H
#define SERIES_H

#include <QString>
#include <vector>
#include "point.h"

class Point;

/**
 * @brief Klasa Series - obiekt tej klasy przechowuje informacje o serii
 */
class Series
{
public:
    Series();

    /**
     * @brief copy - metoda kopiuje serię (kopiowanie głębokie)
     * @param _series - seria do skopiowania
     * @return - wskaźnik na nową serię
     */
    static Series * copy(Series *_series);

    /**
     * @brief getName - metoda pobiera nazwę serii
     * @return - nazwa serii
     */
    QString getName();

    /**
     * @brief setName - metoda ustawia nazwę serii
     * @param _name - nazwa serii do ustawienia
     */
    void setName(QString _name);

    /**
     * @brief getPoints - metoda pobiera punkty wchodzące w skład serii
     * @return - wektor punktów wchodzących w skład serii
     */
    std::vector<Point> getPoints();

    /**
     * @brief setPoints - metoda ustawia punkty dla serii
     * @param _points - punkty do ustawienia
     */
    void setPoints(std::vector<Point> _points);

    /**
     * @brief addPoint - metoda służy do dodawania punktów dla serii
     * @param _time - znacznik czasowy nowego punktu w serii
     * @param _value - wartość pomiaru nowego punktu w serii
     * @param _reliability - wiarygodność nowego punktu w serii
     */
    void addPoint(QDateTime _time, double _value, double _reliability);

private:
    /**
     * @brief name - nazwa serii
     */
    QString name;

    /**
     * @brief points - wektor punktów serii
     */
    std::vector<Point> points;
};

#endif // SERIES_H
