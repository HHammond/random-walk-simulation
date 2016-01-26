/* Run a random Bernoulli walk counting the number of times each simulation
 * crosses switches sides.
 *
 * Each line represents the result of one experiment.
 *
 * Usage:
 *
 * walk <Number of Simulations> <Number of Iterations>
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define sign(x) ((x > 0) - (x < 0))

typedef enum {None=0, A, B} State;


static const int8_t CHANGE_LOOKUP[2] = {-1, 1};


/* Run random walk and count number of times walk crosses over zero.
 *
 * :params iterations: number of iterations in the simulation
 */
int run_simulation(const size_t iterations){
    register int32_t value = 0;
    register uint32_t switches = 0;
    register State current = None,
                   previous = None;

    for(size_t i = 0; i < iterations; ++i){
        value += CHANGE_LOOKUP[rand() % 2];

        switch(sign(value)){
            case  1: current = A; break;
            case -1: current = B; break;
            case  0: current = previous; break;
        }

        if(current != previous
                && (value == 1 || value == -1)
                && previous != None){
            ++switches;
        }

        previous = current;
    }

    return switches;
}

int main(int argc, char *argv[]){
    size_t simulations,
           iterations;

    sscanf(argv[1], "%zi", &simulations);
    sscanf(argv[2], "%zi", &iterations);
    srand(time(0));

    for(size_t i = 0; i < simulations; ++i){
        printf("%d\n", run_simulation(iterations));
    }
}
