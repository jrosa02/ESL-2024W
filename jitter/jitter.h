#ifndef JITTER_H
#define JITTER_H

#include <zephyr/kernel.h>

// Your function declarations, macros, and type definitions go here.

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize and start multiple timers with different periods.
 */
void initialize_timers(void);
void timer_1_expiry(struct k_timer *timer_id);
void timer_2_expiry(struct k_timer *timer_id);
void timer_3_expiry(struct k_timer *timer_id);


#ifdef __cplusplus
}
#endif

#endif // JITTER_H