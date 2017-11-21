CC = avr-gcc -Werror -mmcu=atmega328p -Os -std=c99 -I./lib -I./inc


all: 

build: clear compile upload
	
clear:
	rm -rf bin
	mkdir bin

compile:
	$(CC) -c src/*.c
	#$(CC) -c lib/*.c
	#$(CC) -o main.elf main.o writer.o eeprom_buffer.o
	$(CC) -c lib/time.c
	$(CC) -c lib/non_blocking_delay.c
	$(CC) -c lib/writer.c
	$(CC) -c lib/eeprom_buffer.c
	$(CC) -c lib/uart.c
	$(CC) -c lib/max7219.c
	
	$(CC) -o main.elf main.o time.o non_blocking_delay.o writer.o sound.o eeprom_buffer.o led_matrix.o uart.o max7219.o
	mv *.o bin/
	mv *.elf bin/

run:
	./main
	
upload:
	#sudo avrdude -c stk200 -p m8 -U flash:w:bin/main.elf
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 57600 -U flash:w:bin/main.elf
	
ee:
	sudo avrdude -c stk200 -p m8 -U eeprom:r:eeprom.hex:i
	objcopy -I ihex eeprom.hex -O binary eeprom.txt
	echo '\n' >> eeprom.txt
	cat eeprom.txt
	rm -f eeprom.hex eeprom.txt
	