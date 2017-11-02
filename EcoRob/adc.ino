/*
 * ADC
 */

void init_adc()
{
  TCCR0A = (1<<WGM1);                 //CTC
  TCCR0B = (1<<CS01);                 //16MHz / 8 = 2MHz
  OCR0A = 250;                        //2MHz / 8kHz = 250

  ADMUX = (1<<REFS0);                 //set reference to 5V
  ADCSRA = (1<<ADEN) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  //auto trigger + interrupt + 16MHz / 128
  ADCSRB = (1<<ADTS1) | (1<<ADTS0);   //use TC0 OVF as trigger

  DIDR0 = 0xFF;                       //disable digital inputs on PORTF

  ADCSRA |= (1<<ADSC);                //start first conversion
}

ISR(ADC_vect)
{
  uint8_t ch = ADMUX & 0x1F;
  adc[ch] = ADC;
  ch++;
  ch %= ADC_MAX_CH;
  ADMUX &= ~0x1F;
  ADMUX |= ch;
}

