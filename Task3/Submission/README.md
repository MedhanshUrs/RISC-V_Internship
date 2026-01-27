# Task 3 – UART Driver Library + Application Demo  
**Platform:** VSDSquadron Mini (CH32V003 RISC-V)

---

## Implemented Library

**Library Name:** `uart_driver`

A reusable UART driver library was implemented to abstract all UART hardware access on the VSDSquadron Mini board.

**Library Files:**
- `lib/uart_driver.h`
- `lib/uart_driver.c`

---

## UART Driver APIs

| API Function | Description |
|-------------|-------------|
| `uart_init(uint32_t baud_rate)` | Initializes the UART peripheral |
| `uart_send_char(char c)` | Sends one character (blocking) |
| `uart_send_string(const char *str)` | Sends a string (blocking) |
| `uart_receive_char(void)` | Receives one character (blocking, polling) |

---

## Demo Application Description

**File:** `app/main.c`

The demo application demonstrates:

- UART initialization at 115200 baud  
- UART echo (type → receive → transmit back)  
- Command-based interaction  
- External LED control  

### Application Behavior

- Prints a startup banner over UART  
- Echoes all received characters  
- Toggles an external LED on **PD2** when `'1'` is received  
- Logs all RX and TX activity over UART  

---

## How to Build and Flash (Short Steps)

1. Open the PlatformIO project configured for VSDSquadron Mini  
2. Build the firmware  
3. Upload using the on-board WCH-Link debugger  
4. Reset the board  
5. Open PuTTY and connect using:  
   - **Serial Port:** COM3  
   - **Baud Rate:** 115200  
6. Observe:  
   - UART output appearing in the PuTTY terminal  
   - External LED toggling when `'1'` is sent  

---

## UART Configuration

| Parameter | Value |
|----------|-------|
| UART Peripheral | USART1 |
| TX Pin | PD5 |
| RX Pin | PD6 |
| Baud Rate | 115200 |
| Serial Tool | PuTTY |
| COM Port | COM3 |

---

## Summary

This task demonstrates:

- A clean UART driver library  
- Modular separation between driver and application  
- UART echo functionality  
- Command-based LED control  
- Verified execution on real hardware  

---

