# DoorLocking
Controlling Door locking using PIC18f452 </br>
MPLAB project</br>
</br>
In Activated Mode: 
- reads PIR sensor if motion detected open the door for 10s
- while closing the door a buzzer is fired
- if emergency mode is activated it opens the doors immediately until reset is activated
</br>
In DeActivated Mode:
- Gate is opened
- Emergency can't be activated
<\br>
Change between modes by pressing on system button for 3s and entering the pass code defined in the code (look main.c).
</br>
Reset the emergency state by holding the reset button for 8s and entering the pass code.
