from nf.integral.base.rect.line import integrate_steps, integrate_width

import numpy as np
import sympy, pytest


def test_integrate_line_rect():
	f = lambda x: x**2

	X = sympy.symbols("X")
	term = X**2


	assert integrate_steps(f, range(10), 10000) == pytest.approx(sympy.integrate(term, (X, 0, 10)), rel=1e-2)
	assert integrate_width(f, range(10), 1e-4) == pytest.approx(sympy.integrate(term, (X, 0, 10)), rel=1e-2)
		

