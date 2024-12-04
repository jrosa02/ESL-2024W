#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   100000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static bool led_state = false;

/* Command to turn on the LED */
static int cmd_led_on(const struct shell *shell, size_t argc, char **argv) {
    if (!gpio_is_ready_dt(&led)) {
        shell_print(shell, "LED device is not ready");
        return -ENODEV;
    }

    gpio_pin_set_dt(&led, 1);
    led_state = true;
    shell_print(shell, "LED turned ON");
    return 0;
}

/* Command to turn off the LED */
static int cmd_led_off(const struct shell *shell, size_t argc, char **argv) {
    if (!gpio_is_ready_dt(&led)) {
        shell_print(shell, "LED device is not ready");
        return -ENODEV;
    }

    gpio_pin_set_dt(&led, 0);
    led_state = false;
    shell_print(shell, "LED turned OFF");
    return 0;
}

/* Shell commands definition */
SHELL_STATIC_SUBCMD_SET_CREATE(led_cmds,
    SHELL_CMD_ARG(on, NULL, "Turn on the LED", cmd_led_on, 1, 0),
    SHELL_CMD_ARG(off, NULL, "Turn off the LED", cmd_led_off, 1, 0),
    SHELL_SUBCMD_SET_END
);

/* Register shell command group */
SHELL_CMD_REGISTER(led, &led_cmds, "Control the LED", NULL);

void main(void) {
    int ret;

    if (!gpio_is_ready_dt(&led)) {
        LOG_ERR("LED device is not ready");
        return;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        LOG_ERR("Failed to configure LED pin");
        return;
    }

    LOG_INF("System ready. Use 'led on' or 'led off' commands to control the LED.");

    while (1) {
        /* Optional: Blink LED in the main loop */
        gpio_pin_toggle_dt(&led);
        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(SLEEP_TIME_MS);
    }
}
