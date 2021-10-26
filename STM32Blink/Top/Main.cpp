#include <getopt.h>
#include <stdlib.h>
#include <ctype.h>

#include <STM32/Top/Components.hpp>

volatile sig_atomic_t terminate = 0;

#include <signal.h>
#include <stdio.h>



void run1cycle(void) {
    // call interrupt to emulate a clock
    blockDrv.callIsr();
    Os::Task::delay(1000); //10Hz
}

void runcycles(NATIVE_INT_TYPE cycles) {
    if (cycles == -1) {
        while (true) {
            run1cycle();
        }
    }

    for (NATIVE_INT_TYPE cycle = 0; cycle < cycles; cycle++) {
        run1cycle();
    }
}

int main(int argc, char* argv[]) {
    
    constructApp();


    int cycle = 0;

    while (!terminate) {
//        (void) printf("Cycle %d\n",cycle);
        runcycles(1);
        cycle++;
    }

    // Give time for threads to exit
    (void) printf("Waiting for threads...\n");
    Os::Task::delay(1000);

    (void) printf("Exiting...\n");

    return 0;
}
