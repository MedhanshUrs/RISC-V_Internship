# Task 2 – GPIO & UART Validation on VSDSquadron Mini

## 1. Brief Explanation of Implementation

In this task, firmware was developed and flashed onto the VSDSquadron Mini board to validate:

- Basic board bring-up  
- GPIO control using the on-board LED  
- UART communication using a serial terminal  

The firmware initializes the system clock, configures a GPIO pin connected to the on-board LED, and sets up UART communication.  
During runtime, the LED is toggled periodically, and status messages are transmitted over UART to confirm correct execution.

The firmware is modularized using:
- `gpio.c / gpio.h` for GPIO control  
- `uart.c / uart.h` for UART communication  
- `main.c` as the application entry point  

---

## 2. GPIO Pin Chosen and Why

- **Physical Pin:** On-board LED pin  
- **MCU GPIO Port:** GPIOD  
- **MCU GPIO Pin:** 6  
- **Firmware GPIO Identifier:** GPIOD, Pin 6  

**Reason for choosing this pin:**
- The LED is pre-wired on the VSDSquadron Mini board  
- No external wiring is required  
- It provides immediate visual feedback  
- It is ideal for validating GPIO functionality during board bring-up  

---

## 3. UART Message Description

UART output is used to confirm firmware execution and program flow.

**UART Messages Sent:**
- Boot message (indicates firmware start)  
- Task identifier message  
- Counter incrementing message (printed every iteration)  

Example Output:
Count: 1
Count: 2
Count: 3
...

These messages confirm:
- UART initialization is successful  
- The firmware is executing continuously  
- The main loop is running as expected  

**UART Configuration Used:**
- Tool: PuTTY  
- Serial Port: COM3  
- Baud Rate: 115200  
- Data Bits: 8  
- Parity: None  
- Stop Bits: 1  
- Flow Control: None  

---

## 4. How to Build and Flash (Short Steps)

1. Open the PlatformIO project configured for VSDSquadron Mini  
2. Build the firmware  
3. Upload using the on-board WCH-Link debugger  
4. Reset the board  
5. Open PuTTY and connect using:
   - Serial Port: COM3  
   - Baud Rate: 115200  
6. Observe:
   - LED blinking on the board  
   - UART output appearing in the PuTTY terminal  

---

## References

1. VSDSquadron Mini Board Datasheet & Flashing Guide  
2. Task 2 – VSDSquadron Mini Board Bring-Up, GPIO & UART Validation PDF  
3. WCH CH32V003 SDK Documentation  
4. PlatformIO VSDSquadron Mini Board Support  
