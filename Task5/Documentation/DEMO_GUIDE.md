# Demo and Verification Guide

This guide allows a reviewer to build, flash, run and verify the UART-controlled mode machine on the VSDSquadron Mini in less than five minutes.

---

## 1. Prerequisites

Before starting, ensure you have the following:

**Hardware**

* VSDSquadron Mini (CH32V003)
* On-board WCH-Link programmer

**Software**

* VS Code with the PlatformIO extension installed

**Connection**

* Board connected to the PC using the on-board WCH-Link USB connection

---

## 2. Flashing the Firmware

1. Open the `Task4/Submission` project in VS Code.
2. Connect the VSDSquadron Mini to your computer using the USB cable.
3. Click the **PlatformIO: Build** icon to compile the code.
4. Click the **PlatformIO: Upload** icon to flash the board.
5. Wait for the terminal to display a successful upload message.

---

## UART Settings

Use a serial terminal such as PuTTY with the following settings:

* Port: COM3
* Baud rate: 115200
* Data bits: 8
* Stop bits: 1
* Parity: None
* Flow control: None

---

## Exact Commands to Type

After reset and after opening the serial terminal:

```
h
```

Displays the help menu.

```
0
```

Switches to LED OFF mode.

```
1
```

Switches to slow blink mode.

```
2
```

Switches to fast blink mode.

```
3
```

Switches to double-blink pattern mode.

```
4
```

Starts the reaction-time game.

Inside the reaction game:

```
Press any key when the LED turns ON
```

to register a reaction.

```
q
```

Exits the game and returns to the main menu.

---

## Expected UART Output

The displayed output includes:

```
=== Task 4 : UART Mode Machine ===

Available commands:
0 : LED OFF
1 : Slow blink (1s)
2 : Fast blink (200ms)
3 : Double blink pattern
4 : Reaction game
h / ? : Show this help menu

Switched to MODE 1 (Slow blink)
Switched to MODE 2 (Fast blink)
Switched to MODE 3 (Double blink pattern)
Switched to MODE 0 (LED OFF)
Switched to MODE 4 (Reaction game)

Get ready...
(Press q to exit)
GO!
Reaction score: 649775
Get ready...
(Press q to exit)
GO!
Exiting game mode //Upon entering q

Available commands:
0 : LED OFF
1 : Slow blink (1s)
2 : Fast blink (200ms)
3 : Double blink pattern
4 : Reaction game
h / ? : Show this help menu

Unknown command. Press 'h' for help. //Upon entering any character other than those in the list

Available commands: //Upon entering h or ?
0 : LED OFF
1 : Slow blink (1s)
2 : Fast blink (200ms)
3 : Double blink pattern
4 : Reaction game
h / ? : Show this help menu
```

---

## What the Reviewer Should Observe on Hardware

The reviewer should observe the following on the physical hardware:

* An external LED connected to **PD2** on the VSDSquadron Mini using a breadboard.
* When command `0` is sent, the LED remains OFF.
* When command `1` is sent, the LED blinks slowly.
* When command `2` is sent, the LED blinks faster.
* When command `3` is sent, the LED performs a double-blink pattern followed by a pause.
* When command `4` is sent:

  * the LED remains OFF during the waiting phase,
  * the LED turns ON to indicate the reaction window,
  * the LED turns OFF immediately after a key is pressed.

When `q` is pressed during the reaction game, the LED turns OFF and the application returns to the command menu.
