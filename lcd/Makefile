all:
	avr-gcc -W -Wall  -Os  -mmcu=atmega8  lcd.c progress2.c
	avr-objcopy -O ihex -R .eeprom a.out A.hex
	rm a.out
	avrdude -c avr911 -p m8 -P /dev/ttyUSB0  -V -U flash:w:A.hex
