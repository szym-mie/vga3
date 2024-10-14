#ifndef _M88_H_
#define _M88_H_

#include "io.h"

#define UDR0 IO_REG(0xC6) // reference page 201


#define UBRR0H IO_REG(0xC5) // reference page 205


#define UBRR0L IO_REG(0xC4) // reference page 205


#define UCSR0C IO_REG(0xC2) // reference page 203/218

#define UMSEL01 (1<<7)
#define UMSEL00 (1<<6)
#define UPM01 (1<<5)
#define UPM00 (1<<4)
#define USBS0 (1<<3)
#define UCSZ01 (1<<2)
#define UDORD0 (1<<2)
#define UCSZ00 (1<<1)
#define UCPHA0 (1<<1)
#define UCPOL0 (1<<0)

#define UCSR0B IO_REG(0xC1) // reference page 202

#define RXCIE0 (1<<7)
#define TXCIE0 (1<<6)
#define UDRIE0 (1<<5)
#define RXEN0 (1<<4)
#define TXEN0 (1<<3)
#define UCSZ02 (1<<2)
#define RXB80 (1<<1)
#define TXB80 (1<<0)

#define UCSR0A IO_REG(0xC0) // reference page 201

#define RXC0 (1<<7)
#define TXC0 (1<<6)
#define UDRE0 (1<<5)
#define FE0 (1<<4)
#define DOR0 (1<<3)
#define UPE0 (1<<2)
#define U2X0 (1<<1)
#define MPCM0 (1<<0)

#define TWAMR IO_REG(0xBD) // reference page 251

#define TWAM6 (1<<7)
#define TWAM5 (1<<6)
#define TWAM4 (1<<5)
#define TWAM3 (1<<4)
#define TWAM2 (1<<3)
#define TWAM1 (1<<2)
#define TWAM0 (1<<1)

#define TWCR IO_REG(0xBC) // reference page 248

#define TWINT (1<<7)
#define TWEA (1<<6)
#define TWSTA (1<<5)
#define TWSTO (1<<4)
#define TWWC (1<<3)
#define TWEN (1<<2)
#define TWIE (1<<0)

#define TWDR IO_REG(0xBB) // reference page 250


#define TWAR IO_REG(0xBA) // reference page 251

#define TWA6 (1<<7)
#define TWA5 (1<<6)
#define TWA4 (1<<5)
#define TWA3 (1<<4)
#define TWA2 (1<<3)
#define TWA1 (1<<2)
#define TWA0 (1<<1)
#define TWGCE (1<<0)

#define TWSR IO_REG(0xB9) // reference page 250

#define TWS7 (1<<7)
#define TWS6 (1<<6)
#define TWS5 (1<<5)
#define TWS4 (1<<4)
#define TWS3 (1<<3)
#define TWPS1 (1<<1)
#define TWPS0 (1<<0)

#define TWBR IO_REG(0xB8) // reference page 248


#define ASSR IO_REG(0xB6) // reference page 170

#define EXCLK (1<<6)
#define AS2 (1<<5)
#define TCN2UB (1<<4)
#define OCR2AUB (1<<3)
#define OCR2BUB (1<<2)
#define TCR2AUB (1<<1)
#define TCR2BUB (1<<0)

#define OCR2B IO_REG(0xB4) // reference page 169


#define OCR2A IO_REG(0xB3) // reference page 168


#define TCNT2 IO_REG(0xB2) // reference page 168


#define TCCR2B IO_REG(0xB1) // reference page 167

#define FOC2A (1<<7)
#define FOC2B (1<<6)
#define WGM22 (1<<3)
#define CS22 (1<<2)
#define CS21 (1<<1)
#define CS20 (1<<0)

#define TCCR2A IO_REG(0xB0) // reference page 164

#define COM2A1 (1<<7)
#define COM2A0 (1<<6)
#define COM2B1 (1<<5)
#define COM2B0 (1<<4)
#define WGM21 (1<<1)
#define WGM20 (1<<0)

#define OCR1BH IO_REG(0x8B) // reference page 145


#define OCR1BL IO_REG(0x8A) // reference page 145


#define OCR1AH IO_REG(0x89) // reference page 145


#define OCR1AL IO_REG(0x88) // reference page 145


#define ICR1H IO_REG(0x87) // reference page 146


#define ICR1L IO_REG(0x86) // reference page 146


