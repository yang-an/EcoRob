/*
 * ADC setup and sample routine
 * 
 * ADC capture is triggered by Timer0, the resulting sampling
 * rate is 8 kHz. Normal conversion takes 13 clock cycles, so
 * ADC clock needs to be greater than 104 kHz.
 * The converted value is written to the global data array in
 * the ADC ISR.
 */

void init_adc()
{
  /* Init Timer0 */
  // mode 1: CTC
  TCCR0A |= (1<<WGM01);
  // prescaler: 8 (2 MHz)
  TCCR0B |= (1<<CS01);
  // output compare: 250 (8 kHz ADC trigger)
  OCR0A = 250;
  // enable Timer0 compare A interrupt
  TIMSK0 |= (1<<OCIE0A);
  
  /* Init ADC */
  // internal VREF (5V)
  ADMUX = (1<<REFS0);
  // enable ADC + auto trigger + interrupt
  ADCSRA |= (1<<ADEN) | (1<<ADATE) | (1<<ADIE);
  // prescaler 128 (125 kHz ADC clock)
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
  //use OC0A as trigger
  ADCSRB |= (1<<ADTS1) | (1<<ADTS0);
  //disable digital inputs on PORTF
  DIDR0 = 0xFF;                       
  //start first conversion
  ADCSRA |= (1<<ADSC);               
}

ISR(ADC_vect)
{
  // get current channel
  uint8_t ch = ADMUX & 0x1F;
  // copy current reading into array
  adc[ch] = ADC;
  // increment channel counter
  ch = (ch+1) % ADC_MAX_CH;
  // clear all MUX bits
  ADMUX &= ~0x1F;
  // set MUX bits
  ADMUX |= ch;
  // clear timer interrupt flag
  TIFR0 |= (1 << OCF0A);
}

