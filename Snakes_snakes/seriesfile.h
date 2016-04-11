#ifndef SERIESFILE_H
#define SERIESFILE_H

#include "datamanager.h"
#include "file.h"

/**
 * @brief Klasa SeriesFile - obiekty tej klasy przechowują informacje o pliku z którego jest wczytywana seria
 */
class SeriesFile : public File
{
public:
    SeriesFile();

    /**
     * @brief prepareContentToSet - metoda przygotowuje zawartość pliku dla pól obiektu klasy Series
     * @return - przygotowana treść do ustawienia w obiecie klasy Series
     */
    QStringList prepareContentToSet();

    /**
     * @brief prepareContentToSave - metoda przygotowuje skrypt do zapisu w pliu
     * @param _dataManger - parametr niezbędny do pobrania informacji o aktualnie wybranej serii
     * @param c - parametr informujący o tym co będzie zapisane
     * @return - przygotowana treść do zapisu
     */
    QString prepareContentToSave(DataManager &_dataManger, char c);
};

#endif // SERIESFILE_H