#define TCNT1H IO_REG(0x85) // reference page 145


#define TCNT1L IO_REG(0x84) // reference page 145


#define TCCR1C IO_REG(0x82) // reference page 144

#define FOC1A (1<<7)
#define FOC1B (1<<6)

#define TCCR1B IO_REG(0x81) // reference page 143

#define ICNC1 (1<<7)
#define ICES1 (1<<6)
#define WGM13 (1<<4)
#define WGM12 (1<<3)
#define CS12 (1<<2)
#define CS11 (1<<1)
#define CS10 (1<<0)

#define TCCR1A IO_REG(0x80) // reference page 141

#define COM1A1 (1<<7)
#define COM1A0 (1<<6)
#define COM1B1 (1<<5)
#define COM1B0 (1<<4)
#define WGM11 (1<<1)
#define WGM10 (1<<0)

#define DIDR1 IO_REG(0x7F) // reference page 255

#define AIN1D (1<<1)
#define AIN0D (1<<0)

#define DIDR0 IO_REG(0x7E) // reference page 272

#define ADC5D (1<<5)
#define ADC4D (1<<4)
#define ADC3D (1<<3)
#define ADC2D (1<<2)
#define ADC1D (1<<1)
#define ADC0D (1<<0)

#define ADMUX IO_REG(0x7C) // reference page 268

#define REFS1 (1<<7)
#define REFS0 (1<<6)
#define ADLAR (1<<5)
#define MUX3 (1<<3)
#define MUX2 (1<<2)
#define MUX1 (1<<1)
#define MUX0 (1<<0)

#define ADCSRB IO_REG(0x7B) // reference page 271

#define ACME (1<<6)
#define ADTS2 (1<<2)
#define ADTS1 (1<<1)
#define ADTS0 (1<<0)

#define ADCSRA IO_REG(0x7A) // reference page 269

#define ADEN (1<<7)
#define ADSC (1<<6)
#define ADATE (1<<5)
#define ADIF (1<<4)
#define ADIE (1<<3)
#define ADPS2 (1<<2)
#define ADPS1 (1<<1)
#define ADPS0 (1<<0)

#define ADCH IO_REG(0x79) // reference page 271


#define ADCL IO_REG(0x78) // reference page 271


#define TIMSK2 IO_REG(0x70) // reference page 169

#define OCIE2B (1<<2)
#define OCIE2A (1<<1)
#define TOIE2 (1<<0)

#define TIMSK1 IO_REG(0x6F) // reference page 146

#define ICIE1 (1<<5)
#define OCIE1B (1<<2)
#define OCIE1A (1<<1)
#define TOIE1 (1<<0)

#define TIMSK0 IO_REG(0x6E) // reference page 118

#define OCIE0B (1<<2)
#define OCIE0A (1<<1)
#define TOIE0 (1<<0)

#define PCMSK2 IO_REG(0x6D) // reference page 82

#define PCINT23 (1<<7)
#define PCINT22 (1<<6)
#define PCINT21 (1<<5)
#define PCINT20 (1<<4)
#define PCINT19 (1<<3)
#define PCINT18 (1<<2)
#define PCINT17 (1<<1)
#define PCINT16 (1<<0)

#define PCMSK1 IO_REG(0x6C) // reference page 82

#define PCINT14 (1<<6)
#define PCINT13 (1<<5)
#define PCINT12 (1<<4)
#define PCINT11 (1<<3)
#define PCINT10 (1<<2)
#define PCINT9 (1<<1)
#define PCINT8 (1<<0)

#define PCMSK0 IO_REG(0x6B) // reference page 82

#define PCINT7 (1<<7)
#define PCINT6 (1<<6)
#define PCINT5 (1<<5)
#define PCINT4 (1<<4)
#define PCINT3 (1<<3)
#define PCINT2 (1<<2)
#define PCINT1 (1<<1)
#define PCINT0 (1<<0)

#define EICRA IO_REG(0x69) // reference page 78

#define ISC11 (1<<3)
#define ISC10 (1<<2)
#define ISC01 (1<<1)
#define ISC00 (1<<0)

#define PCICR IO_REG(0x68) // reference page no_ref

#define PCIE2 (1<<2)
#define PCIE1 (1<<1)
#define PCIE0 (1<<0)

#define OSCCAL IO_REG(0x66) // reference page 44


