# VSDSquadron Mini – UART-Controlled Mode Machine

## Project Overview

This project implements a modular, UART-controlled mode machine for the **VSDSquadron Mini (CH32V003 RISC-V)** development board.
The firmware allows a user to dynamically switch between multiple operating modes over a serial terminal without resetting the board. Each mode controls an external LED connected to PD2 and demonstrates different LED behaviours such as slow blinking, fast blinking, a double-blink pattern, and an interactive reaction-time game.

The project follows a layered design where all hardware access is isolated inside reusable driver libraries, and the application logic operates only through clean driver APIs.

### **Target Hardware**

* **Microcontroller:** CH32V003 (RISC-V)
* **Board:** VSDSquadron Mini
* **Programmer / Debugger:** On-board WCH-Link

---

## Supported Drivers

The project uses a small custom driver layer consisting of:

* **GPIO driver** – External LED control on PD2
* **UART driver** – Serial command interface and logging

*(Note: No hardware timer or PWM driver is used in the final implementation. Timing behaviour is implemented using cooperative software counters inside the application.)*

---

## Folder Structure

The documentation for this project follows the required Task-5 layout:

```text
task5/
└── documentation/
    ├── README.md             # Project overview and quick start
    ├── API_REFERENCE.md      # Driver API documentation
    ├── ARCHITECTURE.md       # System design and data flow
    ├── APPLICATION_GUIDE.md  # Application logic and modes
    ├── DEMO_GUIDE.md         # How to run and verify the demo
    └── CHANGELOG.md          # Version history
```

---

## Quick Start (5-Line Setup)

1. **Clone:** `git clone https://github.com/MedhanshUrs/RISC-V_Internship.git`
2. **Open:** Launch VS Code and open the project folder containing the UART Mode Machine firmware.
3. **Build:** Run *PlatformIO: Build*.
4. **Flash:** Run *PlatformIO: Upload* using the on-board WCH-Link.
5. **Monitor:** Open PuTTY on **COM3** at **115200 baud**.

---

## Why this Architecture?

This project uses a layered and modular architecture in which all low-level hardware access is encapsulated inside driver libraries. The application layer implements only the mode logic and user interaction.

This approach provides:

* **Clear separation of concerns** – application code never accesses hardware registers directly.
* **Reusability** – UART and GPIO drivers can be reused across future projects.
* **Maintainability** – new modes can be added without modifying driver code.
* **Predictable behaviour** – blocking and polling behaviour is explicitly controlled through well-defined APIs.

The architecture closely mirrors industry-style embedded firmware development practices, where drivers and applications are developed and maintained as independent software components.
