#include <Python.h>
#include <stdlib.h>

static PyObject * line_integrate_integers(PyObject * self, PyObject * args);


static PyMethodDef methods[] = {
	{"integrate_integers", line_integrate_integers, METH_VARARGS, "Integrate a function returning integers"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef linemodule = {
	PyModuleDef_HEAD_INIT,
	"line",
	"A C backend module used to integrate functions parametrized by lines",
	-1,
	methods
};
	

/*
PyMODINIT_FUNC init_line(void)
{
	PyObject * module = Py_InitModule3("line", methods, "Line integrals in C");
	if(!module)
	{
		return;
	}
}
*/

PyMODINIT_FUNC PyInit_line(void)
{
	return PyModule_Create(&linemodule);
}

static PyObject * line_integrate_integers(PyObject * self, PyObject * args)
{
	return PyLong_FromLong(0L);
}
