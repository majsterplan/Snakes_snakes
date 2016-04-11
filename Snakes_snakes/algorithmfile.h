#ifndef ALGORITHMFILE_H
#define ALGORITHMFILE_H

#include "datamanager.h"
#include "file.h"

/**
 * @brief Klasa AlgorithmFile - obiekty tej klasy przechowują informacje o pliku z którego jest wczytywany algorytm
 */
class AlgorithmFile : public File
{
public:
    AlgorithmFile();

    /**
     * @brief prepareContentToSet - metoda przygotowuje zawartość pliku dla pola skrypt obiektu klasy Algorithm
     * @return - przygotowana treść do ustawienia w obiecie klasy Algorithm
     */
    QStringList prepareContentToSet();

    /**
     * @brief prepareContentToSave - metoda przygotowuje skrypt do zapisu w pliu
     * @param _dataManager - parametr niezbędny do pobrania informacji o aktualnie wybranym algorytmie
     * @param c - parametr informujący o tym co będzie zapisane
     * @return - przygotowana treść do zapisu
     */
    QString prepareContentToSave(DataManager &_dataManager, char c);
};

#endif // ALGORITHMFILE_H
