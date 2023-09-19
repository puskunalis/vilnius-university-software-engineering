#include <Python.h>
#include <ctype.h>

static int is_alphanumeric(char c)
{
    return isalnum((unsigned char)c);
}

static PyObject *is_palindrome(PyObject *self, PyObject *args)
{
    const char *input;
    if (!PyArg_ParseTuple(args, "s", &input))
    {
        PyErr_SetString(PyExc_TypeError, "Input must be a string");
        return NULL;
    }

    int left = 0;
    int right = strlen(input) - 1;

    while (left < right)
    {
        while (left < right && !is_alphanumeric(input[left]))
        {
            left++;
        }
        while (left < right && !is_alphanumeric(input[right]))
        {
            right--;
        }
        if (tolower(input[left]) != tolower(input[right]))
        {
            Py_RETURN_FALSE;
        }
        left++;
        right--;
    }
    Py_RETURN_TRUE;
}

static PyMethodDef PalindromeMethods[] = {
    {"is_palindrome", is_palindrome, METH_VARARGS, "Check if a given string is a palindrome"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef palindromemodule = {
    PyModuleDef_HEAD_INIT,
    "palindrome_module",
    NULL,
    -1,
    PalindromeMethods};

PyMODINIT_FUNC PyInit_palindrome_module(void)
{
    return PyModule_Create(&palindromemodule);
}
