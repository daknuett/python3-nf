#define c_nf_util_iterators
#include "iterators.h"



static PyObject * nf_util_iterators_do_StepIterator_new(PyTypeObject * type, PyObject * args, PyObject * kwds)
{
	nf_util_iterators_do_StepIterator * self = (nf_util_iterators_do_StepIterator *) type->tp_alloc(type, 0);
	return (PyObject *) self;
}

static int nf_util_iterators_do_StepIterator_init(nf_util_iterators_do_StepIterator * self, PyObject * args, PyObject * kwds)
{
	
	static char * kw_names[] = {"start", "stop", "step", NULL};

	if(!PyArg_ParseTupleAndKeywords(args, kwds, "ddd", kw_names, &(self->start), &(self->stop), &(self->step)))
	{
		return -1;
	}
	return 0;
}

static int nf_util_iterators_do_StepIterator_c_next(nf_util_iterators_do_StepIterator * self, double * res)
{
	*res = self->current;
	if(self->current > self->stop)
	{
		return 1; // stop iteration
	}
	self->current += self->step;

	return 0;
}

static PyObject * nf_util_iterators_do_StepIterator_next(PyObject * self)
{

	double res;
	int stop = nf_util_iterators_do_StepIterator_c_next((nf_util_iterators_do_StepIterator *) self, &res);
	if(stop)
	{
		PyErr_SetString(PyExc_StopIteration, "");
		return NULL;
	}

	return PyFloat_FromDouble(res);
}

static void nf_util_iterators_do_StepIterator_reset(nf_util_iterators_do_StepIterator * self)
{
	self->current = self->start;
}
static PyObject * nf_util_iterators_do_StepIterator_iter(PyObject * self)
{
	nf_util_iterators_do_StepIterator_reset((nf_util_iterators_do_StepIterator *) self);
	Py_INCREF((PyObject *) self);
	return (PyObject *) self;
}




static PyTypeObject nf_util_iterators_do_StepIteratorType = 
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"nf.util.do.StepIterator",
	sizeof(nf_util_iterators_do_StepIterator),
	0,                 /* tp_itemsize */
	0,                 /* tp_dealloc */
	0,                 /* tp_print */
	0,                 /* tp_getattr */
	0,                 /* tp_setattr */
	0,                 /* tp_reserved */
	0,                 /* tp_repr */
	0,                 /* tp_as_number */
	0,                 /* tp_as_sequence */
	0,                 /* tp_as_mapping */
	0,                 /* tp_hash  */
	0,                 /* tp_call */
	0,                 /* tp_str */
	0,                 /* tp_getattro */
	0,                 /* tp_setattro */
	0,                 /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT ,/* tp_flags */
	"A StepIterator returns always the next step in a chain defined by"
	"\nwidth, start and stop. This class is optimized to be used in"
	"\n``nf`` and can be accessed from the C backend without using the"
	"\n(slow) python __next__.",   /* tp_doc */	
	0,
	0,
	0,
	0,
	nf_util_iterators_do_StepIterator_iter,
	nf_util_iterators_do_StepIterator_next,
	0, // methods
	0, // members
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc) nf_util_iterators_do_StepIterator_init,
	0,
	nf_util_iterators_do_StepIterator_new,
};


static int nf_util_iterators_do_WidthIterator_init(nf_util_iterators_do_WidthIterator * self, PyObject * args, PyObject * kwds)
{
	static char * kw_names[] = {"width", NULL}; 
	if(!PyArg_ParseTupleAndKeywords(args, kwds, "d", kw_names, &(self->width)))
	{
		return -1;
	}
	return 0;
}

static PyObject * nf_util_iterators_do_WidthIterator_new(PyTypeObject * type, PyObject * args, PyObject * kwds)
{
	nf_util_iterators_do_WidthIterator * self = (nf_util_iterators_do_WidthIterator *) type->tp_alloc(type, 0);
	return (PyObject *) self;
}

static int nf_util_iterators_do_WidthIterator_c_next(nf_util_iterators_do_WidthIterator * self, double * res)
{
	*res = self->width;
	return 0;
}

static PyObject * nf_util_iterators_do_WidthIterator_next(PyObject * self)
{
	double res;
	nf_util_iterators_do_WidthIterator_c_next((nf_util_iterators_do_WidthIterator *) self, &res);
	return PyFloat_FromDouble(res);
}

static PyObject * nf_util_iterators_do_WidthIterator_iter(PyObject * self)
{
	Py_INCREF((PyObject *) self);
	return self;
}

