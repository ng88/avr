
# Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>

MMCU=atmega8
PART=m8
PROGRAMMER=sp12
PORT=/dev/parport0
DUDEFLAGS=-E noreset

CC=avr-gcc
CFLAGS=-W -Wall -Os -Wno-unused -I. -I..  -mmcu=$(MMCU)
LDFLAGS=

SRC=main.c ../lcd/lcd.c kb.c
OBJS=$(SRC:.c=.o)

TARGET=A.hex

all: $(TARGET)

kb.o: pindefs.h kb.h scancodes.h
main.o: kb.h

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

