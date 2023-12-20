#ifndef simhub_collisions_commonincl_h
#define simhub_collisions_commonincl_h

#include "../rules.h"

#ifdef NAME_MANGLE

#include "Particles_collisions.h"
#include "Particles_hashtable.h"
#include "Particles_vector.h"
#include "helper_helper.h"
#include "array_array.h"

#else

#include "particles.h"
#include "hashtable.h"
#include "vector.h"
#include "../../utils/helper/src/helper.h"
#include "../../utils/array/src/array.h"

#endif

#endif
