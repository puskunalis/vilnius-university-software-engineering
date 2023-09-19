#include <Python.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Initialize the Python interpreter
    Py_Initialize();

    // Add the current directory to sys.path
    PyObject *sys_path = PySys_GetObject("path");
    PyObject *current_directory = PyUnicode_FromString(".");
    PyList_Append(sys_path, current_directory);
    Py_DECREF(current_directory);

    // Import the vector module
    PyObject *vector_module = PyImport_ImportModule("vector");
    if (vector_module == NULL)
    {
        PyErr_Print();
        fprintf(stderr, "Failed to import vector module\n");
        return 1;
    }

    // Get the Vector class from the module
    PyObject *vector_class = PyObject_GetAttrString(vector_module, "Vector");
    Py_DECREF(vector_module);
    if (vector_class == NULL)
    {
        PyErr_Print();
        fprintf(stderr, "Failed to get Vector class\n");
        return 1;
    }

    // Create two Vector instances
    PyObject *v1_elements = Py_BuildValue("[i,i,i]", 1, 2, 3);
    PyObject *v1 = PyObject_CallFunctionObjArgs(vector_class, v1_elements, NULL);
    PyObject *v2_elements = Py_BuildValue("[i,i,i]", 4, 5, 6);
    PyObject *v2 = PyObject_CallFunctionObjArgs(vector_class, v2_elements, NULL);

    // Call the multiply method of the first vector with the second vector as argument
    PyObject *multiply_method = PyUnicode_FromString("multiply");
    PyObject *result = PyObject_CallMethodObjArgs(v1, multiply_method, v2, NULL);
    Py_DECREF(multiply_method);
    if (result == NULL)
    {
        PyErr_Print();
        fprintf(stderr, "Failed to call multiply method\n");
        return 1;
    }

    // Get the elements of the result vector
    PyObject *result_elements = PyObject_GetAttrString(result, "elements");
    if (result_elements == NULL)
    {
        PyErr_Print();
        fprintf(stderr, "Failed to get elements attribute\n");
        return 1;
    }

    // Print the result elements
    printf("Result: ");
    PyObject_Print(result_elements, stdout, 0);
    printf("\n");

    // Clean up
    Py_DECREF(v1_elements);
    Py_DECREF(v2_elements);
    Py_DECREF(v1);
    Py_DECREF(v2);
    Py_DECREF(result);
    Py_DECREF(result_elements);
    Py_DECREF(vector_class);

    // Finalize the Python interpreter
    Py_Finalize();

    return 0;
}
