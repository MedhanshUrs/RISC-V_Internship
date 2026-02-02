# Changelog

## v1.2.0 – Game input handling and UI improvement

- Ignored all key presses before the LED turns ON during the reaction game to ensure valid reaction measurements only
- Automatically re-display the main command menu immediately after exiting the game mode
- Added a clear user hint instructing the user to press a key only after the LED turns ON


## v1.1.0 – Reaction game mode added

- Added a UART-controlled reaction time game mode
- Implemented game entry and exit using UART commands
- Displayed reaction score over UART after each round


## v1.0.0 – Initial release

- Implemented GPIO driver for external LED on PD2
- Implemented UART driver and command interface
- Added multi-mode UART-controlled LED behavior (off, slow blink, fast blink, double blink)
```
