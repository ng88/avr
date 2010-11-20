
FCPU=3686400
#FCPU=8000000
MMCU=atmega8
PART=m8
PROGRAMMER=avr910
PORT=/dev/ttyUSB0
DUDEFLAGS=
USART_BAUD_RATE=4800

all: A.hex

A.hex: main.c local_pin_config.h
	avr-gcc -W -Wall  -Os  -mmcu=$(MMCU) main.c ../../serial/serial.c -I.. -I../.. -DF_CPU=$(FCPU) -DUSART_BAUD_RATE=$(USART_BAUD_RATE)
	avr-objcopy -O ihex -R .eeprom a.out A.hex
	rm a.out

flash: A.hex
	avrdude -c $(PROGRAMMER) -p $(PART) -P $(PORT)  -V -U flash:w:A.hex $(DUDEFLAGS)


clean:
	rm A.hex *.o

.PHONY: all flash
