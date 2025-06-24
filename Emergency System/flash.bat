@echo off
C:\"Program Files (x86)\Labcenter Electronics\Proteus 8.13 Professional\Tools\AVRDUDE\avrdude.exe" -C C:/AVR8051.conf -c stk500v1 -P COM5 -p 89s52 -b 19200 -U flash:w:"C:\Users\Name\Desktop\Emergency System\Objects\Emergency System.hex":a
pause