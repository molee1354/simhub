#include "utils.h"

#include <stdarg.h>

double findMin(double first, ...) {
    double min = DBL_MAX;
    double num;
    va_list args;
    va_start(args, first);

    while ((num = va_arg(args, double)) != ENDMIN) {
        if (num < min) {
            min = num;
        }
    }

    va_end(args);
    return min;
}

double findMax(double first, ...) {
    double max = DBL_MIN;
    double num;
    va_list args;
    va_start(args, first);

    while ((num = va_arg(args, double)) != ENDMAX) {
        if (num > max) {
            max = num;
        }
    }

    va_end(args);
    return max;
}
