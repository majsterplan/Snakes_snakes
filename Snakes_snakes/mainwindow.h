#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QObject>
#include <QListWidgetItem>
#include <vector>
#include "filemanager.h"
#include "datamanager.h"
#include "series.h"

class FileManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showSeries(char _whichSeries);
    void showAlgorithm();
    void refreshListOfSeries(char _whichSeries);
    void refreshListOfAlgorithms();
    
private slots:
    void showOpenFileDialog();
    void showSaveFileDialog();
    void on_pushButton_Dodaj_algorytm_clicked();
    void eraseCurrentSeries();
    void eraseCurrentAlgorithm();
    void changeCurrentSeries(QListWidgetItem *, QListWidgetItem *);
    void changeCurrentAlgorithm(QListWidgetItem *, QListWidgetItem *);
    void closeProgram();
    void on_pushButton_Przetwarzaj_clicked();

private:
    Ui::MainWindow *ui;
    FileManager fileManager;
    DataManager dataManager;
};

#endif // MAINWINDOW_H
