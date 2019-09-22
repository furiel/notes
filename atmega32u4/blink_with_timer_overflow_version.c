#define F_CPU 16000000
#include <avr/io.h>
//#include <util/delay.h>
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
enable_timer_overflow_interrupt()
{
  TIMSK0 = _BV(TOIE0);
}

static inline void
select_timer_normal_mode()
{
  TCCR0A = 0;
}

static inline void
setup_clock()
{
  select_timer_normal_mode();
  enable_timer_overflow_interrupt();
}

static inline void
select_1024_prescaler()
{
  TCCR0B = _BV(CS02) | _BV(CS00);
}

static inline void
start_clock()
{
  sei();
  select_1024_prescaler();
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
  }
}

ISR(TIMER0_OVF_vect)
{
  overflow_counter++;
  if (overflow_counter == 61)
    {
      toggle_led();
      overflow_counter = 0;
    }
}
