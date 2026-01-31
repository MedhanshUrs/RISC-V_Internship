#include "gpio_driver.h"
#include <ch32v00x.h>

#define LED_PORT   GPIOD
#define LED_PIN    GPIO_Pin_2

void gpio_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = LED_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(LED_PORT, LED_PIN);
}

void gpio_led_on(void)
{
    GPIO_SetBits(LED_PORT, LED_PIN);
}

void gpio_led_off(void)
{
    GPIO_ResetBits(LED_PORT, LED_PIN);
}

void gpio_led_toggle(void)
{
    if (GPIO_ReadOutputDataBit(LED_PORT, LED_PIN))
        GPIO_ResetBits(LED_PORT, LED_PIN);
    else
        GPIO_SetBits(LED_PORT, LED_PIN);
}

