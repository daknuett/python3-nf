import nf.integral.fast.do.line as line
from nf.util.do.iterators import WidthIterator, StepIterator
import sympy, pytest

def test_integrate_line_rect():
	f = lambda x: x**2

	X = sympy.symbols("X")
	term = X**2


	r = StepIterator(0, 10.0, 0.001)

	assert line.integrate_float_rect(r, WidthIterator(0.001), f) == pytest.approx(sympy.integrate(term, (X, 0, 10)), rel=1e-2)
		
