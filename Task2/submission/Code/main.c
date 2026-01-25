#include <ch32v00x.h>
#include <debug.h>
#include "gpio.h"
#include "uart.h"

int main(void)
{
    SystemCoreClockUpdate();
    Delay_Init();

    gpio_init();

    uart_init();

    uart_print("VSDSquadron Mini");
    uart_print("FW Version: 1.0");
    uart_print("Boot successful");

    while (1)
    {
        gpio_toggle();
        uart_print_counter();
        Delay_Ms(1000);

    }
}
