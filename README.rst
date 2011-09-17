Profiling example for ``/fastcap``
==================================

While developing for Windows Mobile/Windows CE, ``/fascap`` causes the compiler
to insert calls to profiling hooks around each function call. There are no
other generally available tools for profiling in these environments, so a
homebrew solution for profiling is necessary.

The goal of this project is to create optimized profiling hooks that cause as
little overhead for profiling as possible. At exit, the profiling output is
written to a JSON-formatted profile data file for easy parsing from Python (or
any other scripting language) for statistics generation.

Ironically, it's easier to test profiling overhead in Linux, so this project
has been only tested in Ubuntu.

A simple start
--------------

The first tag, ``simple-start`` is the baseline.

Profiling profiling overhead (no pun intended :)) gives the following results::

 $ make
 CPUPROFILE=profile.out ./test
 Writing stats to file at exit...
 PROFILE: interrupts/evictions/bytes = 725/24/18928
 google-pprof --text ./test profile.out
 Total: 725 samples
     394  54.3%  54.3%      394  54.3% 0x00007fff68fff851
      75  10.3%  64.7%      215  29.7% _IO_vfprintf_internal
      57   7.9%  72.6%       57   7.9% _itoa_word
      55   7.6%  80.1%       85  11.7% _IO_new_file_xsputn
      28   3.9%  84.0%       28   3.9% __write_nocancel
      19   2.6%  86.6%       19   2.6% _int_malloc
      11   1.5%  88.1%       11   1.5% __strchrnul
      10   1.4%  89.5%      265  36.6% vector_foreach
       8   1.1%  90.6%       29   4.0% *__GI___libc_malloc
       8   1.1%  91.7%        8   1.1% vector_push_back
       7   1.0%  92.7%       12   1.7% *__GI___libc_free
       5   0.7%  93.4%        5   0.7% _int_free
       5   0.7%  94.1%      134  18.5% print_start_stats_callback
       5   0.7%  94.8%        5   0.7% vector_get

Use ``google-pprof --gv ./test profile.out`` for visual call graph.  See
http://google-perftools.googlecode.com/svn/trunk/doc/cpuprofile.html for
instructions how to interpret the results.

Let's check with simple ``time`` as well (best of 4)::

 $ time ./test 
 Writing stats to file at exit...
 
 real	0m8.542s
 user	0m6.590s
 sys	0m0.530s

Avoiding memory allocation overhead
-----------------------------------

As you can see, memory allocation-related code has notable overhead (see
``*alloc`` above and consider that all the I/O-related calls that dominate the
list happen after execution has finished). To alleviate this:

* Use a static vector that does not grow

* Use a typed vector (create it with a macro) that takes arguments by copy and
  don't malloc them in ``start_profile_hook()``.

Statistics output
-----------------

Create a Python script that parses the JSON file and creates call statistics
(call count, time for self, cumulative time for self with children).

Visual output
-------------

Provide a parser in Python for http://code.google.com/p/jrfonseca/wiki/Gprof2Dot
