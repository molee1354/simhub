#include "list_commonincl.h"

static List* initList_i( int size ) {
    List* list = makeList(sizeof(int));
    if (list == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( list, 0 ); }
    return list;
}
static List* initList_d( int size ) {
    List* list = makeList(sizeof(double));
    if (list == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( list, 0. ); }
    return list;
}
static List* initList_c( int size ) {
    List* list = makeList(sizeof(char));
    if (list == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( list, '\0' ); }
    return list;
}

List* initList( size_t dtype, int size ) {
    if (dtype == sizeof(int)) {
        return initList_i( size );
    } else if (dtype == sizeof(double)) {
        return initList_d( size );
    } else if (dtype == sizeof(char)) {
        return initList_c( size );
    } else {
        return NULL;
    }
}

