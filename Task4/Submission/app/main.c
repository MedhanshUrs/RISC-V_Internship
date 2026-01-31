#include <ch32v00x.h>

#include "uart_driver.h"
#include "gpio_driver.h"

typedef enum
{
    MODE_OFF = 0,
    MODE_SLOW_BLINK,
    MODE_FAST_BLINK,
    MODE_DOUBLE_BLINK,
    MODE_GAME
} mode_t;

static volatile mode_t current_mode = MODE_OFF;
static void handle_command(char c);
static void print_help(void);

static void run_mode(void);

static void mode_off(void);
static void mode_slow_blink(void);
static void mode_fast_blink(void);
static void mode_double_blink(void);
static void uart_print_u32(uint32_t v);
static void mode_game(void);


int main(void)
{
    SystemCoreClockUpdate();

    uart_init(115200);
    gpio_led_init();

    uart_send_string("\r\n=== Task 4 : UART Mode Machine ===\r\n");
    print_help();

    while (1)
    {
        if (current_mode != MODE_GAME)
        {
            if (uart_char_available())
            {
                char c = uart_receive_char();
                handle_command(c);
            }
        }

    run_mode();
    }
}



static void handle_command(char c)
{
    switch (c)
    {
        case '0':
            current_mode = MODE_OFF;
            uart_send_string("Switched to MODE 0 (LED OFF)\r\n");
            break;

        case '1':
            current_mode = MODE_SLOW_BLINK;
            uart_send_string("Switched to MODE 1 (Slow blink)\r\n");
            break;

        case '2':
            current_mode = MODE_FAST_BLINK;
            uart_send_string("Switched to MODE 2 (Fast blink)\r\n");
            break;

        case '3':
            current_mode = MODE_DOUBLE_BLINK;
            uart_send_string("Switched to MODE 3 (Double blink pattern)\r\n");
            break;
        case '4':
            current_mode = MODE_GAME;
            uart_send_string("Switched to MODE 4 (Reaction game)\r\n");
            break;
        case 'h':
        case '?':
            print_help();
            break;

        default:
            uart_send_string("Unknown command. Press 'h' for help.\r\n");
            break;
    }
}

static void print_help(void)
{
    uart_send_string("\r\nAvailable commands:\r\n");
    uart_send_string("0 : LED OFF\r\n");
    uart_send_string("1 : Slow blink (1s)\r\n");
    uart_send_string("2 : Fast blink (200ms)\r\n");
    uart_send_string("3 : Double blink pattern\r\n");
    uart_send_string("4 : Reaction game\r\n");
    uart_send_string("h / ? : Show this help menu\r\n\r\n");
}

static void run_mode(void)
{
    switch (current_mode)
    {
        case MODE_OFF:
            mode_off();
            break;

        case MODE_SLOW_BLINK:
            mode_slow_blink();
            break;

        case MODE_FAST_BLINK:
            mode_fast_blink();
            break;

        case MODE_DOUBLE_BLINK:
            mode_double_blink();
            break;

        case MODE_GAME:
            mode_game();
            break;

        default:
            break;
    }
}

static void mode_off(void)
{
    gpio_led_off();
}

static void mode_slow_blink(void)
{
    static uint32_t cnt = 0;

    cnt++;

    if (cnt > 500000)
    {
        gpio_led_toggle();
        cnt = 0;
    }
}

static void mode_fast_blink(void)
{
    static uint32_t cnt = 0;

    cnt++;

    if (cnt > 150000)
    {
        gpio_led_toggle();
        cnt = 0;
    }
}

static void mode_double_blink(void)
{
    static uint32_t cnt = 0;
    static uint8_t step = 0;

    cnt++;

    if (cnt < 60000)
        return;

    cnt = 0;

    switch(step)
    {
        case 0: gpio_led_on();  step = 1; break;
        case 1: gpio_led_off(); step = 2; break;
        case 2: gpio_led_on();  step = 3; break; 
        case 3: gpio_led_off(); step = 4; break; 

        case 4:                                
            cnt = 0;
            step = 0;
            for(volatile int i=0;i<600000;i++);
            break;
    }
}

static void uart_print_u32(uint32_t v)
{
    char buf[11];
    int i = 0;

    if (v == 0)
    {
        uart_send_char('0');
        return;
    }

    while (v)
    {
        buf[i++] = '0' + (v % 10);
        v /= 10;
    }

    while (i--)
        uart_send_char(buf[i]);
}

static void mode_game(void)
{
    static uint32_t cnt = 0;
    static uint32_t reaction = 0;
    static uint8_t state = 0;

    if (state == 0)
    {
        cnt++;

        if (uart_char_available())
        {
            (void)uart_receive_char();
        }

        if (cnt == 1)
        {
            uart_send_string("\r\nGet ready... (Press any key when the LED turns ON)\r\n");
            uart_send_string("(Press q to exit)\r\n");
            gpio_led_off();
        }

        if (cnt > 800000)
        {
            gpio_led_on();
            uart_send_string("GO!\r\n");

            reaction = 0;
            state = 1;
        }
    }
    else
    {
        reaction++;

        if (uart_char_available())
        {
            char c = uart_receive_char();

            if (c == 'q')
            {
                gpio_led_off();
                uart_send_string("Exiting game mode\r\n");

                current_mode = MODE_OFF;
                state = 0;
                cnt = 0;

                print_help();
                return;
            }

            gpio_led_off();

            uart_send_string("Reaction score: ");
            uart_print_u32(reaction);
            uart_send_string("\r\n");


            state = 0;
            cnt = 0;
        }
    }
}
