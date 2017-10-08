from distutils.core import setup, Extension


base_do_line = Extension("nf.integral.base.do.line",
		sources = ["c/integral/base/line.c"])

setup(name = "nf",
	version = "0.0.1",
	description = "A fast numerical integrator library",
	ext_modules = [base_do_line],
	package_dir = {"": "py"})
