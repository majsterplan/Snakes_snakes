#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ui->label_errors->hide();

    connect(ui->loadSeries, SIGNAL(triggered()), this, SLOT(showOpenFileDialog()));
    connect(ui->loadAlgorithm, SIGNAL(triggered()),this, SLOT(showOpenFileDialog()));
    connect(ui->saveCurrentInputSeries, SIGNAL(triggered()), this, SLOT(showSaveFileDialog()));
    connect(ui->saveCurrentOutputSeries, SIGNAL(triggered()), this, SLOT(showSaveFileDialog()));
    connect(ui->saveCurrentAlgorithm, SIGNAL(triggered()), this, SLOT(showSaveFileDialog()));
    connect(ui->deleteCurrentInputSeries, SIGNAL(triggered()), this, SLOT(eraseCurrentSeries()));
    connect(ui->deleteCurrentOutputSeries, SIGNAL(triggered()), this, SLOT(eraseCurrentSeries()));
    connect(ui->deleteCurrentAlgorithm, SIGNAL(triggered()), this, SLOT(eraseCurrentAlgorithm()));
    connect(ui->series, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changeCurrentSeries(QListWidgetItem *,QListWidgetItem *)));
    connect(ui->series_2, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changeCurrentSeries(QListWidgetItem *,QListWidgetItem *)));
    connect(ui->algorithms, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changeCurrentAlgorithm(QListWidgetItem*,QListWidgetItem*)));
    connect(ui->end, SIGNAL(triggered()), this, SLOT(closeProgram()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showOpenFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Otwórz plik..."));
    if(!filePath.isEmpty())
    {
        QObject *obj = sender(); // sender() zwraca wskaznik na to skad pochodzil sygnal
        bool allRight = true;
        char c;
        if(obj == this->ui->loadSeries)
            c = 's';
        else if(obj == this->ui->loadAlgorithm)
            c = 'a';
        allRight = this->fileManager.openFile(c, filePath);
        if(!allRight)
        {
            this->ui->label_errors->setText("Błąd odczytu pliku.");
            if(this->ui->label_errors->isHidden())
                this->ui->label_errors->show();
        }
        else
        {
            if(!this->ui->label_errors->text().isEmpty())
                this->ui->label_errors->clear();
            if(!this->ui->label_errors->isHidden())
                this->ui->label_errors->hide();
            if(c == 's')
            {
                this->dataManager.addSeriesFromFile(this->fileManager.getFile());
                this->ui->series->addItem(this->dataManager.getCurrentInputSeries()->getName());
                // this->ui->series->setCurrentRow(this->ui->series->count() - 1, QItemSelectionModel::ClearAndSelect);
                // this->showSeries('i');
                this->ui->series->setCurrentRow(this->ui->series->count() - 1);
                delete this->fileManager.getFile();
            }
            else if(c == 'a')
            {
                if(this->dataManager.getCurrentAlgorithm() != NULL)
                    this->dataManager.getCurrentAlgorithm()->setScript(this->ui->script->toPlainText());
                this->dataManager.addAlgorithmFromFile(this->fileManager.getFile());
                this->ui->algorithms->addItem(this->dataManager.getCurrentAlgorithm()->getName());
                // this->ui->algorithms->setCurrentRow(this->ui->algorithms->count() - 1, QItemSelectionModel::ClearAndSelect);
                if(this->ui->script->isReadOnly())
                    this->ui->script->setReadOnly(false);
                // this->showAlgorithm();
                this->ui->algorithms->setCurrentRow(this->ui->algorithms->count() - 1);
                delete this->fileManager.getFile();
            }
        }
    }
}

void MainWindow::showSaveFileDialog()
{
    QObject *obj = sender(); // sender() zwraca wskaznik na to skad pochodzil sygnal
    if((this->ui->series->count() == 0) && (obj == this->ui->saveCurrentInputSeries))
    {
        this->ui->label_errors->setText("Brak serii do zapisu.");
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->show();
    }
    else if((this->ui->algorithms->count() == 0) && (obj == this->ui->saveCurrentAlgorithm))
    {
        this->ui->label_errors->setText("Brak algorytmu do zapisu.");
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->show();
    }
    else if((this->ui->series_2->count() == 0) && (obj == this->ui->saveCurrentOutputSeries))
    {
        this->ui->label_errors->setText("Brak serii do zapisu.");
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->show();
    }
    else
    {
        if(!this->ui->label_errors->text().isEmpty())
            this->ui->label_errors->clear();
        if(!this->ui->label_errors->isHidden())
            this->ui->label_errors->hide();
        QString filePath=QFileDialog::getSaveFileName(this, tr("Zapisz plik..."));
        bool allRight = true;
        char c;
        if(obj == this->ui->saveCurrentInputSeries)
            c = 'i';
        else if(obj == this->ui->saveCurrentOutputSeries)
            c = 'o';
        if(obj == this->ui->saveCurrentAlgorithm)
        {
            c = 'a';
            this->dataManager.getCurrentAlgorithm()->setScript(this->ui->script->toPlainText());
        }
        allRight = this->fileManager.saveFile(c, filePath, this->dataManager);
        if(!allRight)
        {
            this->ui->label_errors->setText("Błąd zapisu pliku.");
            if(this->ui->label_errors->isHidden())
                this->ui->label_errors->show();
        }
        else
        {
            if(!this->ui->label_errors->text().isEmpty())
                this->ui->label_errors->clear();
            if(!this->ui->label_errors->isHidden())
                this->ui->label_errors->hide();
            delete this->fileManager.getFile();
        }
    }
}

void MainWindow::showSeries(char _whichSeries)
{
    std::vector<Point>::iterator it;
    std::vector<Point> pointsToShow;
    int row = 0;
    if(_whichSeries == 'i')
    {
        pointsToShow = this->dataManager.getCurrentInputSeries()->getPoints();
        this->ui->points->setRowCount(pointsToShow.size());
        this->ui->points->verticalHeader()->setVisible(false);
    }
    else if(_whichSeries == 'o')
    {
        pointsToShow = this->dataManager.getCurrentOutputSeries()->getPoints();
        this->ui->points_2->setRowCount(pointsToShow.size());
        this->ui->points_2->verticalHeader()->setVisible(false);
    }
    for(it = pointsToShow.begin(); it != pointsToShow.end(); it++)
    {
        QTableWidgetItem *data = new QTableWidgetItem((*it).getTime().toString());
        data->setFlags(Qt::ItemIsEnabled);
        QTableWidgetItem *value = new QTableWidgetItem(QString::number((*it).getValue(), 'f'));
        value->setFlags(Qt::ItemIsEnabled);
        QTableWidgetItem *reliability = new QTableWidgetItem(QString::number((*it).getReliability(), 'f'));
        reliability->setFlags(Qt::ItemIsEnabled);
        if(_whichSeries == 'i')
        {
            this->ui->points->setItem(row, 0, data);
            this->ui->points->setItem(row, 1, value);
            this->ui->points->setItem(row, 2, reliability);
        }
        else if(_whichSeries == 'o')
        {
            this->ui->points_2->setItem(row, 0, data);
            this->ui->points_2->setItem(row, 1, value);
            this->ui->points_2->setItem(row, 2, reliability);
        }
        row+=1;
    }
}

void MainWindow::showAlgorithm()
{
    // this->ui->script->clear();
    this->ui->script->setText(this->dataManager.getCurrentAlgorithm()->getScript());
}

void MainWindow::refreshListOfSeries(char _whichSeries)
{
    std::vector<Series *> seriesToShow;
    std::vector<Series *>::iterator it;
    if(_whichSeries == 'i')
    {
        seriesToShow = this->dataManager.getInputSeries();
        for(it = seriesToShow.begin(); it != seriesToShow.end(); it++)
            this->ui->series->addItem((*it)->getName());
    }
    else if(_whichSeries == 'o')
    {
        seriesToShow = this->dataManager.getOutputSeries();
        for(it = seriesToShow.begin(); it != seriesToShow.end(); it++)
            this->ui->series_2->addItem((*it)->getName());
    }
}

void MainWindow::refreshListOfAlgorithms()
{
    std::vector<Algorithm *> algorithmsToShow;
    std::vector<Algorithm *>::iterator it;
    algorithmsToShow = this->dataManager.getAlgorithms();
    for(it = algorithmsToShow.begin(); it != algorithmsToShow.end(); it++)
    {
        this->ui->algorithms->addItem((*it)->getName());
    }
}

void MainWindow::on_pushButton_Dodaj_algorytm_clicked()
{
    if(this->ui->new_algorithm_name->text().isEmpty())
    {
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->setHidden(false);
        this->ui->label_errors->setText("Podaj nazwe wprowadzanego algorytmu.");
    }
    else
    {
        if(!this->ui->label_errors->text().isEmpty())
            this->ui->label_errors->clear();
        if(!this->ui->label_errors->isHidden())
            this->ui->label_errors->hide();
        if(this->dataManager.getCurrentAlgorithm() != NULL)
            this->dataManager.getCurrentAlgorithm()->setScript(this->ui->script->toPlainText());
        this->dataManager.addNewAlgorithm(this->ui->new_algorithm_name->text());
        this->ui->algorithms->addItem(this->dataManager.getCurrentAlgorithm()->getName());
        // this->ui->algorithms->setCurrentRow(this->ui->algorithms->count() - 1, QItemSelectionModel::ClearAndSelect);
        if(this->ui->script->isReadOnly())
            this->ui->script->setReadOnly(false);
        // this->showAlgorithm();
        this->ui->algorithms->setCurrentRow(this->ui->algorithms->count() - 1);
        this->ui->new_algorithm_name->clear();
    }
}

void MainWindow::eraseCurrentSeries()
{
    QObject *obj = sender(); // sender() zwraca wskaznik na to skad pochodzil sygnal
    char c;
    if((this->ui->series->count() == 0) && (obj == this->ui->deleteCurrentInputSeries))
    {
        this->ui->label_errors->setText("Brak serii do usunięcia.");
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->show();
    }
    else if((this->ui->series_2->count() == 0) && (obj == this->ui->deleteCurrentOutputSeries))
    {
        this->ui->label_errors->setText("Brak serii do usunięcia.");
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->show();
    }
    else
    {
        if(!this->ui->label_errors->text().isEmpty())
            this->ui->label_errors->clear();
        if(!this->ui->label_errors->isHidden())
            this->ui->label_errors->hide();
        if(obj == this->ui->deleteCurrentInputSeries)
        {
            c = 'i';
            this->dataManager.deleteSeries(this->ui->series->currentRow(), c);
            this->ui->series->clear();
            this->ui->points->setRowCount(0);
            if(this->dataManager.getInputSeries().size() != 0)
            {
                this->refreshListOfSeries(c);
                this->ui->series->setCurrentRow(this->ui->series->count() - 1);
                this->showSeries(c);
            }
        }
        else if(obj == this->ui->deleteCurrentOutputSeries)
        {
            c = 'o';
            this->dataManager.deleteSeries(this->ui->series_2->currentRow(), c);
            this->ui->series_2->clear();
            this->ui->points_2->setRowCount(0);
            if(this->dataManager.getOutputSeries().size() != 0)
            {
                this->refreshListOfSeries(c);
                this->ui->series_2->setCurrentRow(this->ui->series_2->count() - 1);
                this->showSeries(c);
            }
        }
    }
}

void MainWindow::eraseCurrentAlgorithm()
{
    if(this->ui->algorithms->count() == 0)
    {
        this->ui->label_errors->setText("Brak algorytmów do usunięcia.");
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->show();
    }
    else
    {
        if(!this->ui->label_errors->text().isEmpty())
            this->ui->label_errors->clear();
        if(!this->ui->label_errors->isHidden())
            this->ui->label_errors->hide();
        int algorithmToDelete = this->ui->algorithms->currentRow();
        this->ui->algorithms->clear();
        this->dataManager.deleteAlgorithm(algorithmToDelete);
        this->ui->script->clear();
        if(this->dataManager.getAlgorithms().size() != 0)
        {
            this->refreshListOfAlgorithms();
            this->ui->algorithms->setCurrentRow(this->ui->algorithms->count() - 1);
            this->showAlgorithm();
        }
        else
        {
            this->ui->script->setReadOnly(true);
        }
    }
}

void MainWindow::changeCurrentSeries(QListWidgetItem *, QListWidgetItem *)
{
    QObject *obj = sender(); // sender() zwraca wskaznik na to skad pochodzil sygnal
    char c;
    if(obj == this->ui->series)
    {
        c = 'i';
        this->dataManager.setCurrentInputSeries(this->ui->series->currentRow());
        if(this->dataManager.getCurrentInputSeries() != NULL)
            this->showSeries(c);
    }
    else if(obj == this->ui->series_2)
    {
        c = 'o';
        this->dataManager.setCurrentOutputSeries(this->ui->series_2->currentRow());
        if(this->dataManager.getCurrentOutputSeries() != NULL)
            this->showSeries(c);
    }
}

void MainWindow::changeCurrentAlgorithm(QListWidgetItem *, QListWidgetItem *)
{
    // if(this->dataManager.getCurrentAlgorithm() != NULL)
    // {
    //     this->dataManager.getCurrentAlgorithm()->setScript(this->ui->script->toPlainText());
    // }
    this->dataManager.setCurrentAlgorithm(this->ui->algorithms->currentRow());
    if(this->dataManager.getCurrentAlgorithm() != NULL)
        this->showAlgorithm();
}

void MainWindow::closeProgram()
{
    this->close();
}

void MainWindow::on_pushButton_Przetwarzaj_clicked()
{
    if(this->ui->new_series_name->text().isEmpty())
    {
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->setHidden(false);
        this->ui->label_errors->setText("Podaj nazwe generowanej serii.");
    }
    else if(this->dataManager.getCurrentAlgorithm() == NULL)
    {
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->setHidden(false);
        this->ui->label_errors->setText("Brak algorytmu/serii wejściowej.");
    }
    else if(this->dataManager.getCurrentInputSeries() == NULL)
    {
        if(this->ui->label_errors->isHidden())
            this->ui->label_errors->setHidden(false);
        this->ui->label_errors->setText("Brak algorytmu/serii wejściowej.");
    }
    else
    {
        this->dataManager.getCurrentAlgorithm()->setScript(this->ui->script->toPlainText());
        if(!this->ui->label_errors->text().isEmpty())
            this->ui->label_errors->clear();
        if(!this->ui->label_errors->isHidden())
            this->ui->label_errors->hide();
        this->dataManager.prepareNewSeries(this->ui->new_series_name->text());
        this->ui->series_2->addItem(this->dataManager.getCurrentOutputSeries()->getName());
        // this->ui->algorithms->setCurrentRow(this->ui->algorithms->count() - 1, QItemSelectionModel::ClearAndSelect);
        this->ui->series_2->setCurrentRow(this->ui->series_2->count() - 1);
        this->ui->new_series_name->clear();
    }
}
