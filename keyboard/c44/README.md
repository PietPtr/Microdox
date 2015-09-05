Custom spilt keyboard firmware
======


Flashing
--------

Before you go to flash the program memory for the first time, you will need to
EEPROM for the left and right halves. The EEPROM is used to store whether the
half is left handed or right handed. This makes it so that the same firmware
file will run on both hands instead of having to flash left and right handed
versions of the firmware to each half. To flash the EEPROM file for the left
half run:
```
make eeprom-left
```
and similarly for right half
```
make eeprom-right
```

After you have flashed the EEPROM for the first time, you then need to program
the flash memory:
```
make program
```
Note that you need to program both halves, but you have the option of using
different keymaps for each half. You could program the left half with a QWERTY
layout and the right half with a Colemak layout. Then if you connect the left
half to a computer by USB the keyboard will use QWERTY and Colemak when the
right half is connected.


