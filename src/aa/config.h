/* src/config.h.  Generated from config.h.in by configure.  */
/* src/config.h.in.  Generated from configure.in by autoheader.  */
#define CURSES_DRIVER 1
/* #undef X11_DRIVER */
#define SLANG_DRIVER 1
/* #undef LINUX_DRIVER */
#define CURSES_KBDDRIVER 1
/* #undef X11_KBDDRIVER */
#define SLANG_KBDDRIVER 1
/* #undef LINUX_KBDDRIVER */
#define CURSES_MOUSEDRIVER 1
/* #undef GPM_MOUSEDRIVER */
/* #undef X11_MOUSEDRIVER */
#define PACKAGE "aalib"
#define VERSION "1.4.0"
/* #undef SUNOS_CURSES */
/* #undef NO_COLOR_SUPPORT */
/* #undef USE_CURSES */
#define USE_NCURSES 1
/* #undef USE_SYSV_CURSES */

#ifdef _WIN32
#undef CURSES_DRIVER
#undef SLANG_DRIVER
#undef SLANG_KBDDRIVER
#undef CURSES_KBDDRIVER
#undef CURSES_MOUSEDRIVER
#undef USE_NCURSES
#endif

/* Define to 1 if you have the 'curs_set' function. */
#define HAVE_CURS_SET 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the 'curses' library (-lcurses). */
/* #undef HAVE_LIBCURSES */

/* Define to 1 if you have the 'm' library (-lm). */
#define HAVE_LIBM 1

/* Define to 1 if you have the 'ncurses' library (-lncurses). */
#define HAVE_LIBNCURSES 1

/* Define to 1 if you have the 'slang' library (-lslang). */
#define HAVE_LIBSLANG 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the 'mousemask' function. */
#define HAVE_MOUSEMASK 1

/* Define to 1 if you have the 'redrawwin' function. */
#define HAVE_REDRAWWIN 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the 'strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the <strings.h> header file. */
/* #define HAVE_STRINGS_H 1 */

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if 'st_rdev' is a member of 'struct stat'. */
#define HAVE_STRUCT_STAT_ST_RDEV 1

/* Define to 1 if your 'struct stat' has 'st_rdev'. Deprecated, use
   'HAVE_STRUCT_STAT_ST_RDEV' instead. */
#define HAVE_ST_RDEV 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the 'termattrs' function. */
#define HAVE_TERMATTRS 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the 'wredrawln' function. */
#define HAVE_WREDRAWLN 1

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "aalib"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define as the return type of signal handlers ('int' or 'void'). */
#define RETSIGTYPE void

/* Define to 1 if all of the C89 standard headers exist (not just the ones
   required in a freestanding environment). This macro is provided for
   backward compatibility; new code need not use it. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. This
   macro is obsolete. */
#define TIME_WITH_SYS_TIME 1

/* Version number of package */
#define VERSION "1.4.0"

/* Define to 1 if the X Window System is missing or not being used. */
/* #undef X_DISPLAY_MISSING */
