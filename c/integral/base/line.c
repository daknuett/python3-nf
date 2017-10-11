#include <Python.h>

static PyObject * line_integrate_numbers_rect(PyObject * self, PyObject * args);


static PyMethodDef methods[] = {
	{
		"integrate_numbers_rect", 
		line_integrate_numbers_rect, 
		METH_VARARGS, 
		"Integrate a function returning numbers using rects."},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef linemodule = {
	PyModuleDef_HEAD_INIT,
	"nf.base.do.line",
	"A C backend module used to integrate functions parametrized by lines",
	-1,
	methods
};
	


PyMODINIT_FUNC PyInit_line(void)
{
	return PyModule_Create(&linemodule);
}

static PyObject * line_integrate_numbers_rect(PyObject * self, PyObject * args)
{
	PyObject * parametrization;
	PyObject * step_width;
	PyObject * parametrization_nocheck;
	PyObject * step_width_nocheck;
	PyObject * func;
	PyObject * zero;

	PyObject * point;
	PyObject * step;
	PyObject * this_result;
	PyObject * this_rect;
	PyObject * old_result;
	PyObject * result;


	if(!PyArg_ParseTuple(args, "OOOO", &parametrization_nocheck, &step_width_nocheck, &func, &zero))
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
	if(!PyNumber_Check(zero))
	{
		PyErr_SetString(PyExc_TypeError, "zero (args[3]) must be number");
		return NULL;
	}

	parametrization = PyObject_GetIter(parametrization_nocheck);
	step_width = PyObject_GetIter(step_width_nocheck);

	Py_INCREF(zero);

	result = zero;

	while((point = PyIter_Next(parametrization)))
	{
		step = PyIter_Next(step_width);
		if(!step)
		{
			PyErr_SetString(PyExc_AttributeError, "step_with contains less items than parametrization");
			goto cleanup_err;
		}

		if(!PyNumber_Check(step))
		{
			PyErr_SetString(PyExc_TypeError, "step_with contains a non numerical type");
			goto cleanup_err;
		}

		PyObject * tuple = PyTuple_Pack(1, point);

		this_result = PyObject_CallObject(func, tuple);
		Py_DECREF(tuple);
		if(!this_result)
		{
			goto cleanup_err;
		}

		old_result = result;
		this_rect = PyNumber_Multiply(this_result, step);

		Py_DECREF(this_result);

		result = PyNumber_Add(old_result, this_rect);
		Py_DECREF(old_result);
		Py_DECREF(this_rect);
		Py_DECREF(point);
		Py_DECREF(step);

	}



	Py_DECREF(parametrization);
	Py_DECREF(step_width);


	return result;

cleanup_err:
	Py_DECREF(parametrization);
	Py_DECREF(step_width);
	return NULL;
}
