#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QStringList>
#include <QObject>
#include <QTextStream>
#include <QFile>
#include "datamanager.h"
#include "file.h"
#include "seriesfile.h"
#include "algorithmfile.h"

class DataManager;
class File;

/**
 * @brief Klasa FileManager - obiekt tej klasy służy do obsługi plików wczytywanych do programu
 */
class FileManager
{
public:
    FileManager();

    /**
     * @brief getFile - metoda pobiera wskaźnik na aktualnie obsługiwanego pliku
     * @return - wskaźni do aktualnie obsługiwanego pliku
     */
    File * getFile();

    /**
     * @brief setFile - metoda ustawia wskaźnik na aktualnie obsługiwany plik
     * @param _file - plik do ustawienia
     */
    void setFile(File *_file);

    /**
     * @brief openFile - metoda służy do otwierania pliku
     * @param _whatToLoad - parametr informujący o tym co jest do wczytania: algorytm czy seria
     * @param _path - ścieżka pliu do odczytu
     * @return - czy poprawnie wczytano plik
     */
    bool openFile(char _whatToLoad, QString _path);

    /**
     * @brief saveFile - metoda służy do zapisywania pliku
     * @param _whatToSave - parametr informujący o tym co jest do zapisania: algorytm czy seria
     * @param _path - ścieżka pliku do zapisu
     * @param _dataManager - parametr niezbędny do pobrania informacji o aktualnie wybranych danych do zapisu
     * @return - czy poprawnie zapisano plik
     */
    bool saveFile(char _whatToSave, QString _path, DataManager &_dataManager);

private:  
    /**
     * @brief file - wskaźnik na aktualnie obsługiwany plik
     */
    File *file;
};

#endif // FILEMANAGER_H
