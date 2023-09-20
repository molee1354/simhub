#include "gol_commonincl.h"

#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        render(argc, argv);
    } else if ( !strcmp(argv[1], "save") ) {
        saveSim();
    } else {
        puts("Incorrect input.");
    }
    return 0;
}
