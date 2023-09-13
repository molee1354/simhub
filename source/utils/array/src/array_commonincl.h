#ifndef _array_commonincl_h
#define _array_commonincl_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "../rules.h"

#ifdef NAME_MANGLE
#include "array_array.h"
#include "array__array.h"
#else
#include "array.h"
#include "_array.h"
#endif

#endif
