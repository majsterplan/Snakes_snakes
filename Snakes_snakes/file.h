#ifndef FILE_H
#define FILE_H

#include <QString>
#include "ifile.h"

/**
 * @brief Klasa File - obiekty tej klasy przechowują informacje o pliku z którego są wczytywane dane
 */
class File : public IFile
{
public:
    File();
    virtual ~File();

    /**
     * @brief getName - metoda pobiera nazwę pliku
     * @return - nazwa pliku
     */
    QString getName();

    /**
     * @brief setName - metoda ustawia nazwę pliku
     * @param _name - nazwa pliku do ustawienia
     */
    void setName(QString _name);

    /**
     * @brief getFilePath - metoda pobiera ścieżkę do pliku
     * @return - ścieżka do pliku
     */
    QString getFilePath();

    /**
     * @brief setFilePath - metoda ustawia ścieżkę do pliku
     * @param _path - ścieżka do pliku do ustawienia
     */
    void setFilePath(QString _path);

    /**
     * @brief getContent - metoda pobiera zawartość pliku
     * @return - zawartość pliku
     */
    QString getContent();

    /**
     * @brief setContent - metoda ustawia zawartość pliku
     * @param _content - zawartość pliku do ustawienia
     */
    void setContent(QString _content);
    virtual QStringList prepareContentToSet() = 0;
    virtual QString prepareContentToSave(DataManager &_dataManger, char c) = 0;

protected:
    /**
     * @brief fileName - nazwa pliku
     */
    QString fileName;

    /**
     * @brief filePath - ścieżka do pliku
     */
    QString filePath;

    /**
     * @brief fileContent - zwartość pliku
     */
    QString fileContent;
};

#endif // FILE_H
