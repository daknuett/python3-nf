from nf.integral.base.rect.line import integrate

import numpy as np
import sympy, pytest


def test_integrate_line_rect():
	f = lambda x: x**2

	X = sympy.symbols("X")
	term = X**2


	assert integrate(f, range(10), 10 / 0.001) == pytest.approx(sympy.integrate(term, (X, 0, 10)), rel=1e-2)
		

