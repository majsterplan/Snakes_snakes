#include "pythoninterpreter.h"
#include <QDebug>

PythonInterpreter::PythonInterpreter()
{
}

void PythonInterpreter::initialize()
{
    Py_Initialize();
}

double PythonInterpreter::execute(QString _script, double _inputValue)
{
    try
    {
        boost::python::object main_module = boost::python::import("__main__");
        boost::python::object main_namespace = main_module.attr("__dict__");
        main_module.attr("x") = _inputValue;
        boost::python::exec((boost::python::str)_script.toStdString(), main_namespace);
        return boost::python::extract<double>(main_namespace["result"]);
    }
    catch(boost::python::error_already_set)
    {
        return 0;
    }
}

void PythonInterpreter::finalize()
{
    Py_Finalize();
}
