#ifndef PYTHONINTERPRETER_H
#define PYTHONINTERPRETER_H

#include "iinterpreter.h"
#include "boost/python.hpp"

/**
 * @brief Klasa PythonInterpreter - interpreter
 */
class PythonInterpreter : public IInterpreter
{
public:
    PythonInterpreter();

    /**
     * @brief initialize - metoda inicjalizuje pracę interpretera
     */
    void initialize();

    /**
     * @brief execute - metoda wywołuje skrypt na wybranej danej
     * @param _script - skrypt do wykonania
     * @param _inputValue - wartość punktu do przetworzenia
     * @return
     */
    double execute(QString _script, double _inputValue);

    /**
     * @brief finalize - metoda finalizuje działanie interpretera
     */
    void finalize();
};

#endif // PYTHONINTERPRETER_H
