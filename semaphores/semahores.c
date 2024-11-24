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

#define LOGING_LEN  (1<<10u)
#define CLOCKS_NR    (6u)

#define DEBUG_PRINT(...) printk(__VA_ARGS__)

uint32_t output_table[CLOCKS_NR][LOGING_LEN] = {0};
static size_t indexes[CLOCKS_NR] = {0};

void timer_1_expiry(struct k_timer *timer_id) {
    static size_t count = 0;
    count++;

    if (count % 1 == 0) { k_sem_give(&SemVar100); }
    if (count % 3 == 0) { k_sem_give(&SemVar300); }
    if (count % 5 == 0) { k_sem_give(&SemVar500); }
    if (count % 10 == 0) { k_sem_give(&SemVar1000); }
    if (count % 20 == 0) { k_sem_give(&SemVar2000); }
    if (count % 50 == 0) { k_sem_give(&SemVar5000); }

    if (indexes[5] > LOGING_LEN - 2)
    {
        for (size_t i = 0; i < 6; i++)
        {
            for (size_t j = 0; j < LOGING_LEN-2; j++)
            {
                printk("C: %d, S: %u, D: %u\n", i, j, output_table[i][j]);
            }
        }
    }
}

#define timestamp(clock_nr)                                                                    \
    {                                                                                          \
        uint32_t current_times = {0};                                                          \
        static uint32_t prev_times = {0};                                                      \
                                                                                               \
        current_times = k_cycle_get_32();                                                      \
                                                                                               \
        output_table[clock_nr][indexes[clock_nr]++ % LOGING_LEN] = current_times - prev_times; \
        prev_times = current_times;                                                            \
    }

void Task100(void) 
{ 
    while (1) 
    {
        if (k_sem_take(&SemVar100, K_MSEC(10)) == 0)  // Timeout of 10ms
        {
            timestamp(0);
        }
        else
        {
            printk("Task100 Late\n");  // If timeout occurs, log late
        }
    } 
}

void Task300(void) 
{ 
    while (1) 
    {
        if (k_sem_take(&SemVar300, K_MSEC(30)) == 0)  // Timeout of 30ms
        {
            timestamp(1);
        }
        else
        {
            printk("Task300 Late\n");  // If timeout occurs, log late
        }
    } 
}

void Task500(void) 
{ 
    while (1) 
    {
        if (k_sem_take(&SemVar500, K_MSEC(50)) == 0)  // Timeout of 50ms
        {
            timestamp(2);
        }
        else
        {
            printk("Task500 Late\n");  // If timeout occurs, log late
        }
    } 
}

void Task1000(void) 
{ 
    while (1) 
    {
        if (k_sem_take(&SemVar1000, K_MSEC(100)) == 0)  // Timeout of 100ms
        {
            timestamp(3);
        }
        else
        {
            printk("Task1000 Late\n");  // If timeout occurs, log late
        }
    } 
}

void Task2000(void) 
{ 
    while (1) 
    {
        if (k_sem_take(&SemVar2000, K_MSEC(200)) == 0)  // Timeout of 200ms
        {
            timestamp(4);
        }
        else
        {
            printk("Task2000 Late\n");  // If timeout occurs, log late
        }
    } 
}

void Task5000(void) 
{ 
    while (1) 
    {
        if (k_sem_take(&SemVar5000, K_MSEC(500)) == 0)  // Timeout of 500ms
        {
            timestamp(5);
        }
        else
        {
            printk("Task5000 Late\n");  // If timeout occurs, log late
        }
    } 
}

