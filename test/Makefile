
FCPU=3686400
#FCPU=8000000
MMCU=atmega8
PART=m8
PROGRAMMER=avr910
PORT=/dev/ttyUSB0
DUDEFLAGS=

all: compile

compile:
	avr-gcc -W -Wall  -Os  -mmcu=$(MMCU) buzzer*.c   -DF_CPU=$(FCPU)
	avr-objcopy -O ihex -R .eeprom a.out A.hex
	rm a.out

flash: compile
	avrdude -c $(PROGRAMMER) -p $(PART) -P $(PORT)  -V -U flash:w:A.hex $(DUDEFLAGS)



.PHONY: compile all flash
