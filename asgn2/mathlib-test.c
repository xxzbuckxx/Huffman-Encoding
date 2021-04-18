#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h> // For getopt()

#define OPTIONS "asctl"

static void tests(double (*operation)(), double (*library)(), double start, double end) {

    /* printf("  x\t\t  myfunc\t   libfunc\tdifference\n"); */
    /* printf("  -\t\t  ------\t   -------\t---------\n"); */
    for (double x = start; x < end; x += 0.00001) {
        double my_imp = operation(x);
        double lib_imp = library(x);
        double difference = my_imp - lib_imp;
        /* printf(" %7.4f % 16.5f % 16.5f % 16.15f\n", x, my_imp, lib_imp, difference); */
        /* printf(" %7.41f % 16.81f % 16.81f % 16.101f\n", x, my_imp, lib_imp, difference); */
        printf("%7.3f %16.20f\n", x, difference);
    }
}

int main(int argc, char **argv) {
    int opt = 0;

    // Parse w getopt before
    // Remember to ensure that tests do not run twice
    // Remember to add default case
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            tests(arcSin, asin, -1, 1);
            tests(arcCos, acos, -1, 1);
            tests(arcTan, atan, -1, 10);
            tests(Log, log, 1, 10);
            return 0;
        case 's': tests(arcSin, asin, -1, 1); break;
        case 'c': tests(arcCos, acos, -1, 1); break;
        case 't': tests(arcTan, atan, 1, 10); break;
        case 'l': tests(Log, log, 1, 10); break;
        }
    }

    return 0;
}
