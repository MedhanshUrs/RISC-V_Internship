# Project-11 – UART-Controlled Mode Machine

This project implements a UART-controlled mode machine on the VSDSquadron Mini (CH32V003 RISC-V board).  
Multiple operating modes can be selected at runtime through a serial terminal without resetting the board.  
Each mode changes the behaviour of an external LED connected to PD2, including blink patterns and an
interactive reaction-time game.

---

## Drivers Used

- UART driver
- GPIO driver

(Note: Timing behaviour is implemented using cooperative loop counters. No hardware timer is used in the final demo.)

---

## API Summary

### UART Driver
- `uart_init(uint32_t baud)`
- `uart_send_char(char c)`
- `uart_send_string(const char *str)`
- `uart_receive_char(void)`
- `uart_char_available(void)`

### GPIO Driver
- `gpio_led_init(void)`
- `gpio_led_on(void)`
- `gpio_led_off(void)`
- `gpio_led_toggle(void)`

---

## Build and Flash (Short Steps)

1. Open the PlatformIO project for VSDSquadron Mini.
2. Build the firmware.
3. Upload using the on-board WCH-Link debugger.
4. Reset the board.
5. Open PuTTY and connect using:
   - Serial Port: COM3  
   - Baud Rate: 115200

---

## UART Settings

- Port: COM3  
- Baud rate: 115200  
- Data bits: 8  
- Stop bits: 1  
- Parity: None  
- Flow control: None  

---

## How to Demo

Open the serial terminal and use the following commands:

h or ? → Show help menu (This exact command options menu)
0 → LED OFF
1 → Slow blink mode
2 → Fast blink mode
3 → Double-blink pattern
4 → Reaction-time game


Inside the reaction game:

Press any key when the LED turns ON → measure reaction (Lower the time the better)
q → exit game mode

