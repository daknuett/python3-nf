#include <Python.h>
#include <math.h>
#include "../../util/iterators.h"

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
	if(import_nf_util_iterators_do())
	{
		return 0;
	}
	return PyModule_Create(&linemodule);
}

static int _do_line_integrate_float_rect_default(double * result, 
	PyObject * parametrization,
	PyObject * step_width,
	PyObject * func
	)

{
	PyObject * point;
	PyObject * step;
	PyObject * this_result;
	double this_result_float = 0;
	double this_rect = 0;
	while((point = PyIter_Next(parametrization)))
	{
		step = PyIter_Next(step_width);
		if(!step)
		{
			PyErr_SetString(PyExc_AttributeError, "step_with contains less items than parametrization");
			return -1;
		}

		if(!PyFloat_Check(step))
		{
			PyErr_SetString(PyExc_TypeError, "step_with contains a non float type");
			return -1;
		}

		PyObject * tuple = PyTuple_Pack(1, point);
		Py_INCREF(tuple);

		this_result = PyObject_CallObject(func, tuple);
		Py_DECREF(tuple);

		if(!this_result)
		{
			return -1;
		}
		if(!PyFloat_Check(this_result))
		{
			PyErr_SetString(PyExc_TypeError, "func returned non-float");
			return -1;
		}

		this_result_float = PyFloat_AsDouble(this_result);
		double step_float = PyFloat_AsDouble(step);
		this_rect = step_float * this_result_float;


		Py_DECREF(this_result);

		*result += this_rect;
		Py_DECREF(point);
		Py_DECREF(step);

	}
	return 0;
}

/*
 * This is actually a pretty nice implementation:
 * ``nf.util.do.iterators`` provide a interface that bypasses
 * the python interface. Using this interface one is able
 * to write even faster code, as he omitts the PyObject_GetIter,
 * PyIter_Next, and PyFloat_AsDouble.
 * */
static int _do_line_integrate_float_rect_builtins(double * result, 
	PyObject * parametrization,
	nf_util_iterators_do_WidthIterator * step_width,
	PyObject * func
	)

{
	double step, this_result_float;
	PyObject * point;
	PyObject * this_result;

	while((point = PyIter_Next(parametrization)))
	{
		// Returns always 0. No need to check this.
		nf_util_iterators_do_WidthIterator_c_next(step_width, &step);

		PyObject * tuple = PyTuple_Pack(1, point);
		Py_INCREF(tuple);

		this_result = PyObject_CallObject(func, tuple);
		Py_DECREF(tuple);

		if(!this_result)
		{
			return -1;
		}
		if(!PyFloat_Check(this_result))
		{
			PyErr_SetString(PyExc_TypeError, "func returned non-float");
			return -1;
		}

		this_result_float = PyFloat_AsDouble(this_result);
		*result += this_result_float * step;
		Py_DECREF(point);
	}
	return 0;
}

static PyObject * line_integrate_float_rect(PyObject * self, PyObject * args)
{

	PyObject * parametrization_nocheck;
	PyObject * step_width_nocheck;
	PyObject * parametrization;
	PyObject * step_width;
	PyObject * func;

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



	int ok;

	parametrization = PyObject_GetIter(parametrization_nocheck);
	if(PyObject_IsInstance(parametrization_nocheck, (PyObject *) nf_util_iterators_do_StepIteratorType) &&
		PyObject_IsInstance(step_width_nocheck, (PyObject *) nf_util_iterators_do_WidthIteratorType))
	{
		ok = _do_line_integrate_float_rect_builtins(&result, 
			parametrization, 
			(nf_util_iterators_do_WidthIterator *) step_width_nocheck, func);
	}
	else
	{

		step_width = PyObject_GetIter(step_width_nocheck);
		ok = _do_line_integrate_float_rect_default(&result, parametrization, step_width, func);
		Py_DECREF(step_width);
	}
	Py_DECREF(parametrization);
	if(!ok)
	{
		return PyFloat_FromDouble(result);
	}

	return NULL;
}

