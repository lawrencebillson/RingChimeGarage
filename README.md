# RingChimeGarage
Ring doesn't have a method of activating doors, etc.

To fix this, we added a Ring Chime. This can be paired with another Ring alert, or used with the 'Test Tone' menu option.

This project uses a little Arduino code to monitor the I2S lines within the chime. If it counts sufficient pulses, it is reasonably sure that the chime is ringing. From there, it sends a pulse, via an opto isolator, to the door controller.


Wiring details are in the .ino file.
