
#include <Python.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include <numpy/numpyconfig.h>

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
    import_array( );    // initialize numpy

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

    // create a numpy array
    npy_intp dims[] = {2, 3};
    //npy_intp dims[2] = {0,0};
    PyObject* pData = PyArray_SimpleNew( 2, dims, NPY_DOUBLE );

    PyObject *pCall = PyUnicode_FromString( "execute" );


    PyObject_Print( pData, stdout, 0 );
    std::cout << std::endl;

    // two ways to avoid allocation:
    // 1. use the parameter as i/o, no return value
    // 2. return the parameter as return value
    //
    // The first has the advantage that the user cannot return a completely
    // new object, but this is not very pythonic(?).
    //
    // The second allows the user to return any value. But if they return the
    // parameter, no new stuff will be created. So it's up to the user to
    // avoid allocation. However, this could lead to problems with handling
    // of *any* return types...
    PyObject *pRet = PyObject_CallMethodObjArgs( pInst, pCall, pData, NULL );

    PyObject_Print( pData, stdout, 0 );
    std::cout << std::endl;


    Py_DECREF(pRet);
    Py_DECREF(pData);
    Py_DECREF(pCall);
    Py_DECREF(pInst);
    Py_DECREF(pClass);
    Py_DECREF(pModule);

    Py_Finalize();
    return 0;
}

