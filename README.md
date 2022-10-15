# Syringe pump and fraction collector based on stepper motor

![stepper](https://github.com/alexandervolikov/stepper/blob/main/img/stepper.jpg)

Initially conceived as a syringe pump, the functionality has been further expanded for use as a fraction collector.

Details:

- stepper motor nema 17hs4401s
- arduino nano + drv8825 driver
- power supply 12 V, 2.4 A
- screw gear
- structural profile 2040, steel shaft 8 mm
- bearing 8 mm linear and radial
- coupling rigid 5x8 mm
- 3d printed parts

drawings in the scheme folder, part models in the 3d_print folder, wiring diagram in hardware, firmware for arduino in firmware, control program code for a computer in gui

The GUI for the computer is based on a python script, implemented using the [PySimpleGUI] library (https://github.com/PySimpleGUI/PySimpleGUI)

![gui](https://github.com/alexandervolikov/stepper/blob/main/img/gui.png)

Need to enter

- the name of the COM port to which the connection is made
- speed from 1 to 1000
- step (1mm - 400 steps)
- how many steps to take
- delay between steps in milliseconds

Press Start

After that, the program will start, it will also be stored in the EEPROM memory of the controller. If you connect the controller to power, the recorded program will start, thus, the computer does not have to be used directly during operation.

The circuit and the program do not have foolproofing, if you enter it incorrectly, for example, the step length is greater than the device can physically do, something may break in the device

In releases - compiled with pyinstaller versions for windows and mac os

GNU General Public License v3.0