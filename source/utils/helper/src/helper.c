#include <stdarg.h>
#include "helper_commonincl.h"

double findMin(double first, double second) {
    return (first < second) ? first : second;
}

double findMax(double first, double second) {
    return (first > second) ? first : second;
}

double clamp(double x, double min, double max) {
    if (x<min) return min;
    else if (x>max) return max;
    else return x;
}
