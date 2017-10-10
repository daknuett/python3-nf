#include <Python.h>


typedef struct
{
	PyObject_HEAD
	double start;   // for __iter__ reset purposes.
	double current; // will be returned by __next__()
	double stop;    // if (current >= stop): raise StopIteration
	double step;    // on __next__: current += step
} nf_util_iterators_do_StepIterator;


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

static PyObject * nf_util_iterators_do_StepIterator_next(nf_util_iterators_do_StepIterator * self)
{
	double res;
	int stop = nf_util_iterators_do_StepIterator_c_next(self, &res);
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
static PyObject * nf_util_iterators_do_StepIterator_iter(nf_util_iterators_do_StepIterator * self)
{
	nf_util_iterators_do_StepIterator_reset(self);
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

typedef struct 
{
	PyObject_HEAD
	double width;
} nf_util_iterators_do_WidthIterator;


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

static PyObject * nf_util_iterators_do_WidthIterator_next(nf_util_iterators_do_WidthIterator * self)
{
	double res;
	nf_util_iterators_do_WidthIterator_c_next(self, &res);
	return PyFloat_FromDouble(res);
}

static PyObject * nf_util_iterators_do_WidthIterator_iter(nf_util_iterators_do_WidthIterator * self)
{
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

	Py_INCREF(&nf_util_iterators_do_StepIteratorType);
	Py_INCREF(&nf_util_iterators_do_WidthIteratorType);
	PyModule_AddObject(module, "StepIterator", (PyObject *)&nf_util_iterators_do_StepIteratorType);
	PyModule_AddObject(module, "WidthIterator", (PyObject *)&nf_util_iterators_do_WidthIteratorType);
	return module;
}