static PyTypeObject nf_util_iterators_do_WidthIteratorType = 
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"nf.util.do.WidthIterator",
	sizeof(nf_util_iterators_do_WidthIterator),
	0,                 /* tp_itemsize */
	0,                 /* tp_dealloc */
	0,                 /* tp_print */
	0,                 /* tp_getattr */
	0,                 /* tp_setattr */
	0,                 /* tp_reserved */
	0,                 /* tp_repr */
	0,                 /* tp_as_number */
	0,                 /* tp_as_sequence */
	0,                 /* tp_as_mapping */
	0,                 /* tp_hash  */
	0,                 /* tp_call */
	0,                 /* tp_str */
	0,                 /* tp_getattro */
	0,                 /* tp_setattro */
	0,                 /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT ,/* tp_flags */
	"A WidthIterator returns always the same value (width)."
	"\nThis class is optimized to be used in"
	"\n``nf`` and can be accessed from the C backend without using the"
	"\n(slow) python __next__.",   /* tp_doc */	

	0,
	0,
	0,
	0,
	nf_util_iterators_do_WidthIterator_iter,
	nf_util_iterators_do_WidthIterator_next,
	0, // methods
	0, // members
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc) nf_util_iterators_do_WidthIterator_init,
	0,
	nf_util_iterators_do_WidthIterator_new,
};


static PyModuleDef nf_util_iterators_do_iteratorsmodule = 
{
	PyModuleDef_HEAD_INIT,
	"nf.util.do.iterators",
	"Module containing fast iterators. Those iterators are\n"
	"optimized for ``nf`` and can be used by the backend without\n"
	"accessing the python methods, which increases the speed dramatically.\n",
	-1,
	NULL,NULL,NULL,NULL,NULL
};

PyMODINIT_FUNC PyInit_iterators(void)
{
	PyObject * module;
	if(PyType_Ready(&nf_util_iterators_do_StepIteratorType) < 0)
	{
		return NULL;
	}
	if(PyType_Ready(&nf_util_iterators_do_WidthIteratorType) < 0)
	{
		return NULL;
	}
	module = PyModule_Create(&nf_util_iterators_do_iteratorsmodule);
	if(!module)
	{
		return NULL;
	}

	PyObject * nf_util_iterators_do_StepIterator_c_next_capsule;
	PyObject * nf_util_iterators_do_StepIterator_reset_capsule;
	PyObject * nf_util_iterators_do_StepIteratorType_capsule;
	PyObject * nf_util_iterators_do_WidthIterator_c_next_capsule;
	PyObject * nf_util_iterators_do_WidthIteratorType_capsule;


	nf_util_iterators_do_StepIterator_c_next_capsule = PyCapsule_New(
			nf_util_iterators_do_StepIterator_c_next, 
			"nf.util.do.iterators.StepIterator_c_next", 
			NULL);
	nf_util_iterators_do_StepIterator_reset_capsule = PyCapsule_New(
			nf_util_iterators_do_StepIterator_reset, 
			"nf.util.do.iterators.StepIterator_reset", 
			NULL);
	nf_util_iterators_do_StepIteratorType_capsule = PyCapsule_New(
			&nf_util_iterators_do_StepIteratorType, 
			"nf.util.do.iterators.StepIteratorType", 
			NULL);
	nf_util_iterators_do_WidthIterator_c_next_capsule = PyCapsule_New(
			nf_util_iterators_do_WidthIterator_c_next,
			"nf.util.do.iterators.WidthIterator_c_next", 
			NULL);
	nf_util_iterators_do_WidthIteratorType_capsule = PyCapsule_New(
			&nf_util_iterators_do_WidthIteratorType,
			"nf.util.do.iterators.WidthIteratorType", 
			NULL);


	if(  (nf_util_iterators_do_StepIterator_c_next_capsule == NULL) ||
             (nf_util_iterators_do_StepIterator_reset_capsule == NULL) ||
             (nf_util_iterators_do_StepIteratorType_capsule == NULL) || 
             (nf_util_iterators_do_WidthIterator_c_next_capsule == NULL) || 
             (nf_util_iterators_do_WidthIteratorType_capsule == NULL) )
	{
		return NULL;
	}

	Py_INCREF(&nf_util_iterators_do_StepIteratorType);
	Py_INCREF(&nf_util_iterators_do_WidthIteratorType);
	PyModule_AddObject(module, "StepIterator", (PyObject *)&nf_util_iterators_do_StepIteratorType);
	PyModule_AddObject(module, "WidthIterator", (PyObject *)&nf_util_iterators_do_WidthIteratorType);
	Py_INCREF(nf_util_iterators_do_StepIterator_c_next_capsule);
	Py_INCREF(nf_util_iterators_do_StepIterator_reset_capsule);
	Py_INCREF(nf_util_iterators_do_StepIteratorType_capsule);
	Py_INCREF(nf_util_iterators_do_WidthIterator_c_next_capsule);
	Py_INCREF(nf_util_iterators_do_WidthIteratorType_capsule);
	PyModule_AddObject(module, "StepIterator_c_next", nf_util_iterators_do_StepIterator_c_next_capsule);
	PyModule_AddObject(module, "StepIterator_reset", nf_util_iterators_do_StepIterator_reset_capsule);
	PyModule_AddObject(module, "StepIteratorType", nf_util_iterators_do_StepIteratorType_capsule);
	PyModule_AddObject(module, "WidthIterator_c_next", nf_util_iterators_do_WidthIterator_c_next_capsule);
	PyModule_AddObject(module, "WidthIteratorType", nf_util_iterators_do_WidthIteratorType_capsule);


	return module;
}
