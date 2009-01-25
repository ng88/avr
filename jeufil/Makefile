
FCPU=3686400
#FCPU=8000000
MMCU=atmega8
PART=m8
PROGRAMMER=avr910
PORT=/dev/ttyUSB0
DUDEFLAGS=

all: A.hex

A.hex: main.c local_pin_config.h
	avr-gcc -W -Wall  -Os  -mmcu=$(MMCU) main.c -I.. ../buzzer/buzzer.c  -DF_CPU=$(FCPU)
	avr-objcopy -O ihex -R .eeprom a.out A.hex
	rm a.out

flash: A.hex
	avrdude -c $(PROGRAMMER) -p $(PART) -P $(PORT)  -V -U flash:w:A.hex $(DUDEFLAGS)



.PHONY: all flash
