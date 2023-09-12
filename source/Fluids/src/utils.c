#include "utils.h"

#include <stdarg.h>

double findMin(double first, double second) {
    return (first < second) ? first : second;
}

double findMax(double first, double second) {
    return (first > second) ? first : second;
}
