#include <stdio.h>
#include <stdlib.h>

#include "array.h"

#ifndef _test_h
#define _test_h

int testSuccess = 0;
int testFail = 0;

#define TYPE int

#define TEST_FAIL(reason)      printf("\t=> [  FAIL  ] --> %s\n\n", reason); \
                               testFail++

#define TEST_SUCCESS()         printf("\t=> [  PASS  ]\n\n"); \
                               testSuccess++



#endif
