Profiling example for ``/fastcap``
==================================

While developing for Windows Mobile/Windows CE, ``/fascap`` causes the
compiler to insert calls to profiling hooks around each function call.

The goal of this project is to create optimized profiling hooks that cause as
little overhead for profiling as possible. The output is written to a
JSON-formatted profile data file for easy parsing from Python (or any other
scripting language) for statistics generation.

A simple start
--------------

The first tag, ``simple-start`` is the baseline.

Profiling profiling overhead (no pun intended :)) gives the following results::

 make
 ./test
 gprof ./test
 
 FIXME: unable to profile malloc overhead without -lc_p,
 but stuck with https://bugs.launchpad.net/ubuntu/+source/glibc/+bug/667470

Avoiding memory allocation overhead
-----------------------------------

* Use a static vector that does not grow

* Use a typed vector (create it with a macro) that takes arguments by copy

Statistics output
-----------------

Create a Python script that parses the JSON file and creates call statistics
(call count, time for self, cumulative time for self with children).

Visual output
-------------

Provide a parser in Python for http://code.google.com/p/jrfonseca/wiki/Gprof2Dot
