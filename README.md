# Arduino Electromagnetic Accelerator

## Overview
This project implements a small-scale particle accelerator using Arduino-controlled electromagnets made from copper wire coils. The system sequentially activates electromagnets to accelerate a ferromagnetic object through a tube or track.

## Components
- Arduino board (Uno/Nano recommended)
- Copper wire (enameled, 24-28 AWG)
- Multiple MOSFETs or transistors (suitable for your coil current)
- Diodes (1N4001 or similar for back-EMF protection)
- Power supply (12-24V depending on coil requirements)
- Ferromagnetic projectiles (small steel balls/bearings)
- Non-magnetic tube for the acceleration track
- Hall effect sensors or IR sensors for position detection
- Resistors (various, as needed for circuit)
- Breadboard/PCB
- Jumper wires

## Circuit Setup
1. Wind multiple coils using copper wire (100-200 turns each)
2. Connect each coil to a MOSFET/transistor controlled by an Arduino output pin
3. Place protective diodes across each coil to prevent back-EMF damage
4. Position sensors between coils to detect projectile movement
5. Connect the circuit according to the schematic in `/docs/circuit.png`

## How It Works
The accelerator uses precisely timed electromagnetic pulses to propel a ferromagnetic object. As the object approaches each coil, the Arduino activates the electromagnet, pulling the object toward it. Just as the object reaches the center of the coil, power is cut, allowing the object to continue its forward momentum without being pulled back. This sequence repeats through multiple stages, progressively increasing velocity.

## Usage
1. Place the ferromagnetic projectile at the starting position
2. Power on the system
3. Use the serial monitor to view acceleration data and timing
4. Press the start button to begin the acceleration sequence
5. Adjust timing parameters in the code to optimize acceleration

## Safety Precautions
- Never touch the coils while the system is powered
- Be aware of the projectile's exit path and velocity
- Use protective eyewear during operation
- Monitor coil temperature to prevent overheating

## Future Improvements
- Add velocity measurement capabilities
- Implement PID control for adaptive timing
- Create a multi-stage design for higher acceleration
- Add wireless control and monitoring

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.