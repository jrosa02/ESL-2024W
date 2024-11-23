#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>

LOG_MODULE_REGISTER(semahores, LOG_LEVEL_INF);

K_SEM_DEFINE(SemVar100, 0, 1);
K_SEM_DEFINE(SemVar300, 0, 1);
K_SEM_DEFINE(SemVar500, 0, 1);
K_SEM_DEFINE(SemVar1000, 0, 1);
K_SEM_DEFINE(SemVar2000, 0, 1);
K_SEM_DEFINE(SemVar5000, 0, 1);

#define LOGING_LEN  (1<<10)

uint32_t output_table[6][LOGING_LEN] = {0};

void timer_1_expiry(struct k_timer *timer_id) {
    static size_t count = 0;
    count++;

    if (count % 1 == 0) { k_sem_give(&SemVar100); }
    if (count % 3 == 0) { k_sem_give(&SemVar300); }
    if (count % 5 == 0) { k_sem_give(&SemVar500); }
    if (count % 10 == 0) { k_sem_give(&SemVar1000); }
    if (count % 20 == 0) { k_sem_give(&SemVar2000); }
    if (count % 50 == 0) { k_sem_give(&SemVar5000); }
}

void timestamp(uint8_t clock_nr) {
    static uint32_t current_times[6] = {0};
    static uint32_t prev_times[6] = {0};
    static size_t indexes[6] = {0};

    current_times[clock_nr] = k_cycle_get_32();
    uint32_t delta = current_times[clock_nr] - prev_times[clock_nr];
    output_table[clock_nr][indexes[clock_nr]++ % LOGING_LEN] = delta;
    prev_times[clock_nr] = current_times[clock_nr];

    printk("Clock: %d, Delta: %u\n", clock_nr, delta);
}

void Task100(void) { while (1) { k_sem_take(&SemVar100, K_FOREVER); timestamp(0); } }
void Task300(void) { while (1) { k_sem_take(&SemVar300, K_FOREVER); timestamp(1); } }
void Task500(void) { while (1) { k_sem_take(&SemVar500, K_FOREVER); timestamp(2); } }
void Task1000(void) { while (1) { k_sem_take(&SemVar1000, K_FOREVER); timestamp(3); } }
void Task2000(void) { while (1) { k_sem_take(&SemVar2000, K_FOREVER); timestamp(4); } }
void Task5000(void) { while (1) { k_sem_take(&SemVar5000, K_FOREVER); timestamp(5); } }
