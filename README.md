VTMPL - Variadic Template Meta Programming Library
====

This is a template meta programming library which uses the powerful variadic template feature introduced into C++ with the latest official C++ standard, ISO C++11.

It makes uses of variadic templates to ease the definition of various compile-time mechanisms and is powerful yet lightweight.
Some headers can be used on their own; they just depend on some definitions in typedefs.hxx, which you can provide yourself.

Some parts are also written in C++1Y and use the "relaxing constraints on constexpr functions"-feature.
If you know your compiler supports it (but doesn't define the __cplusplus macro greater than 201103), define the VTMPL_RELAX_CONSTEXPR_FUNC yourself to 1.

---

This library is distributed under the Boost Software License (see LICENSE_1_0.txt).

**Special thanks to Volkard Henkel for the Multiply-with-Carry PRNG in random.hxx.**

