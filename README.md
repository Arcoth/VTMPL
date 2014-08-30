VTMPL - Variadic Template Meta Programming Library
---

VTMPL is a lightweight template meta programming (TMP) library which uses the powerful variadic template feature introduced into C++ with the 2011 ISO C++ standard.


It makes use of parameter packs to ease the definition of various compile-time mechanisms.
Using the random.hxx-header, you can even create pseudo random numbers at compile time, seeding it with the current time (provided by the __TIME__ macro).
Some headers can be used on their own; they just depend on definitions in typedefs.hxx, which you can provide yourself (or copy&paste them inside the header).

Parts are also written in C++14 (the latest official ISO standard) and use the
"relaxing constraints on constexpr functions"- and "string literal operator templates"-features.
If you know your compiler supports them (but doesn't define the __cplusplus macro greater than 201103, which indicates C++14-support),
define the macro VTMPL_RELAX_CONSTEXPR_FUNC (or STRING_LITERAL_OPERATOR_TEMPLATES, respectively) as 1.

---

This library is distributed under the Boost Software License (see LICENSE_1_0.txt).

**Special thanks to**
- Volkard Henkel (volkard @ http://www.c-plusplus.de/) for the Multiply-with-Carry PRNG in random.hxx.
- camper @ http://www.c-plusplus.de/ for the binary recursion definition of make_index_list.
