from ..do.line import integrate_numbers_rect
from numpy import arange

class StepIterator(object):
	def __init__(self, width):
		self.width = width
	def __iter__(self):
		return self
	def __next__(self):
		return self.width


def integrate(f, rnge, steps):
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
	return integrate_numbers_rect(iter(arange(start, stop, width)), StepIterator(width), 0)

