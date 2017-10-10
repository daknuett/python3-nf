from ..do.line import integrate_numbers_rect

from ...util.do.iterators import WidthIterator, StepIterator


def integrate_steps(f, rnge, steps):
	"""
	Approximate the integral of ``f``
	in the range ``rnge`` using a decomposition
	with ``steps`` subintervalls. 

	``f`` must return ``float`` or ``int``.
	``rnge`` must be ``range`` or a ``tuple`` containing
	``start`` and ``stop``

	Algorithm: *Riemann upper sum*
	"""

	if(isinstance(rnge, range)):
		start = rnge.start
		stop = rnge.stop
	elif(isinstance(rnge, list, tuple)):
		if(len(rnge) != 2):
			raise ValueError("rnge must have length 2: (start, stop)")
		start, stop = rnge
	else:
		raise TypeError("rnge must be range or list or tuple")


	width = (stop - start) / steps
	return integrate_numbers_rect(StepIterator(start, stop, width), WidthIterator(width), f, 0)

def integrate_width(f, rnge, width):
	"""
	Approximate the integral of ``f``
	in the range ``rnge`` using a decomposition
	with subintervalls with ``width`` length. 

	``f`` must return ``float`` or ``int``.
	``rnge`` must be ``range`` or a ``tuple`` containing
	``start`` and ``stop``

	Algorithm: *Riemann upper sum*
	"""

	if(isinstance(rnge, range)):
		start = rnge.start
		stop = rnge.stop
	elif(isinstance(rnge, list, tuple)):
		if(len(rnge) != 2):
			raise ValueError("rnge must have length 2: (start, stop)")
		start, stop = rnge
	else:
		raise TypeError("rnge must be range or list or tuple")


	return integrate_numbers_rect(StepIterator(start, stop, width), WidthIterator(width), f, 0)

