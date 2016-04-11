#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <QString>
#include "series.h"
#include "algorithm.h"
#include "filemanager.h"
#include "ifile.h"
#include "pythoninterpreter.h"
#include "iinterpreter.h"

class Series;
class Algorithm;
class FileManager;
class IFile;
class IInterpreter;

/**
 * @brief Klasa DataManager - obiekt tej klasy zarządza przetwarzanymi w programie danymi, tj. algorytmami i seriami
 */
class DataManager
{
public:
    DataManager();

    /**
     * @brief getCurrentAlgorithm - metoda pobiera wskaźnik na aktualnie wybrany algorytm
     * @return - wskaźnik do aktualnie wybranego algorytmu
     */
    Algorithm * getCurrentAlgorithm();

    /**
     * @brief getAlgorithms - metoda pobiera wskaźniki na wszystkie algorytmy
     * @return - wektor wskaźników na algorytmy
     */
    std::vector<Algorithm *> getAlgorithms();

    /**
     * @brief setCurrentAlgorithm - metoda ustawia wskaźnik na aktualnie wybrany algorytm
     * @param _algorithmRow - numer wiersza wybranego algorytmu w okienku głównym
     */
    void setCurrentAlgorithm(int _algorithmRow);

    /**
     * @brief getCurrentInputSeries - metoda pobiera wskaźnik na aktualnie wybraną serię wejściową
     * @return - wskaźni do aktualnie wybranej serii wejściowej
     */
    Series * getCurrentInputSeries();

    /**
     * @brief getInputSeries - metoda pobiera wskaźniki na wszystkie serie wejściowe
     * @return - wektor wskaźników na serie wejściowe
     */
    std::vector<Series *> getInputSeries();

    /**
     * @brief setCurrentInputSeries - metoda ustawia wskaźnik na aktualnie wybraną serię wejściową
     * @param _inputSeriesRow - numer wiersza wybranej serii wejściowej w okienku głównym
     */
    void setCurrentInputSeries(int _inputSeriesRow);

    /**
     * @brief getCurrentOutputSeries - metoda pobiera wskaźnik na aktualnie wybraną serię wyjściową
     * @return - wskaźnik do aktualnie wybranej serii wyjściowej
     */
    Series * getCurrentOutputSeries();

    /**
     * @brief getOutputSeries - metoda pobiera wskaźniki na wszystkie serie wyjściowe
     * @return - wektor wskaźników na serie wyjściowe
     */
    std::vector<Series *> getOutputSeries();

    /**
     * @brief setCurrentOutputSeries - metoda ustawia wskaźnik na aktualnie wybraną serię wyjściową
     * @param _outputSeries - numer wiersza wybranej serii wyjściowej w okienku głównym
     */
    void setCurrentOutputSeries(int _outputSeries);

    /**
     * @brief addSeriesFromFile - metoda dodaje serię z pliku
     * @param _file - obsługiwany plik
     */
    void addSeriesFromFile(IFile *_file);

    /**
     * @brief deleteSeries - metoda usuwa serię
     * @param _currentSeries - numer wiersza wybranej aktualnie serii wejściowej/wyjściowej w okienku głównym
     * @param _whichSeries - parametr informujący o tym która seria jest do usunięcia: wejściowa czy wyjściowa
     */
    void deleteSeries(int _currentSeries, char _whichSeries);

    /**
     * @brief addNewAlgorithm - metoda dodaje nowy algorytm
     * @param _name - nazwa nowego algorytmu
     */
    void addNewAlgorithm(QString _name);

    /**
     * @brief addAlgorithmFromFile - metoda dodaje algorytm z pliku
     * @param _file - obsługiwany plik
     */
    void addAlgorithmFromFile(IFile *_file);

    /**
     * @brief deleteAlgorithm - metoda usuwa algorytm
     * @param _currentAlgorithm - numer wiersza wybranego aktualnie algorytmu w okienku głównym
     */
    void deleteAlgorithm(int _currentAlgorithm);

    /**
     * @brief prepareNewSeries - metoda przygotowuje nową serię wyjściową
     * @param _name - nazwa nowej serii
     */
    void prepareNewSeries(QString _name);

private:
    /**
     * @brief inputSeries - wektor wskaźników na dostępne serie wejściowe
     */
    std::vector<Series *> inputSeries;

    /**
     * @brief outputSeries - wektor wskaźników na dostępne serie wyjściowe
     */
    std::vector<Series *> outputSeries;

    /**
     * @brief algorithms - wektor wskaźników na dostępne algorytmy
     */
    std::vector<Algorithm *> algorithms;

    /**
     * @brief currentInputSeries - wskaźnik na aktualnie wybraną serię wejściową
     */
    Series *currentInputSeries;

    /**
     * @brief currentOutputSeries - wskaźnik na aktualnie wybraną serię wyjściową
     */
    Series *currentOutputSeries;

    /**
     * @brief currentAlgorithm - wskaźnik na aktualnie wybrany algorytm
     */
    Algorithm *currentAlgorithm;
};

#endif // DATAMANAGER_H
