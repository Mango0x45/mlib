#ifndef MLIB__ATTRS_H
#define MLIB__ATTRS_H

#define _mlib_pure         __nodiscard__, __unsequenced__
#define _mlib_inline       gnu::__always_inline__, clang::__always_inline__
#define _mlib_printf(n, m) gnu::__format__(printf, n, m)

#endif /* !MLIB__ATTRS_H */
