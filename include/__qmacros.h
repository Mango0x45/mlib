#ifndef MLIB___QMACROS_H
#define MLIB___QMACROS_H

/* Macros for qualifier-preserving functions.  These are wrappers around some
   functions declared above which will return a const-qualified pointer if the
   input string is const-qualified, and a non-const-qualified pointer otherwise.

   The macros are taken from the N3020 proposal for C23. */

/* clang-format off */
#define __MLIB_PTR_IS_CONST(P) \
	_Generic(1 ? (P) : (void *)(P), \
	         const void *: 1, \
	         default: 0)
#define __MLIB_STATIC_IF(P, T, E) \
	_Generic(&(char[!!(P) + 1]){0}, \
	         char(*)[2]: T, \
	         char(*)[1]: E)
#define __MLIB_Q_PTR(T, F, S, ...) \
	__MLIB_STATIC_IF(__MLIB_PTR_IS_CONST((S)), \
	                (const T *)(F)(__VA_ARGS__), \
	                      (T *)(F)(__VA_ARGS__))
/* clang-format on */

#endif /* !MLIB___QMACROS_H */
