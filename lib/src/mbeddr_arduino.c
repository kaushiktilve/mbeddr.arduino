#include <avr/io.h>


#if defined (__AVR_ATmega328__)
#define 	UCSRA 	UCSR0A
#define 	UCSRB 	UCSR0B
#define 	UCSRC 	UCSR0C
#define 	UBRRH 	UBRR0H
#define 	UBRRL 	UBRR0L
#define 	UDRE 	UDRE0
#define 	UDR 	UDR0
#define 	RXC 	RXC0
#endif

void ADC_Init(void) {

  uint16_t result;
  //set ADCref to AVcc
  ADMUX = (1<<REFS0);

  //set ADC prescale to 128
  ADCSRA = (1<<ADPS1) | (1<<ADPS0);
  ADCSRA |= (1<<ADEN);                  // enable ADC

  ADCSRA |= (1<<ADSC);                  // start a dummy conversion
  while (ADCSRA & (1<<ADSC) ) {         // because the first conversion after
  }                                     // after set up is invalid

  result = ADCW;
}

uint16_t ADC_Read( uint8_t channel )
{
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
  ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"
  while (ADCSRA & (1<<ADSC) ) {   // auf Abschluss der Konvertierung warten
  }
  return ADCW;                    // ADC auslesen und zurückgeben
}


int uart_putc(unsigned char c)
{
     while(!(UCSRA & (1<<UDRE)));
      UDR = c;
    return 0;
}

void uart_write(char* s)
{
  while(*s)
  {
    uart_putc(*s);
    s++;
  }
}

void uart_write_byte(uint8_t d)
{
       while(!(UCSRA & (1<<UDRE)));
       UDR = d;

}

unsigned char uart_receive(void){

 while(!(UCSRA & (1<<RXC)));
 return UDR;

}
