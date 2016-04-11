#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QString>

/**
 * @brief Klasa Algorithm - obiekty tej klasy przechowują informacje o algorytmach
 */
class Algorithm
{
public:
    Algorithm();

    /**
     * @brief getName - metoda pobiera nazwę algorytmu
     * @return - nazwa algorytmu
     */
    QString getName();

    /**
     * @brief setName - metoda ustawia nazwę algorytmu
     * @param _name - nazwa algorytmu do ustawienia
     */
    void setName(QString _name);

    /**
     * @brief getScript - metoda pobiera skrypt do wykonania
     * @return - skrpyt
     */
    QString getScript();

    /**
     * @brief setScript - metoda ustawia skrypt algorytmu
     * @param _script - skrypt do ustawienia
     */
    void setScript(QString _script);

private:
    /**
     * @brief name - nazwa algorytmu
     */
    QString name;

    /**
     * @brief script - skrypt algorytmu
     */
    QString script;
};

#endif // ALGORITHM_H
