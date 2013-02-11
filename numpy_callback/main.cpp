
#include "Python.h"

#include <iostream>

using namespace std;

// this code does:
//  0. initialize python, set module search path
//  1. load module
//  2. get attribute from module (should be a class?)
//  3. call the attribute (instantiate class?)
//  4. call the object's "execute" method

int main( int argc, char *argv[] )
{
    if (argc < 3) {
        fprintf(stderr,"Usage: numpy_callback pythonfile classname\n");
        return 1;
    }

    Py_Initialize();

    // Set module search path(s)
    PySys_SetPath( L"." );

    // append to module search path
    PyObject *pPath = PySys_GetObject((char*)"path");
    PyList_Append( pPath, PyUnicode_FromString("..") );

    PyObject_Print( pPath, stdout, 0 );
    std::cout << std::endl;

    PyObject *pName = PyUnicode_FromString( argv[1] );
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule == NULL)
    {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return -1;
    }

    PyObject_Print( pModule, stdout, 0 );
    std::cout << std::endl;

    PyObject *pClass = PyObject_GetAttrString( pModule, argv[2] );

    if( !pClass )
    {
        Py_DECREF(pModule);
        PyErr_Print();
        return -1;
    }

    PyObject_Print( pClass, stdout, 0 );
    std::cout << std::endl;

    PyObject *pInst = PyObject_CallObject( pClass, NULL );

    if( !pInst )
    {
        PyErr_Print();
    }

    PyObject_Print( pInst, stdout, 0 );
    std::cout << std::endl;

    PyObject *pCall = PyUnicode_FromString( "execute" );

    PyObject_CallMethodObjArgs( pInst, pCall , NULL );
    PyErr_Print();

    Py_DECREF(pCall);
    Py_DECREF(pInst);
    Py_DECREF(pClass);
    Py_DECREF(pModule);

    Py_Finalize();
    return 0;
}

