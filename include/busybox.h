/* vi: set sw=4 ts=4: */
/*
 * Busybox main internal header file
 *
 * Licensed under the GPL v2 or later, see the file LICENSE in this tarball.
 */
#ifndef	_BB_INTERNAL_H_
#define	_BB_INTERNAL_H_    1

#include "bb_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

extern const char BB_BANNER[];

/* Pull in the utility routines from libbb */
#include "libbb.h"

enum Location {
	_BB_DIR_ROOT = 0,
	_BB_DIR_BIN,
	_BB_DIR_SBIN,
	_BB_DIR_USR_BIN,
	_BB_DIR_USR_SBIN
};

enum SUIDRoot {
	_BB_SUID_NEVER = 0,
	_BB_SUID_MAYBE,
	_BB_SUID_ALWAYS
};

struct BB_applet {
	const char *name;
	int (*main) (int argc, char **argv);
	__extension__ enum Location location:4;
	__extension__ enum SUIDRoot need_suid:4;
};

/* From busybox.c */
extern const struct BB_applet applets[];

/* Automagically pull in all the applet function prototypes and
 * applet usage strings.  These are all of the form:
 *		extern int foo_main(int argc, char **argv);
 *		extern const char foo_usage[];
 * These are all autogenerated from the set of currently defined applets.
 */
#define PROTOTYPES
#include "applets.h"
#undef PROTOTYPES

#ifndef RB_POWER_OFF
/* Stop system and switch power off if possible.  */
#define RB_POWER_OFF   0x4321fedc
#endif

/* Try to pull in PATH_MAX */
#include <limits.h>

/* for PATH_MAX on systems that don't have it in limits.h */
#include <sys/param.h>
#ifndef PATH_MAX
#define  PATH_MAX         256
#endif

#ifdef DMALLOC
#include <dmalloc.h>
#endif

#endif							/* _BB_INTERNAL_H_ */
