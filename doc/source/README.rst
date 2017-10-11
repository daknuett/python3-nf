nf -- Numeric Functions
***********************

A library for numerical function handling.

.. image:: https://travis-ci.org/daknuett/python3-nf.svg?branch=master
   :target: https://travis-ci.org/daknuett/python3-nf

.. contents::


Links
=====

Full Documentation hosted by GitHub
	https://daknuett.github.io/python3-nf/

The GitHub Repository
	https://github.com/daknuett/python3-nf

Goal
====

The goal of this project is to create a universal toolbox
for numerically handling functions and data.

This toolbox should have a pythonic interface, without
restricting access to the backend and a good performance for
all algorithms.

Design
======

To fulfill the prerequisites named under `Goal`_, the
library contains two parts: 

A ``C`` backend
	the backend is written in ``C`` using the python
	``C-API``. The implemented algorithms are therefore
	fast and can be accessed using the python import
	mechanism.

A ``python3`` frontend
	the frontend provides a pythonic straight forward
	interface that should be usable by beginners.

All sub-packages contain a backend and a frontend, the
backend is always in the sub-package or module ``do``.





