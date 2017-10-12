from nf.util.do.iterators import ConvergenceIterator, WidthIterator, StepIterator
import pytest

def test_convergence_iterator():
	lim = 3
	prec = 1e-3
	last = None
	for i in ConvergenceIterator(0, lim, prec):
		last = i
	
	assert last == pytest.approx(lim, abs = prec)

