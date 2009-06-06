
# Author: Nicolas GUILLAUME <ng@ngsoft-fr.com>

#FCPU=8000000UL
FCPU=3686400
MMCU=atmega8
PART=m8
PROGRAMMER=avr911
PORT=/dev/ttyUSB0
DUDEFLAGS=-E noreset

OPT=-DFAT_TESTING_ONLY

CC=avr-gcc

CFLAGS=-W -Wall -Os -Wno-unused -I. -I.. -mmcu=$(MMCU) -DF_CPU=$(FCPU) $(OPT)
CFLAGS += -gdwarf-2 -std=gnu99  -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

LDFLAGS=
LDFLAGS +=  -Wl,-Map=SD_Card.map


SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)

TARGET=A.hex
EEP=A.eep

HEX_FLASH_FLAGS = -R.eeprom

HEX_EEPROM_FLAGS = -j .eeprom
#HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
#HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings

all: $(TARGET) $(EEP)

FAT32.o: FAT32.c
SD_main.o: SD_main.c
SD_routines.o: SD_routines.c
SPI_routines.o: SPI_routines.c
UART_routines.o: UART_routines.c


$(TARGET): a.out
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS) a.out $(TARGET)

$(EEP): a.out
	avr-objcopy -O ihex $(HEX_EEPROM_FLAGS) a.out $(EEP)

a.out: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o a.out

.PHONY: clean flash

clean:
	@rm -f $(OBJS)  *~ core *.core core.* *.tmp a.out dep/*

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

flash: $(TARGET) $(EEP)
	avrdude -c $(PROGRAMMER) -p $(PART) -P $(PORT)  -V -U flash:w:$(TARGET) -U eeprom:w:$(EEP)  $(DUDEFLAGS)


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
