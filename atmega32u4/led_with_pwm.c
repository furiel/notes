#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FOREVER while (1)

static inline void
fix_bootloader_bug()
{
  /* It seems usb generates interrupts that break the code after
  sei(), unless USB_GEN_vect is defined.
  Removing and reattaching power also fixes problem. Still, let's just disable USB.
  Source: https://stackoverflow.com/questions/40214361/atmega32u4-enabling-interrupts-hangs */
  USBCON = 0;
}

static inline void
setup_fpwm()
{
  // PB5 : pin9, OC1A
  DDRB = _BV(PORTB5);
  TIMSK1 = _BV(TOIE1); // Enables interrupt for timer1
  TCCR1A = _BV(COM1A1) | _BV(WGM10); // Together with TCCR1B, these set FPWM.
  sei();
  TCCR1B = _BV(WGM12) | _BV(CS10); // Together with TCCR1A, WGM12 sets FPWM. CS10 sets no prescaler.
}

static inline void
setup()
{
  setup_fpwm();
}

static unsigned char dutyCycle;

int main()
{
  fix_bootloader_bug();

  setup();

  FOREVER
    {
      _delay_ms(100);
      dutyCycle += 16;
    }

  return 0;
}

ISR(TIMER1_OVF_vect)
{
  OCR1AL = dutyCycle;
}
