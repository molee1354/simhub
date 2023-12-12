#ifdef NAME_MANGLE
#include "array_array.h"
#else
#include "array.h"
#endif

int main(int argc, char** argv) {
    Array* out = initArray();
    free(out);
    return 0;
}
