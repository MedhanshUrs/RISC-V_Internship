# Application Guide – UART Mode Machine

## Overview

This application implements a UART-controlled mode machine that allows a user to select different LED behaviors at run time without resetting the board.
An external LED connected to pin **PD2** is controlled using multiple operating modes, including an interactive reaction-time game.

All hardware interaction is performed through the UART and GPIO driver APIs.

This document explains the application behavior and logic only.
Driver implementation details are covered in the API reference.

---

## Application Modes

The application supports the following operating modes:

| Mode name         | UART command | Description                          |
| ----------------- | ------------ | ------------------------------------ |
| MODE_OFF          | `0`          | LED is forced OFF                    |
| MODE_SLOW_BLINK   | `1`          | LED toggles at a slow rate           |
| MODE_FAST_BLINK   | `2`          | LED toggles at a faster rate         |
| MODE_DOUBLE_BLINK | `3`          | Two short blinks followed by a pause |
| MODE_GAME         | `4`          | Interactive reaction-time game       |

The currently selected mode is stored in a global mode variable and is updated at run time using UART commands.

---

## Application State Machine

At the top level, the application behaves as a simple mode-based state machine.

Each main-loop iteration executes the handler corresponding to the active mode.

High-level structure:

```
Main loop
 ├─ handle user command (if not in game mode)
 └─ execute active mode function
```

---

## Reaction Game State Machine

The reaction-time game internally uses a second state machine.

Two internal states are implemented:

### 1. Waiting state

* LED is OFF
* The user is instructed to wait
* Any early key presses are discarded
* After a delay period, the LED is turned ON and the game transitions to the reaction state

### 2. Reaction state

* LED is ON
* The application waits for a key press
* A counter is incremented continuously while waiting
* When a key is received:

  * the LED is turned OFF
  * the reaction score is printed
  * the game returns to the waiting state for the next round

The user can exit the game at any time by pressing `q`.

When the game exits, control returns to the normal command-based mode machine and the help menu is displayed again.

---

## Task Flow

The application flow can be summarized as:

1. Initialize drivers
2. Print startup banner and help menu
3. Enter main loop
4. If not in game mode:

   * check for UART input
   * update the current mode if a valid command is received
5. Execute the handler for the active mode
6. Repeat continuously

During game mode, the game logic temporarily owns UART input handling.

---

## Timing Behavior

No hardware timer or RTOS is used.

All timing is implemented using cooperative software counters inside the main loop.

Examples:

* slow blink and fast blink are implemented by incrementing counters and toggling the LED when a threshold is reached
* the reaction game delay before turning the LED ON is implemented using a counter
* the reaction score is measured as the number of main-loop iterations that occur while waiting for user input

Because of this design:

* the reaction score represents relative time, not absolute time
* the score depends on CPU speed and compiler optimization

---

## Driver Orchestration

The application orchestrates the drivers as follows:

### UART driver usage

* receive user commands
* print the help menu
* print mode change messages
* print game prompts and reaction scores
* receive user input during the game

### GPIO driver usage

* turn the LED ON or OFF
* toggle the LED for blink patterns
* signal the start of the reaction window during the game

The application never accesses hardware registers directly.

All UART and GPIO operations go through the corresponding driver APIs.

---

## Edge Cases and Error Handling

The following edge cases are explicitly handled by the application:

### Invalid commands

If a character is received that does not correspond to a supported command, an informative message is printed and the user is instructed to display the help menu.

---

### Early key presses during the game

While waiting for the LED to turn ON in the reaction game:

* any received characters are discarded
* this prevents falsely registering a reaction before the LED is activated

---

### Game exit

The user can exit the reaction game at any time by pressing `q`.

When this occurs:

* the LED is turned OFF
* the game state is reset
* the application returns to normal command mode
* the help menu is printed again

---

### Continuous operation without reset

All mode changes occur at run time without requiring a board reset.

The application maintains its internal state across mode transitions and returns cleanly from the game mode to normal operation.

---

## Known Limitations

* The reaction score is based on loop iteration counts and is not calibrated to milliseconds.
* Timing accuracy varies depending on compiler optimization and instruction execution time.
* No random delay is used before the LED turns ON in the reaction game.
