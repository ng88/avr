
# Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>

FCPU=8000000
#3686400
MMCU=atmega8
PART=m8
PROGRAMMER=avr911
PORT=/dev/ttyUSB0
DUDEFLAGS=-E noreset

CC=avr-gcc
CFLAGS=-W -Wall -Os -Wno-unused -I. -I.. -mmcu=$(MMCU) -DF_CPU=$(FCPU)
LDFLAGS=

SRC=main.c ../serial/serial.c
OBJS=$(SRC:.c=.o)

TARGET=A.hex

all: $(TARGET)

$(TARGET): a.out
	avr-objcopy -O ihex -R .eeprom a.out A.hex

a.out: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o a.out

.PHONY: clean flash

clean:
	@rm -f $(OBJS)  *~ core *.core core.* *.tmp a.out

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

flash: $(TARGET)
	avrdude -c $(PROGRAMMER) -p $(PART) -P $(PORT)  -V -U flash:w:$(TARGET) $(DUDEFLAGS)

