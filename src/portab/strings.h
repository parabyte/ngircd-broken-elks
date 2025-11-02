/*
 * Minimal <strings.h> shim for the ELKS build: defer to the libc string
 * declarations and avoid pulling in the Watcom host header, which conflicts
 * with ELKS prototypes.
 */
#ifndef NGIRCD_PORTAB_STRINGS_H
#define NGIRCD_PORTAB_STRINGS_H

#include <string.h>

#endif
