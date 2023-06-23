#include <stdlib.h>
#include <stdarg.h>
#include "matrix.h"
#include "guard.h"

int freeAll_M( Matrix* first, ... ) {
    va_list argList;
    va_start(argList, first);

    Matrix* targ = first;
    while (targ != NULL)
    {
        freeObj(targ);
        targ = va_arg(argList, Matrix*);
    }

    va_end(argList);
    return 0;
}
int freeAll_V( Vector* first, ... ) {
    va_list argList;
    va_start(argList, first);

    Vector* targ = first;
    while (targ != NULL)
    {
        freeObj(targ);
        targ = va_arg(argList, Vector*);
    }

    va_end(argList);
    return 0;
}
