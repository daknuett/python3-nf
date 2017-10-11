#ifndef c_nf_util_iterators_h
#define c_nf_util_iterators_h
#include <Python.h>


typedef struct
{
	PyObject_HEAD
	double start;   // for __iter__ reset purposes.
	double current; // will be returned by __next__()
	double stop;    // if (current >= stop): raise StopIteration
	double step;    // on __next__: current += step
} nf_util_iterators_do_StepIterator;

typedef struct 
{
	PyObject_HEAD
	double width;
} nf_util_iterators_do_WidthIterator;

#ifndef c_nf_util_iterators

static int (* nf_util_iterators_do_StepIterator_c_next)(nf_util_iterators_do_StepIterator * self, double * res);
static void (* nf_util_iterators_do_StepIterator_reset)(nf_util_iterators_do_StepIterator * self);
static PyTypeObject * nf_util_iterators_do_StepIteratorType; 
static int (* nf_util_iterators_do_WidthIterator_c_next)(nf_util_iterators_do_WidthIterator * self, double * res);
static PyTypeObject * nf_util_iterators_do_WidthIteratorType;


static int import_nf_util_iterators_do(void)
{
	PyObject * base = PyImport_ImportModule("nf.util.do.iterators");
	if(!base)
	{
		return -1;
	}

	nf_util_iterators_do_StepIterator_c_next = PyCapsule_Import("nf.util.do.iterators.StepIterator_c_next", 0);
	nf_util_iterators_do_StepIterator_reset = PyCapsule_Import("nf.util.do.iterators.StepIterator_reset", 0);
	nf_util_iterators_do_StepIteratorType = PyCapsule_Import("nf.util.do.iterators.StepIteratorType", 0);
	nf_util_iterators_do_WidthIterator_c_next = PyCapsule_Import("nf.util.do.iterators.WidthIterator_c_next", 0);
	nf_util_iterators_do_WidthIteratorType = PyCapsule_Import("nf.util.do.iterators.WidthIteratorType", 0);

	if(  (nf_util_iterators_do_StepIterator_c_next == NULL) ||
             (nf_util_iterators_do_StepIterator_reset == NULL) ||
             (nf_util_iterators_do_StepIteratorType == NULL) || 
             (nf_util_iterators_do_WidthIterator_c_next == NULL) || 
             (nf_util_iterators_do_WidthIteratorType == NULL) )
	{
		return -1;
	}
	return 0;
}
#endif
#endif
