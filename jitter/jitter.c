#include "jitter.h"
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>

LOG_MODULE_REGISTER(jitter, LOG_LEVEL_INF);

#define TIMER1_Count 100
#define TIMER2_Count 500
#define TIMER3_Count 1000

// Timer instances
K_TIMER_DEFINE(timer_1, timer_1_expiry, NULL);
K_TIMER_DEFINE(timer_2, timer_2_expiry, NULL);
K_TIMER_DEFINE(timer_3, timer_3_expiry, NULL);

// Variables to track previous execution times for each timer
static uint32_t prev_time_1 = 0;
static uint32_t prev_time_2 = 0;
static uint32_t prev_time_3 = 0;

// Timer callback functions
void timer_1_expiry(struct k_timer *timer_id) {
    uint32_t curr_time = k_cycle_get_32();
    if (prev_time_1 != 0) {
        uint32_t elapsed_us = k_cyc_to_us_near32(curr_time - prev_time_1);
        printk("Timer 1: elapsed = %ul us\n", elapsed_us);
    }
    prev_time_1 = curr_time;
}

void timer_2_expiry(struct k_timer *timer_id) {
    uint32_t curr_time = k_cycle_get_32();
    if (prev_time_2 != 0) {
        uint32_t elapsed_us = k_cyc_to_us_near32(curr_time - prev_time_2);
        printk("Timer 2: elapsed = %ul us\n", elapsed_us);
    }
    prev_time_2 = curr_time;
}

void timer_3_expiry(struct k_timer *timer_id) {
    uint32_t curr_time = k_cycle_get_32();
    if (prev_time_3 != 0) {
        uint32_t elapsed_us = k_cyc_to_us_near32(curr_time - prev_time_3);
        printk("Timer 3: elapsed = %ul us\n", elapsed_us);
    }
    prev_time_3 = curr_time;
}

void initialize_timers(void) {
    // Start timers with different periods
    k_timer_start(&timer_1, K_USEC(TIMER1_Count), K_USEC(TIMER1_Count));
    k_timer_start(&timer_2, K_USEC(TIMER2_Count), K_USEC(TIMER2_Count)); 
    k_timer_start(&timer_3, K_USEC(TIMER3_Count), K_USEC(TIMER3_Count));
}
