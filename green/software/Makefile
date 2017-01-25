CC=avr-gcc
AS=$(CC)
LD=$(CC)

CPU=atmega328p
AVRDUDE=avrdude -C"C:\Program Files (x86)\Arduino\hardware/tools/avr/etc/avrdude.conf"  -p $(CPU) -P usb -c usbasp
CFLAGS=-Wall -mmcu=$(CPU) -Os -DF_CPU=8000000L
LDFLAGS=-mmcu=$(CPU) -Wl,-Map=mapfile.map

OBJS=supergun.o
PROG=supergun

# Fuse Settings
HF=0xE2
LF=0xD9

all: $(PROG).hex

clean:
	rm -f $(PROG).elf $(PROG).hex mapfile.map $(OBJS)

$(PROG).elf: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(PROG).elf

$(PROG).hex: $(PROG).elf
	avr-objcopy -j .data -j .text -O ihex $(PROG).elf $(PROG).hex
	avr-size $(PROG).elf

flash: $(PROG).hex
	$(AVRDUDE) -Uflash:w:$< -B 5.0 -e

fuse:
	$(AVRDUDE) -e -Uhfuse:w:$(HF):m -Ulfuse:w:$(LF):m -B 20.0 -F

erase:
	$(AVRDUDE) -B 10.0 -e

%.o: %.S
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

