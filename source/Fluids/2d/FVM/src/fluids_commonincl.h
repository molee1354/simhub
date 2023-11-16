#ifndef simhub_fvm_fluids_commonincl_h
#define simhub_fvm_fluids_commonincl_h

#include "../rules.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef NAME_MANGLE

#include "FVM_fluid.h"
#include "FVM_deps.h"
#include "helper_helper.h"
#include "c_array_c_array.h"

#else

#include "fluid.h"
#include "deps.h"
#include "../../../../utils/helper/src/helper.h"
#include "../../../../utils/c_array/src/c_array.h"

#endif

#endif