#define PRR IO_REG(0x64) // reference page 48

#define PRTWI (1<<7)
#define PRTIM2 (1<<6)
#define PRTIM0 (1<<5)
#define PRTIM1 (1<<3)
#define PRSPI (1<<2)
#define PRUSART0 (1<<1)
#define PRADC (1<<0)

#define CLKPR IO_REG(0x61) // reference page 44

#define CLKPCE (1<<7)
#define CLKPS3 (1<<3)
#define CLKPS2 (1<<2)
#define CLKPS1 (1<<1)
#define CLKPS0 (1<<0)

#define WDTCSR IO_REG(0x60) // reference page 60

#define WDIF (1<<7)
#define WDIE (1<<6)
#define WDP3 (1<<5)
#define WDCE (1<<4)
#define WDE (1<<3)
#define WDP2 (1<<2)
#define WDP1 (1<<1)
#define WDP0 (1<<0)

#define SREG IO_REG(0x5F) // reference page 18

#define I (1<<7)
#define T (1<<6)
#define H (1<<5)
#define S (1<<4)
#define V (1<<3)
#define N (1<<2)
#define Z (1<<1)
#define C (1<<0)

#define SPH IO_REG(0x5E) // reference page 20


#define SPL IO_REG(0x5D) // reference page 20

#define SP7 (1<<7)
#define SP6 (1<<6)
#define SP5 (1<<5)
#define SP4 (1<<4)
#define SP3 (1<<3)
#define SP2 (1<<2)
#define SP1 (1<<1)
#define SP0 (1<<0)

#define SPMCSR IO_REG(0x57) // reference page 297


#define MCUCR IO_REG(0x55) // reference page no_ref

#define PUD (1<<4)
#define IVSEL (1<<1)
#define IVCE (1<<0)

#define MCUSR IO_REG(0x54) // reference page no_ref

#define WDRF (1<<3)
#define BORF (1<<2)
#define EXTRF (1<<1)
#define PORF (1<<0)

#define SMCR IO_REG(0x53) // reference page 46

#define SM2 (1<<3)
#define SM1 (1<<2)
#define SM0 (1<<1)
#define SE (1<<0)

#define ACSR IO_REG(0x50) // reference page 254

#define ACD (1<<7)
#define ACBG (1<<6)
#define ACO (1<<5)
#define ACI (1<<4)
#define ACIE (1<<3)
#define ACIC (1<<2)
#define ACIS1 (1<<1)
#define ACIS0 (1<<0)

#define SPDR IO_REG(0x4E) // reference page 181


#define SPSR IO_REG(0x4D) // reference page 180

#define SPIF (1<<7)
#define WCOL (1<<6)
#define SPI2X (1<<0)

#define SPCR IO_REG(0x4C) // reference page 179

#define SPIE (1<<7)
#define SPE (1<<6)
#define DORD (1<<5)
#define MSTR (1<<4)
#define CPOL (1<<3)
#define CPHA (1<<2)
#define SPR1 (1<<1)
#define SPR0 (1<<0)

#define GPIOR2 IO_REG(0x4B) // reference page 33


#define GPIOR1 IO_REG(0x4A) // reference page 33


#define OCR0B IO_REG(0x48) // reference page no_ref


#define OCR0A IO_REG(0x47) // reference page no_ref


#define TCNT0 IO_REG(0x46) // reference page no_ref


#define TCCR0B IO_REG(0x45) // reference page no_ref

#define FOC0A (1<<7)
#define FOC0B (1<<6)
#define WGM02 (1<<3)
#define CS02 (1<<2)
#define CS01 (1<<1)
#define CS00 (1<<0)

#define TCCR0A IO_REG(0x44) // reference page no_ref

#define COM0A1 (1<<7)
#define COM0A0 (1<<6)
#define COM0B1 (1<<5)
#define COM0B0 (1<<4)
#define WGM01 (1<<1)
#define WGM00 (1<<0)

#define GTCCR IO_REG(0x43) // reference page 150/171

#define TSM (1<<7)
#define PSRASY (1<<1)
#define PSRSYNC (1<<0)

#define EEARH IO_REG(0x42) // reference page 29


#define EEARL IO_REG(0x41) // reference page 29


#define EEDR IO_REG(0x40) // reference page 29


#define EECR IO_REG(0x3F) // reference page 29

