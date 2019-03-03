#include <stdio.h>
#include "operations.h"

int main(int argc, char *argv[]) {
    product *ex = makeProduct("Apple Watch", 500.0, "Watches", 1199.99, "per watch");
    product *ci = makeProduct("Microsoft Watch", 800.0, "Watches", 799.99, "per watch");
    product *bb = makeProduct("Blackberry Watch", 20.0, "Watches", 99.99, "per watch");
    insert(&ex, ci);
    insert(&ex, bb);
    rmItem(ex, ex);
    findItem(ex, "Microsoft Watch");
    findItem(ex, "Blackberry Watch");
    return 0;
}