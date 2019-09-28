#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FOREVER while (1)

static void
fix_bootloader_bug()
{
  /* It seems usb generates interrupts that break the code after
  sei(), unless USB_GEN_vect is defined.
  Removing and reattaching power also fixes problem. Still, let's just disable USB.
  Source: https://stackoverflow.com/questions/40214361/atmega32u4-enabling-interrupts-hangs */
  USBCON = 0;
}

static void
setup_fpwm()
{
  // PB5 : pin9, OC1A
  DDRB = _BV(PORTB5);
  TIMSK1 = _BV(TOIE1); // Enables interrupt for timer1
  TCCR1A = _BV(COM1A1) | _BV(WGM10); // Together with TCCR1B, these set FPWM.
  TCCR1B = _BV(WGM12);
}

static void
start_fpwm()
{
  TCCR1B |= _BV(CS10); // CS10 sets no prescaler.
}

static void
setup_adc()
{
  ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // choose prescaler
  ADMUX |= _BV(REFS0); // choose reference: V_cc
  ADMUX |= _BV(ADLAR); // choose adjustment: left

  // choose channel: pin8 -> PB4 == ADC11
  ADMUX |= _BV(MUX0) | _BV(MUX1);
  ADCSRB |= _BV(MUX5); // Theoretically should couple with ADMUX.

  ADCSRA |= _BV(ADIE); // enable interrupt
  ADCSRA |= _BV(ADEN); // Enable conversion
  DIDR2 |= _BV(ADC11D); // Disable digital read
}

static void
start_adc_conversion()
{
  ADCSRA |= _BV(ADSC);
}

static void
setup()
{
  setup_adc();
  setup_fpwm();
  sei();
  start_fpwm();
  start_adc_conversion();
}

static unsigned char dutyCycle;

int main()
{
  fix_bootloader_bug();

  setup();

  FOREVER {
    /* start_adc_conversion(); */
    /* _delay_ms(200); */
    /* OCR1AL = ADCH; */
  }

  return 0;
}

ISR(TIMER1_OVF_vect)
{
  OCR1AL = dutyCycle;
}

ISR(ADC_vect)
{
  dutyCycle = ADCH;
  start_adc_conversion();
}
