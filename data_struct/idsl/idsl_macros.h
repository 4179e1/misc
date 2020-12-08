#ifndef _IDSL_MACROS_H
#define _IDSL_MACROS_H

#ifdef IDSL_MAX
#undef IDSL_MAX
#endif /* IDSL_MAX */

#define IDSL_MAX(x, y) (x > y ? x : y)

#ifdef IDSL_MIN
#undef IDSL_MIN
#endif /* IDSL_MIN */

#define IDSL_MIN(x, y) (x < y ? x : y)

#endif /* _IDSL_MACROS_H */
