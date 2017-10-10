#include <Python.h>
#include <math.h>

static PyObject * line_integrate_float_rect(PyObject * self, PyObject * args);

static PyMethodDef methods[] = {
	{
		"integrate_float_rect", 
		line_integrate_float_rect, 
		METH_VARARGS, 
		"Integrate a function returning float using rects."},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef linemodule = {
	PyModuleDef_HEAD_INIT,
	"nf.fast.do.line",
	"A C backend module used to integrate functions parametrized by lines",
	-1,
	methods
};
	


PyMODINIT_FUNC PyInit_line(void)
{
	return PyModule_Create(&linemodule);
}

static PyObject * line_integrate_float_rect(PyObject * self, PyObject * args)
{

	PyObject * parametrization;
	PyObject * step_width;
	PyObject * parametrization_nocheck;
	PyObject * step_width_nocheck;
	PyObject * func;

	PyObject * point;
	PyObject * step;
	PyObject * this_result;
	double this_result_float = 0;
	double this_rect = 0;
	double result = 0;


	if(!PyArg_ParseTuple(args, "OOO", &parametrization_nocheck, &step_width_nocheck, &func))
	{
		return NULL;
	}
	
	if(!PyCallable_Check(func))
	{
		PyErr_SetString(PyExc_TypeError, "func (args[2]) must be callable");
		return NULL;
	}
	if(!PyIter_Check(parametrization_nocheck))
	{
		PyErr_SetString(PyExc_TypeError, "parametrization (args[0]) must be iterable");
		return NULL;
	}
	if(!PyIter_Check(step_width_nocheck))
	{
		PyErr_SetString(PyExc_TypeError, "step_width (args[1]) must be iterable");
		return NULL;
	}

	parametrization = PyObject_GetIter(parametrization_nocheck);
	step_width = PyObject_GetIter(step_width_nocheck);


	while((point = PyIter_Next(parametrization)))
	{
		step = PyIter_Next(step_width);
		if(!step)
		{
			PyErr_SetString(PyExc_AttributeError, "step_with contains less items than parametrization");
			goto cleanup_err;
		}

		if(!PyFloat_Check(step))
		{
			PyErr_SetString(PyExc_TypeError, "step_with contains a non float type");
			goto cleanup_err;
		}

		PyObject * tuple = PyTuple_Pack(1, point);
		Py_INCREF(tuple);

		this_result = PyObject_CallObject(func, tuple);
		Py_DECREF(tuple);

		if(!this_result)
		{
			goto cleanup_err;
		}
		if(!PyFloat_Check(this_result))
		{
			PyErr_SetString(PyExc_TypeError, "func returned non-float");
			goto cleanup_err;
		}

		this_result_float = PyFloat_AsDouble(this_result);
		double step_float = PyFloat_AsDouble(step);
		this_rect = step_float * this_result_float;


		Py_DECREF(this_result);

		result += this_rect;
		Py_DECREF(point);
		Py_DECREF(step);

	}



	Py_DECREF(parametrization);
	Py_DECREF(step_width);


	return PyFloat_FromDouble(result);

cleanup_err:
	Py_DECREF(parametrization);
	Py_DECREF(step_width);
	return NULL;
}

