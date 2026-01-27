# Task 3 – Evidence of Execution  
**Platform:** VSDSquadron Mini (CH32V003 RISC-V)

---

## UART Evidence

### Serial Terminal Configuration

| Parameter | Value |
|----------|-------|
| Tool | PuTTY |
| COM Port | COM3 |
| Baud Rate | 115200 |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |
| Flow Control | None |

---

UART Evidence Media

Screenshot: UART_PuTTy.png
📸 Screenshot showing:

PuTTY terminal window

COM3 port visible

Baud rate set to 115200

Startup banner

RX and echo logs (10+ lines)


Hardware Evidence Media

Video: VID20260127145432.mp4
🎥 Short video showing:

Board powered ON

PuTTY terminal open

Characters being typed

Echo output appearing

'1' typed in terminal

External LED turning ON

'1' typed again

External LED turning OFF

Explanation

The demo application uses the UART driver library to perform all UART operations.

Workflow:

uart_init(115200) initializes the UART peripheral

uart_receive_char() waits for a character from the serial terminal

Received characters are echoed using:

uart_send_char()

uart_send_string()

When the character '1' is received:

The application toggles the GPIO PD2 output

The external LED connected on the breadboard changes state

A confirmation message is printed over UART

All UART hardware interaction is performed only through the UART driver APIs.

---

This evidence confirms that:

The UART driver library works correctly

The application correctly uses the library APIs

UART echo and command-based interaction function as expected

The external LED on a breadboard toggles using GPIO PD2

The firmware runs on real VSDSquadron Mini hardware
