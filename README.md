# FLEXITIMER - Arduino Timer Systems

## Introduction
**FLEXITIMER** is a versatile timing system based on the **Arduino Nano** platform, designed to provide stopwatch, countdown, and clock functionalities. The FLEXITIMER project comes in two versions:

- **FX486**: The standard version, with extended components and modular connectivity for more robust projects.
- **MX486**: A miniaturized version of the FX486, designed for projects where space is limited, while retaining key functionalities of the standard version.

Both versions use the Arduino Nano as the central microcontroller and are programmable via the Arduino IDE, with compatibility for RTC modules to handle real-time clock functions.

## Version Features

### FX486 (Standard Version)
- **Extended Control Board**: Allows for greater modularity, compatible with additional modules via I2C bus and extra analog/digital ports.
- **Integrated NO/NC Relay**: Controls external devices based on the timer programs.
- **8-digit 7-segment Display**: Provides a clear view for timers, stopwatches, and clock functions.
- **Extended Connectivity**: Includes I/O conversion boards, connectors for a numeric keypad, and pins for external sensors.

### MX486 (Miniaturized Version)
- **Compact Size**: Designed for projects with limited space, while still offering the essential features of the standard version.
- **Integrated Components**: Reduces the need for external modules but still includes an NO/NC relay and 7-segment display.
- **Same Flexibility**: Programmable in the same way as the FX486 using the Arduino IDE, and compatible with RTC modules and basic sensors.

## Main Features

- **Clock Mode**: Allows the system to function as a clock with the DS3231 RTC module.
- **Countdown Timer**: Set values for countdown timers using the numeric keypad, with real-time display updates.
- **Stopwatch**: Measures time down to the millisecond with start, stop, and reset functions.
- **External Control via Relay**: Control external devices or circuits using the integrated NO/NC relay based on the programmed timing.

## Installation

### Step 1: Download the Arduino IDE
Download and install the [Arduino IDE](https://www.arduino.cc/en/software) on your computer.

### Step 2: Clone or Download the Repository
Clone this repository or download it as a zip file and extract it on your local machine.

### Step 3: Open the Project in the Arduino IDE
1. Open the Arduino IDE.
2. Load the `.ino` file corresponding to the FLEXITIMER version you want to use (FX486 or MX486) from the `code/` folder.
3. Select the **Arduino Nano** board and the appropriate COM port in the IDE.

### Step 4: Upload the Code
Upload the code to your Arduino Nano by clicking the **Upload** button in the Arduino IDE.

## Usage

### Numeric Keypad
The 4x4 numeric keypad allows you to:
- **Enter values** for the clock or timer durations.
- **Start/Stop** timers or the stopwatch.
- **Reset** the system or enter configuration mode.

### Display
The 7-segment display shows:
- **The time** in clock mode.
- **Time remaining** in countdown timer mode.
- **Elapsed time** in stopwatch mode.

### Relay
The NO/NC relay can be used to trigger external events based on the programmed timing (e.g., triggering an alarm or activating a device).

## Wiring Diagrams and Documentation
Detailed wiring diagrams for both the FX486 and MX486, as well as an assembly guide, are available in the `docs/` folder.

- **Complete Assembly Guide**: [assembly_guide.pdf](docs/assembly_guide.pdf)
- **Wiring Diagram**: [wiring_diagram.png](docs/wiring_diagram.png)

## Contributing
We welcome contributions to improve FLEXITIMER. If you wish to add features, fix bugs, or improve the documentation, feel free to fork this repository and submit a pull request.

## License
This project is licensed under the **MIT License**. For more information, see the [LICENSE](LICENSE) file.

## Contact
For any questions or assistance, please contact us at:
- **Website**: [www.foxtek.eu](http://www.foxtek.eu)
- **Email**: foxtek@gmx.com
