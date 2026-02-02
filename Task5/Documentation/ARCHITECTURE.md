# System Architecture

## Overview

This project is structured using a layered embedded firmware architecture.
All hardware access is isolated inside reusable driver modules, while the application layer implements only the mode machine and user interaction logic.

The firmware runs on the VSDSquadron Mini (CH32V003) and provides a UART-controlled interface to switch LED behaviour at run time.

---

## High-Level Block Diagram

```
          PC / Laptop
        (PuTTY - COM3)
                |
                |  UART
                v
        +----------------+
        |   UART Driver  |
        +----------------+
                |
                v
+--------------------------------+
|        Application Layer        |
|    UART Mode Machine (main)     |
|  - command handling             |
|  - mode state machine           |
|  - reaction-time game           |
+--------------------------------+
                |
                v
        +----------------+
        |   GPIO Driver  |
        +----------------+
                |
                v
     External LED (PD2)
```

---

## Layer Separation

### Driver layer

The driver layer provides all low-level access to hardware peripherals.

It contains:

* UART driver

  * USART1 configuration
  * transmit and receive primitives
* GPIO driver

  * configuration of PD2
  * LED on / off / toggle operations

The driver layer is responsible only for:

* register configuration
* peripheral control
* providing clean APIs

The driver layer contains no application logic.

---

### Application layer

The application layer implements the UART-controlled mode machine and the reaction-time game.

It is responsible for:

* decoding UART commands
* switching between operating modes
* executing the selected LED behaviour
* managing the internal game state

The application layer never accesses peripheral registers directly and interacts only through the driver APIs.

This approach is sufficient for the small number of peripherals and real-time constraints of the project.

---

## Data Flow

1. User input is sent from the PC terminal through UART.
2. The UART driver receives the character.
3. The application reads the character using the UART driver API.
4. The application updates its internal state or current mode.
5. The application issues LED control requests through the GPIO driver.
6. The GPIO driver updates the physical LED pin (PD2).

---

## Control Flow

The firmware executes continuously inside the main loop.

The high-level control flow is:

```
main loop
 ├─ check UART input (if not in game mode)
 ├─ update current mode based on command
 └─ execute active mode handler
```

For the reaction-time game mode, the control flow is extended with an internal two-state machine:

```
WAIT state
 └─ LED OFF, early input discarded

REACTION state
 └─ LED ON, wait for user key
```

The game mode temporarily takes ownership of UART input handling and returns control to the normal command handler when the game exits.

---

## Why This Architecture Was Chosen

This architecture was selected to match industry-standard embedded firmware practices.

The key design goals were:

* strict separation between hardware access and application logic
* reusable driver modules
* simple and predictable execution model

Using a layered structure provides the following advantages:

* drivers can be reused in future projects without modification
* application logic remains readable and easy to extend
* hardware configuration is centralized and isolated
* mode behaviour can be modified without touching driver code

A cooperative loop-based design was chosen instead of interrupts or an RTOS to keep the firmware simple, deterministic, and suitable for the limited resource environment of the CH32V003 microcontroller.
