#ifndef _list_commonincl_h
#define _list_commonincl_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "../rules.h"

#ifdef NAME_MANGLE
#include "list_list.h"
#include "list__list.h"
#else
#include "list.h"
#include "_list.h"
#endif

#endif
