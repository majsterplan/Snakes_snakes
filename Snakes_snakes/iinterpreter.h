#ifndef IINTERPRETER_H
#define IINTERPRETER_H

#include <QString>

/**
 * @brief Klasa IInterpreter - interfejs dla interpreterów
 */
class IInterpreter
{
public:
    IInterpreter();
    virtual ~IInterpreter();
    virtual void initialize() = 0;
    virtual double execute(QString _script, double _inputValue) = 0;
    virtual void finalize() = 0;
};

#endif // IINTERPRETER_H
