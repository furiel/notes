CC:=avr-gcc
OBJCOPY:=avr-objcopy
AVRDUDE:=avrdude
MCU=atmega32u4
PROGRAMMER=avr109
USBDEV:=/dev/ttyACM0

all: simple_blink.hex blink_with_timer_overflow_version.hex blink_with_timer_compare_version.hex led_with_pwm.hex adc_potmeter_led.hex blink_with_ext_interrupt.hex

reset:
	@gpio -g mode 27 out
	@gpio -g write 27 1
	@sleep 0.1
	@gpio -g toggle 27
	@sleep 0.1
	@gpio -g write 27 1
	@sleep 0.1
	@gpio -g toggle 27
	@sleep 0.1
	@gpio -g toggle 27
	@sleep 1

flash-%: % reset
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -U flash:w:$<:i -D -b57600 -P $(USBDEV) -v

%.bin: %.c
	$(CC) -Wall -g -Os -mmcu=$(MCU) -o $@ $<

%.hex: %.bin
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

.PHONY = reset
