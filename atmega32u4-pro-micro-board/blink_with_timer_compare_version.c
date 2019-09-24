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

static uint compare_event = 0;

static inline void
enable_timer0_compare_interrupt()
{
  TIMSK0 = _BV(OCIE0A);
}

static inline void
set_timer0_compare_mode()
{
  TCCR0A = _BV(WGM01);
}

static inline void
set_compare_value()
{
  OCR0A = 156; // This takes around 0.01s time.
}

static inline void
setup_clock()
{
  set_compare_value();
  enable_timer0_compare_interrupt();
  set_timer0_compare_mode();
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

static inline void
fix_bootloader_bug()
{
  /* It seems usb generates interrupts that break the code after
  sei(), unless USB_GEN_vect is defined.
  Removing and reattaching power also fixes problem. Still, let's just disable USB.
  Source: https://stackoverflow.com/questions/40214361/atmega32u4-enabling-interrupts-hangs */
  USBCON = 0;
}

int main()
{
  fix_bootloader_bug();

  setup();

  FOREVER
  {
  }
}

ISR(TIMER0_COMPA_vect)
{
  compare_event++;
  if (compare_event == 100)
    {
      toggle_led();
      compare_event = 0;
    }
}
