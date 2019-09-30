#define F_CPU 16000000
#define BAUD 9600
#define FOREVER while (1)
#define uchar unsigned char

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define UBRR_VALUE ((F_CPU/16)/BAUD - 1)

static void
setup_uart()
{
 UBRR1H = (uchar)(UBRR_VALUE >> 8);
 UBRR1L = (uchar)UBRR_VALUE;

  UCSR1B = _BV(RXEN1) | _BV(TXEN1);
  UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); // 8 bit
}

static void
wait_for_empty_buffer()
{
  while (!(UCSR1A & _BV(UDRE1)));
}

static void
uart_write_char(const char c)
{
  wait_for_empty_buffer();
  UDR1 = c;
}

static void
uart_write(const char *str)
{
  for (; *str; str++)
    {
      if (*str == '\n')
        {
          // Serial terminal does not carriage return automatically
          // even in linux (tested with screen)
          uart_write_char('\r');
          uart_write_char('\n');
        }
      else
        {
          uart_write_char(*str);
        }
    }
}

static char
uart_read_char()
{
  /* Wait for data to be received */
  while (!(UCSR1A & (1<<RXC1)));

  return UDR1;
}

static void
echo_char(const char c)
{
  char text[300];
  sprintf(text, "Received: 0x%x (%c)\n", c, c);
  uart_write(text);
}

int main()
{
  setup_uart();

  uart_write("Enter command: ");

  FOREVER {
    echo_char(uart_read_char());
  }
}
