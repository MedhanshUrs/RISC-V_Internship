# Task 2 – Evidence of GPIO & UART Validation

This document contains visual and runtime proof that GPIO and UART functionality were successfully validated on the VSDSquadron Mini board.

---

## 1. UART Evidence

### Description

UART output was generated during firmware execution to confirm program flow and runtime behavior.  
The output was captured using a serial terminal.

### Serial Terminal Configuration

- Tool: PuTTY  
- Serial Port: COM3  
- Baud Rate: 115200  
- Data Bits: 8  
- Parity: None  
- Stop Bits: 1  
- Flow Control: None  

### Proof Files

**Screenshot (10+ lines of output):**
Images/UART/UART_Proof.png

**Video (UART output scrolling):**
Videos/UART/VID20260125194935.mp4


### Observations

- The terminal shows more than 10 lines of UART output  
- Boot and task identifier messages are visible  
- Repeated loop messages confirm continuous execution  
- Confirms correct UART initialization and data transmission  

---

## 2. GPIO Evidence

### Description

GPIO functionality was validated using the on-board LED connected to the MCU.  
The LED is toggled periodically by the firmware.

### Hardware Details

- **Physical Pin Label:** On-board LED pin  
- **Firmware GPIO Port:** GPIOD  
- **Firmware GPIO Pin:** 6  

### Proof Files

**Photo (physical board + LED state):**
Images/GPIO/GPIO_Proof.jpg

**Video (LED toggling):**
Videos/GPIO/VID20260125200823.mp4


### Observations

- The photo clearly shows the physical VSDSquadron Mini board  
- The LED state change is visible  
- The video shows the LED turning ON and OFF repeatedly  
- Confirms real hardware GPIO control  

---

## 3. How Correct Behavior Was Verified

### GPIO Verification

- The LED toggles at a fixed time interval  
- The behavior matches the firmware delay logic  
- Confirms correct GPIO initialization and output control  

### UART Verification

- UART output appears consistently in PuTTY  
- Messages are not corrupted  
- Output timing matches firmware loop execution  
- Confirms correct UART configuration and communication  

---

## 4. Conclusion

The following have been successfully validated:

- Firmware flashing and execution  
- GPIO output using the on-board LED  
- UART communication using PuTTY on COM3  
- Continuous runtime operation  
- Physical hardware interaction  

This confirms that all Task-2 requirements for board bring-up, GPIO validation, and UART communication have been fully satisfied.

---
