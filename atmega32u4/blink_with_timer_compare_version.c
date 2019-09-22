#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

#define FOREVER while (1)
#define BLINK_DELAY 2000
#define uint unsigned int

static inline void
set_pin16_to_output()
{
  DDRB = _BV(PORTB2); // pin 16
}

static inline void
toggle_led()
{
    PORTB ^= _BV(PORTB2);
}

static uint overflow_counter = 0;

static inline void
setup_clock()
{
  OCR0A = 156;
  TIMSK0 = _BV(OCIE0A);
  TCCR0A = _BV(WGM01);
}

static inline void
start_clock()
{
  sei();
  TCCR0B = _BV(CS02) | _BV(CS00);

}

static void
setup()
{
  setup_clock();
  set_pin16_to_output();
  start_clock();
}

int main()
{
  setup();

  FOREVER
  {
    /* toggle_led(); */
    /* _delay_ms(BLINK_DELAY); */
  }
}

ISR(TIMER0_COMPA_vect)
{
  overflow_counter++;
  if (overflow_counter == 100)
    {
      toggle_led();
      overflow_counter = 0;
    }
}
