# arduino-brainf

### Simple Arduino-Brainf*ck - interpreter / visualizer

128x32px OLED SCREEN shows current char (ASCII_value -> String) being printed

Fancy 8+1 LED's show the current binary value of the current "serial.read(char);"
blue led for "clock"-speed visualization

It's useless, but fun and beautiful at the same time

current Maximum_array length = 230 ("""Pointer_positions""")

**Notice: due to some Arduino limitations, you can't enter BF_instructions longer than 32 Chars in the Serial Monitor, since additional ones will simply be ingnored. **

> supported operations / BF_instructions : "><.,[]+-" 
  
(other characters ignored and seen as comments except the ',' instruction explicitly calls for the next char)

**The ' , ' (comma) instruction isn't able to receive live-user-input from the USB-Keyboard and instead just reads the following Char in the serial console as its
correspondant ascii_integer value.**

_______________________

> Example   ' , F . [ - ] ' 

echo's the Letter F on the OLED Screen and decreases the Value in it's array location back to Zero
