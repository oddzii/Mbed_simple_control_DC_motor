# Mbed_simple_control_DC_motor

the following project is required Motor.h library.

You can download this from the Github repository in Motor directory.

A program that controls motor speed using PWM and read encoder. Adjust the speed using keystroke through the terminal (The speed of the motor as a normalised value between -255 and 225)

```
 -255 Counterclockwise
    0 No rotate
  255 Clockwise
```
And You can pause and change direction just push USER_BUTTON (PC_13).

The encoder start count form 0 to 32767 (Clockwise) when runout increase from -32767.

In the same. start count form 0 to -32767 (Counterclockwise) when runout decrease from 32767.

# System Components
1. NucleoF411RE
2. Motor Driver L298N
3. DC Motor with encoder
4. Breadboard (If any)
5. Jumper wire

# Connecting
![Sketch](https://user-images.githubusercontent.com/68624655/107952701-ad833200-6fcc-11eb-8caf-dc315597ef1a.png)
