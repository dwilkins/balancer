## Process this file with automake to produce Makefile.in
bin_PROGRAMS=balancer
MCU=atmega328p
F_CPU=-DF_CPU=16000000
ARDUINO_VERSION=-DARDUINO=105
ARDUINO_INSTALL=/usr/share/arduino/hardware/arduino
ARDUINO_CORES=$(ARDUINO_INSTALL)/cores/arduino
ARDUINO_VARIANTS=$(ARDUINO_INSTALL)/variants/standard
ARDUINO_INCLUDE_PATH=-I$(ARDUINO_CORES) -I$(ARDUINO_VARIANTS)
nodist_balancer_SOURCES=src/main.cpp src/BalanceWheel.cpp src/Axel.cpp src/TaskScheduler.cpp src/Task.cpp src/BalancerTest.cpp
balancer_CFLAGS=-Wall $(ARDUINO_INCLUDE_PATH) -gstabs -mmcu=$(MCU) $(F_CPU) $(ARDUINO_VERSION) -D__AVR_LIBC_DEPRECATED_ENABLE__
balancer_CXXFLAGS=-Wall $(ARDUINO_INCLUDE_PATH) -mmcu=$(MCU) $(F_CPU) $(ARDUINO_VERSION) -D__AVR_LIBC_DEPRECATED_ENABLE__
balancer_LDFLAGS=-L. -lm
balancer_LDADD=-lcore -lm

lib_LIBRARIES=libcore.a
libcore_a_CFLAGS=-Wall $(ARDUINO_INCLUDE_PATH) -gstabs -mmcu=$(MCU) $(F_CPU) $(ARDUINO_VERSION) -D__AVR_LIBC_DEPRECATED_ENABLE__
libcore_a_CXXFLAGS=-Wall $(ARDUINO_INCLUDE_PATH) -mmcu=$(MCU) $(F_CPU) $(ARDUINO_VERSION) -D__AVR_LIBC_DEPRECATED_ENABLE__
libcore_a_SOURCES=/usr/share/arduino/hardware/arduino/cores/arduino/HardwareSerial.cpp /usr/share/arduino/hardware/arduino/cores/arduino/WMath.cpp /usr/share/arduino/hardware/arduino/cores/arduino/WString.cpp /usr/share/arduino/hardware/arduino/cores/arduino/Print.cpp /usr/share/arduino/hardware/arduino/cores/arduino/IPAddress.cpp /usr/share/arduino/hardware/arduino/cores/arduino/wiring.c /usr/share/arduino/hardware/arduino/cores/arduino/wiring_analog.c /usr/share/arduino/hardware/arduino/cores/arduino/wiring_digital.c /usr/share/arduino/hardware/arduino/cores/arduino/wiring_pulse.c /usr/share/arduino/hardware/arduino/cores/arduino/wiring_shift.c /usr/share/arduino/hardware/arduino/cores/arduino/WInterrupts.c


AM_LDFLAGS=
AM_CXXFLAGS=-g
AM_CFLAGS=-g
VPATH=/usr/share/arduino/hardware/arduino/cores/arduino

AVRDUDE_PORT=/dev/ttyUSB0
AVRDUDE_PROGRAMMER = arduino
MY_AVRDUDE=~/bin/avrdude
UPLOAD_RATE = 57600
FORMAT=ihex

AVRDUDE_WRITE_FLASH = -U flash:w:$(bin_PROGRAMS).hex
# AVRDUDE_FLAGS = -q -D -C/etc/avrdude/avrdude.conf -p$(MCU) -P$(AVRDUDE_PORT) -c$(AVRDUDE_PROGRAMMER) -b$(UPLOAD_RATE)
AVRDUDE_FLAGS = -vv -D -C/home/dwilkins/project/avrdude-6.0.1/avrdude.conf -p$(MCU) -P$(AVRDUDE_PORT) -c$(AVRDUDE_PROGRAMMER) -b$(UPLOAD_RATE)

.PHONY: upload
upload:
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $(bin_PROGRAMS) $(bin_PROGRAMS).hex
	$(MY_AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)
