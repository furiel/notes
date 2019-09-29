#define F_CPU 16000000
#define bool unsigned char
#define TRUE 1
#define FALSE 0

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define FOREVER while (1)
static volatile bool debouncing;

static void
toggle_led()
{
  PORTB ^= _BV(PORTB2);
}

static void
setup_led()
{
  DDRB = _BV(PORTB2); // pin 16
}

static void
setup_int1()
{
  // pin2
  PORTD |= _BV(PORTD1); // Enabling pullup helps debouncing
  // EICRA remains zero : low level
  EIMSK |= _BV(INT1);
}

int main()
{
  USBCON = 0;

  setup_led();
  toggle_led();

  setup_int1();

  sei();

  FOREVER {
    if (debouncing)
      {
        cli();
        debouncing = FALSE;
        _delay_ms(200);
        sei();
      }

  }
}

ISR(INT1_vect)
{
  toggle_led();
  debouncing = TRUE;
}
