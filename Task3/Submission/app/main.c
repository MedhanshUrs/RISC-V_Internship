#include <ch32v00x.h>
#include "uart_driver.h"

#define LED_PORT GPIOD
#define LED_PIN  GPIO_Pin_2

static void gpio_init(void);
static void led_toggle(void);

int main(void)
{
    SystemCoreClockUpdate();

    gpio_init();
    uart_init(115200);

    uart_send_string("\r\n=== Task 3 UART Driver Demo ===\r\n");
    uart_send_string("Echo demo + command-based LED toggle\r\n");
    uart_send_string("Type any key to echo\r\n");
    uart_send_string("Send '1' to toggle external LED (PD2)\r\n");

    while (1)
    {
        char rx = uart_receive_char();

        uart_send_string("RX: ");
        uart_send_char(rx);
        uart_send_string("\r\n");

        if (rx == '1')
        {
            led_toggle();
            uart_send_string("LED toggled!\r\n");
        }
        else
        {
            uart_send_string("Echo: ");
            uart_send_char(rx);
            uart_send_string("\r\n");
        }
    }
}

static void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = LED_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);

    GPIO_ResetBits(LED_PORT, LED_PIN);  // Start OFF (active-HIGH)
}

static void led_toggle(void)
{
    if (GPIO_ReadOutputDataBit(LED_PORT, LED_PIN))
        GPIO_ResetBits(LED_PORT, LED_PIN);  // OFF
    else
        GPIO_SetBits(LED_PORT, LED_PIN);    // ON
}
