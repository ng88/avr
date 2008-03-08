all:
	avr-gcc -W -Wall  -Os  -mmcu=atmega8  lcd.c timer_lcd.c
	avr-objcopy -O ihex -R .eeprom a.out A.hex
	rm a.out
	avrdude -c sp12 -p m8 -P /dev/parport0  -V -U flash:w:A.hex
