#include "jitter.h"

int main(void) {
    printk("Starting jitter timers...\n");
    initialize_timers();

    while (1) {
        k_sleep(K_SECONDS(10)); // Main thread can sleep while timers run
    }
}

