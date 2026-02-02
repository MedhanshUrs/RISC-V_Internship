# API Reference

This document describes the public APIs exposed by the UART and GPIO driver libraries used by the *UART-Controlled Mode Machine* project running on the VSDSquadron Mini (CH32V003).

All hardware access is performed exclusively through these APIs.
The application layer does not directly access peripheral registers.

---

# UART Driver API

## Overview

The UART driver provides blocking transmit and polling-based receive functionality using **USART1** on the VSDSquadron Mini board.

### Hardware mapping

* Peripheral : USART1
* TX pin     : PD5
* RX pin     : PD6

---

### uart_init

```c
void uart_init(uint32_t baud_rate);
```

**Brief**

Initializes the USART1 peripheral and configures the GPIO pins required for UART communication.

**Parameters**

* `baud_rate`
  Desired UART baud rate.

**Return value**

* None.

**Constraints / Notes**

* Must be called once before any other UART API.
* Configures:

  * PD5 as UART TX (alternate function push-pull)
  * PD6 as UART RX (floating input)
* Transmission and reception use polling (no interrupts or DMA).

**Example usage**

```c
uart_init(115200);
```

---

### uart_send_char

```c
void uart_send_char(char c);
```

**Brief**

Transmits a single character over UART.

**Parameters**

* `c`
  Character to be transmitted.

**Return value**

* None.

**Constraints / Notes**

* Blocking function.
* Waits until the transmit operation has completed before returning.

**Example usage**

```c
uart_send_char('A');
```

---

### uart_send_string

```c
void uart_send_string(const char *str);
```

**Brief**

Transmits a null-terminated string over UART.

**Parameters**

* `str`
  Pointer to a null-terminated string buffer.

**Return value**

* None.

**Constraints / Notes**

* Blocking function.
* Internally transmits one character at a time using `uart_send_char`.

**Example usage**

```c
uart_send_string("Hello from VSDSquadron Mini\r\n");
```

---

### uart_receive_char

```c
char uart_receive_char(void);
```

**Brief**

Receives a single character from the UART interface.

**Parameters**

* None.

**Return value**

* The received character.

**Constraints / Notes**

* Blocking function.
* Waits until a character is received.
* Should not be called unless the application is prepared to block.

**Example usage**

```c
char c = uart_receive_char();
```

---

### uart_char_available

```c
uint8_t uart_char_available(void);
```

**Brief**

Checks whether a character is available in the UART receive buffer.

**Parameters**

* None.

**Return value**

* `1` if a character is available.
* `0` if no character is available.

**Constraints / Notes**

* Non-blocking function.
* Intended to be used before calling `uart_receive_char` when non-blocking behaviour is required.

**Example usage**

```c
if (uart_char_available())
{
    char c = uart_receive_char();
}
```

---

# GPIO Driver API

## Overview

The GPIO driver provides control of a single external LED connected to the VSDSquadron Mini board.

### Hardware mapping

* Port : GPIOD
* Pin  : PD2
* Electrical logic : Active-high
* LED connection : External LED mounted on a breadboard connected to PD2 and GND

---

### gpio_led_init

```c
void gpio_led_init(void);
```

**Brief**

Initializes the GPIO pin connected to the external LED.

**Parameters**

* None.

**Return value**

* None.

**Constraints / Notes**

* Configures PD2 as push-pull output.
* The LED is turned OFF after initialization.

**Example usage**

```c
gpio_led_init();
```

---

### gpio_led_on

```c
void gpio_led_on(void);
```

**Brief**

Turns the external LED ON.

**Parameters**

* None.

**Return value**

* None.

**Constraints / Notes**

* Sets PD2 to logic HIGH.

**Example usage**

```c
gpio_led_on();
```

---

### gpio_led_off

```c
void gpio_led_off(void);
```

**Brief**

Turns the external LED OFF.

**Parameters**

* None.

**Return value**

* None.

**Constraints / Notes**

* Sets PD2 to logic LOW.

**Example usage**

```c
gpio_led_off();
```

---

### gpio_led_toggle

```c
void gpio_led_toggle(void);
```

**Brief**

Toggles the current state of the external LED.

**Parameters**

* None.

**Return value**

* None.

**Constraints / Notes**

* Reads the current output state of PD2 and inverts it.

**Example usage**

```c
gpio_led_toggle();
```
