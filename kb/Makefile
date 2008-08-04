
# Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>

FCPU=3686400
MMCU=atmega8
PART=m8
PROGRAMMER=sp12
PORT=/dev/parport0
DUDEFLAGS=-E noreset


ifdef KB_KEYMAP
	KM=-DKB_KEYMAP_$(KB_KEYMAP)
else
	KM=-DKB_KEYMAP_AZERTY
endif

CC=avr-gcc
CFLAGS=-W -Wall -Os -Wno-unused -I. -I.. -mmcu=$(MMCU) -DF_CPU=$(FCPU) $(KM)
LDFLAGS=

SRC=main.c kb.c ../serial/serial.c
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

