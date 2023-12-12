#include "list_commonincl.h"

List* toList_i( int* nList, int size ) {
    List* list = makeList(sizeof(int));
    if (list == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( list, nList[i] ); }
    return list;
}
List* toList_d( double* nList, int size ) {
    List* list = makeList(sizeof(double));
    if (list == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( list, nList[i] ); }
    return list;
}
List* toList_c( char* nList, int size ) {
    List* list = makeList(sizeof(char));
    if (list == NULL) { return NULL; }
    for (int i=0; i<size; i++) { append( list, nList[i] ); }
    return list;
}

