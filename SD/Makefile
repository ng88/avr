
# Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>

FCPU=8000000UL
MMCU=atmega8
PART=m8
PROGRAMMER=avr911
PORT=/dev/ttyUSB0
DUDEFLAGS=-E noreset

OPT=-DFAT_TESTING_ONLY

CC=avr-gcc
CFLAGS=-W -Wall -Os -Wno-unused -I. -I.. -mmcu=$(MMCU) -DF_CPU=$(FCPU) $(OPT)
LDFLAGS=

SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)

TARGET=A.hex

all: $(TARGET)

FAT32.o: FAT32.c
SD_main.o: SD_main.c
SD_routines.o: SD_routines.c
SPI_routines.o: SPI_routines.c
UART_routines.o: UART_routines.c


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

