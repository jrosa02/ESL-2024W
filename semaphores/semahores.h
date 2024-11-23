#ifndef SEMAHORES_H
#define SEMAHORES_H

#include <zephyr/kernel.h>

// Your function declarations, macros, and type definitions go here.
#ifdef __cplusplus
extern "C" {
#endif

void timer_1_expiry(struct k_timer *timer_id);

K_TIMER_DEFINE(timer_1, timer_1_expiry, NULL);

void Task100(void);
void Task300(void);
void Task500(void);
void Task1000(void);
void Task2000(void);
void Task5000(void);

K_THREAD_DEFINE(task100_id, 1024, Task100, NULL, NULL, NULL, 1, 0, 0);
K_THREAD_DEFINE(task300_id, 1024, Task300, NULL, NULL, NULL, 1, 0, 0);
K_THREAD_DEFINE(task500_id, 1024, Task500, NULL, NULL, NULL, 1, 0, 0);
K_THREAD_DEFINE(task1000_id, 1024, Task1000, NULL, NULL, NULL, 1, 0, 0);
K_THREAD_DEFINE(task2000_id, 1024, Task2000, NULL, NULL, NULL, 1, 0, 0);
K_THREAD_DEFINE(task5000_id, 1024, Task5000, NULL, NULL, NULL, 1, 0, 0);

void timestamp(uint8_t clock_nr);

#ifdef __cplusplus
}
#endif

#endif // SEMAHORES_H