#define EEPM1 (1<<5)
#define EEPM0 (1<<4)
#define EERIE (1<<3)
#define EEMPE (1<<2)
#define EEPE (1<<1)
#define EERE (1<<0)

#define GPIOR0 IO_REG(0x3E) // reference page 33


#define EIMSK IO_REG(0x3D) // reference page 80

#define INT1 (1<<1)
#define INT0 (1<<0)

#define EIFR IO_REG(0x3C) // reference page 80

#define INTF1 (1<<1)
#define INTF0 (1<<0)

#define PCIFR IO_REG(0x3B) // reference page no_ref

#define PCIF2 (1<<2)
#define PCIF1 (1<<1)
#define PCIF0 (1<<0)

#define TIFR2 IO_REG(0x37) // reference page 169

#define OCF2B (1<<2)
#define OCF2A (1<<1)
#define TOV2 (1<<0)

#define TIFR1 IO_REG(0x36) // reference page 147

#define ICF1 (1<<5)
#define OCF1B (1<<2)
#define OCF1A (1<<1)
#define TOV1 (1<<0)

#define TIFR0 IO_REG(0x35) // reference page no_ref

#define OCF0B (1<<2)
#define OCF0A (1<<1)
#define TOV0 (1<<0)

#define PORTD IO_REG(0x2B) // reference page 100

#define PORTD7 (1<<7)
#define PORTD6 (1<<6)
#define PORTD5 (1<<5)
#define PORTD4 (1<<4)
#define PORTD3 (1<<3)
#define PORTD2 (1<<2)
#define PORTD1 (1<<1)
#define PORTD0 (1<<0)

#define DDRD IO_REG(0x2A) // reference page 100

#define DDD7 (1<<7)
#define DDD6 (1<<6)
#define DDD5 (1<<5)
#define DDD4 (1<<4)
#define DDD3 (1<<3)
#define DDD2 (1<<2)
#define DDD1 (1<<1)
#define DDD0 (1<<0)

#define PIND IO_REG(0x29) // reference page 100

#define PIND7 (1<<7)
#define PIND6 (1<<6)
#define PIND5 (1<<5)
#define PIND4 (1<<4)
#define PIND3 (1<<3)
#define PIND2 (1<<2)
#define PIND1 (1<<1)
#define PIND0 (1<<0)

#define PORTC IO_REG(0x28) // reference page 99

#define PORTC6 (1<<6)
#define PORTC5 (1<<5)
#define PORTC4 (1<<4)
#define PORTC3 (1<<3)
#define PORTC2 (1<<2)
#define PORTC1 (1<<1)
#define PORTC0 (1<<0)

#define DDRC IO_REG(0x27) // reference page 99

#define DDC6 (1<<6)
#define DDC5 (1<<5)
#define DDC4 (1<<4)
#define DDC3 (1<<3)
#define DDC2 (1<<2)
#define DDC1 (1<<1)
#define DDC0 (1<<0)

#define PINC IO_REG(0x26) // reference page 100

#define PINC6 (1<<6)
#define PINC5 (1<<5)
#define PINC4 (1<<4)
#define PINC3 (1<<3)
#define PINC2 (1<<2)
#define PINC1 (1<<1)
#define PINC0 (1<<0)

#define PORTB IO_REG(0x25) // reference page 99

#define PORTB7 (1<<7)
#define PORTB6 (1<<6)
#define PORTB5 (1<<5)
#define PORTB4 (1<<4)
#define PORTB3 (1<<3)
#define PORTB2 (1<<2)
#define PORTB1 (1<<1)
#define PORTB0 (1<<0)

#define DDRB IO_REG(0x24) // reference page 99

#define DDB7 (1<<7)
#define DDB6 (1<<6)
#define DDB5 (1<<5)
#define DDB4 (1<<4)
#define DDB3 (1<<3)
#define DDB2 (1<<2)
#define DDB1 (1<<1)
#define DDB0 (1<<0)

#define PINB IO_REG(0x23) // reference page 99

#define PINB7 (1<<7)
#define PINB6 (1<<6)
#define PINB5 (1<<5)
#define PINB4 (1<<4)
#define PINB3 (1<<3)
#define PINB2 (1<<2)
#define PINB1 (1<<1)
#define PINB0 (1<<0)

#endif//_M88_H_
