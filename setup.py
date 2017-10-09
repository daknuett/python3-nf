from distutils.core import setup, Extension


base_do_line = Extension("nf.integral.base.do.line",
		sources = ["c/integral/base/line.c"])

setup(name = "nf",
	version = "0.0.1",
	description = "A fast numerical integrator library",
	ext_modules = [base_do_line],
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
