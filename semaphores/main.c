#include "semahores.h"

#define MY_STACK_SIZE 500
#define MY_PRIORITY 5
#define TIMER1_Count 100

int main(void) {
    printk("Starting jitter timers...\n");
    k_timer_start(&timer_1, K_USEC(TIMER1_Count), K_USEC(TIMER1_Count));

    k_thread_start(task100_id);
    k_thread_start(task300_id);
    k_thread_start(task500_id);
    k_thread_start(task1000_id);
    k_thread_start(task2000_id);
    k_thread_start(task5000_id);

    while (1)
    {
        /* code */
    }
    
}