# Project-11 – Evidence of Execution

Platform: VSDSquadron Mini (CH32V003 RISC-V)

---

## UART Evidence

### Serial Terminal Configuration

- Tool: PuTTY
- Port: COM3
- Baud rate: 115200
- Data bits: 8
- Stop bits: 1
- Parity: None
- Flow control: None

### Screenshot Evidence

A screenshot is provided showing:

- PuTTY terminal connected to COM3
- Project startup banner
- Help menu output
- Mode switching commands
- Reaction-time game messages
- More than 10 lines of relevant UART logs

File: Task4_PuTTy.png

---

## Hardware Evidence

A Short video is provided showing:

- The VSDSquadron Mini board
- An external LED mounted on a breadboard
- A wire connected from PD2 of the board to the LED
- A wire connected from the LED to GND
- The LED turns on and OFF according to selected modes
- The LED reacts during the reaction-time game

File: VID20260131152955.mp4

---

## Verification Notes

The following were tested and verified on real hardware:

- All UART commands (0 to 4, h, ?) correctly switch modes without resetting the board
- The help menu is printed correctly over UART
- The external LED connected to PD2 responds to:
  - slow blink mode
  - fast blink mode
  - double-blink pattern
- The reaction-time game:
  - ignores early key presses before the LED turns ON
  - accepts a key press only after the LED turns ON
  - prints a reaction score over UART
  - allows exiting the game using the `q` key
- After exiting the game, the main menu is displayed again

---

## Limitations

- Timing and reaction measurement are based on cooperative loop counters rather than a hardware timer.
- The reaction score represents relative timing (loop count), not real milliseconds.
