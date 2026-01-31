#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

void gpio_led_init(void);
void gpio_led_on(void);
void gpio_led_off(void);
void gpio_led_toggle(void);

#endif
