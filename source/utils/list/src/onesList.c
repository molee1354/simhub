#include "list_commonincl.h"

static List* onesList_i( int size ) {
    List* list = makeList(sizeof(int));
    if (list == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( list, 1 ); }
    return list;
}
static List* onesList_d( int size ) {
    List* list = makeList(sizeof(double));
    if (list == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( list, 1. ); }
    return list;
}
static List* onesList_c( int size ) {
    List* list = makeList(sizeof(char));
    if (list == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( list, '1' ); }
    return list;
}

List* onesList( size_t dtype, int size ) {
    if (dtype == sizeof(int)) {
        return onesList_i( size );
    } else if (dtype == sizeof(double)) {
        return onesList_d( size );
    } else if (dtype == sizeof(char)) {
        return onesList_c( size );
    } else {
        return NULL;
    }
}

