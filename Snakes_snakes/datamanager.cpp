#include "datamanager.h"

DataManager::DataManager()
{
    this->currentAlgorithm = NULL;
    this->currentInputSeries = NULL;
    this->currentOutputSeries = NULL;
}

Algorithm * DataManager::getCurrentAlgorithm()
{
    return this->currentAlgorithm;
}

std::vector<Algorithm *> DataManager::getAlgorithms()
{
    return this->algorithms;
}

void DataManager::setCurrentAlgorithm(int _algorithmRow)
{
    if(_algorithmRow != -1)
        this->currentAlgorithm = this->algorithms.at(_algorithmRow);
    else
        this->currentAlgorithm = NULL;
}

Series * DataManager::getCurrentInputSeries()
{
    return this->currentInputSeries;
}

std::vector<Series *> DataManager::getInputSeries()
{
    return this->inputSeries;
}

void DataManager::setCurrentInputSeries(int _inputSeriesRow)
{
    if(_inputSeriesRow != -1)
        this->currentInputSeries = this->inputSeries.at(_inputSeriesRow);
    else
        this->currentInputSeries = NULL;
}

Series * DataManager::getCurrentOutputSeries()
{
    return this->currentOutputSeries;
}

std::vector<Series *> DataManager::getOutputSeries()
{
    return this->outputSeries;
}

void DataManager::setCurrentOutputSeries(int _outputSeries)
{
    if(_outputSeries != -1)
        this->currentOutputSeries = this->outputSeries.at(_outputSeries);
    else
        this->currentOutputSeries = NULL;
}

void DataManager::addSeriesFromFile(IFile *_file)
{
    Series *series = new Series;
    QStringList points = _file->prepareContentToSet();
    series->setName(_file->getName());
    for(int i = 0; i < points.size()/3; i++)
    {
        series->addPoint(QDateTime::fromString(points[3*i], Qt::ISODate),
                         points[3*i+1].toDouble(), points[3*i+2].toDouble());
    }
    this->currentInputSeries = series;
    this->inputSeries.push_back(series);
}

void DataManager::deleteSeries(int _currentSeries, char _whichSeries)
{
    if(_whichSeries == 'i')
    {
        this->inputSeries.erase(inputSeries.begin() + _currentSeries);
        delete this->currentInputSeries;
    }
    if(_whichSeries == 'o')
    {
        this->outputSeries.erase(outputSeries.begin() + _currentSeries);
        delete this->currentOutputSeries;
    }
}

void DataManager::addNewAlgorithm(QString _name)
{
    Algorithm *algorithm = new Algorithm;
    algorithm->setName(_name);
    algorithm->setScript("");
    this->currentAlgorithm = algorithm;
    this->algorithms.push_back(algorithm);
}

void DataManager::addAlgorithmFromFile(IFile *_file)
{
    Algorithm *algorithm = new Algorithm;
    QStringList script = _file->prepareContentToSet();
    algorithm->setName(_file->getName());
    algorithm->setScript(script.first());
    this->currentAlgorithm = algorithm;
    this->algorithms.push_back(algorithm);
}

void DataManager::deleteAlgorithm(int _currentAlgorithm)
{
    this->algorithms.erase(algorithms.begin() + _currentAlgorithm);
    delete this->currentAlgorithm;
}

void DataManager::prepareNewSeries(QString _name)
{
    Series *newSeries = Series::copy(this->currentInputSeries);
    newSeries->setName(_name);
    std::vector<Point> pointsToCalculate = newSeries->getPoints();
    std::vector<Point>::iterator it;
    IInterpreter *interpreter = new PythonInterpreter;
    interpreter->initialize();
    for(it = pointsToCalculate.begin(); it != pointsToCalculate.end(); it++)
        (*it).setValue(interpreter->execute(this->currentAlgorithm->getScript(),
                                            (*it).getValue()));
    interpreter->finalize();
    delete interpreter;
    newSeries->setPoints(pointsToCalculate);
    this->currentOutputSeries = newSeries;
    this->outputSeries.push_back(newSeries);
}
