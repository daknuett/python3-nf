from distutils.core import setup, Extension


base_do_line = Extension("nf.integral.base.do.line",
		sources = ["c/integral/base/line.c"])
fast_do_line = Extension("nf.integral.fast.do.line",
		sources = ["c/integral/fast/line_float.c"])
util_do_iterators = Extension("nf.util.do.iterators",
		sources = ["c/util/iterators.c"])

setup(name = "nf",
	version = "0.0.1",
	description = "A fast numerical integrator library",
	ext_modules = [base_do_line, fast_do_line, util_do_iterators],
	packages = [
		"nf",
		"nf.integral", 
		"nf.integral.base",
		"nf.integral.base.do",
		"nf.integral.base.rect"
	],
	package_dir = {"nf": "py/nf"},
	url="https://github.com/daknuett/python3-nf",
	author = "Daniel Knüttel",
	author_email = "daknuett@gmail.com")
