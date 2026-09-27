# Bare-Metal ATmega328P Traffic Light Controller

A register-level Embedded C implementation of a traffic light system with an interrupt-driven pedestrian crossing on the ATmega328P microcontroller.

## Technical Highlights
* **Direct Register Control:** Utilizes `DDRB`, `PORTB`, `DDRD`, and `PORTD` registers for GPIO operations without Arduino framework abstractions.
* **Non-Blocking System Tick:** Configures **Timer0 in CTC mode** (`OCR0A = 249`, 64 prescaler) to generate a precise 1 ms tick count.
* **Hardware Interrupts:** Implements asynchronous pedestrian crossing requests via **INT0 (Digital Pin 2)** on a rising edge trigger.
* **Finite State Machine (FSM):** Handles non-blocking state transitions across `STATE_GREEN`, `STATE_YELLOW`, `STATE_RED`, and `STATE_PEDESTRIAN`.

## Hardware Pin Mapping
| Component | Pin / Register | Description |
| :--- | :--- | :--- |
| Red LED | Pin 12 (`PB4`) | Main Traffic Red Light |
| Yellow LED | Pin 11 (`PB3`) | Main Traffic Yellow Light |
| Green LED | Pin 10 (`PB2`) | Main Traffic Green Light |
| Pedestrian LED | Pin 8 (`PB0`) | Pedestrian Walk Indicator (Cyan/White) |
| Push Button | Pin 2 (`PD2` / `INT0`) | External Interrupt Input (Active HIGH with 10kΩ Pull-down) |

## Simulation Demo
![Traffic Light Simulation](docs/simulation.gif)

## How to Run in Wokwi
1. Open [Wokwi AVR Simulator](https://wokwi.com).
2. Load the contents of `src/main.c` into the code tab.
3. Load `diagram.json` into the layout configuration.
4. Click **Play** to start the simulation.