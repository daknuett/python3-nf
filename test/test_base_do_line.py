import nf.base.do.line as line
import numpy as np
import sympy, pytest


def test_integrate_line_rect():
	f = lambda x: x**2

	X = sympy.symbols("X")
	term = X**2


	r = np.arange(0, 10.0, 0.001)
	class StepIterator(object):
		def __init__(self, step):
			self.step = step
		def __iter__(self):
			return self
		def __next__(self):
			return self.step

	assert line.integrate_numbers_rect(iter(r), StepIterator(0.001), f, 0) == pytest.approx(sympy.integrate(term, (X, 0, 10)), rel=1e-2)
		
