/*
 * 
 */
void init_ecorob(){
  init_pins();
  init_boost_pwm();
  init_drive_pwm();
  init_adc();
}

//Init pins for Ecorob
void init_pins() {
  /*digital in (Buttons) */
  PORTB |= 0xFF;
  /* digital out (LEDs) */
  DDRK |= 0xFF;
  /* analong in (IR sensors) */
  ;
  /* interface to motor driver */
  // PWM outputs motor 1
  DDRH |= (1 << PH5) | (1 << PH4) | (1 << PH3);
  // PWM outputs motor 1
  DDRE |= (1 << PE5) | (1 << PE4) | (1 << PE3);
  // analog in (sense)
  ;
  /* interface from motor encoder */
  ;
  /* interface to boost converter */
  // PWM outputs
  DDRB |= (1 << PB7) | (1 << PB6);
  // analog in (sense)
  ;
}

//Init PWM for boost converter
void init_boost_pwm() {
  /* Set up Counter1 */
  // OC1B non-inverted, OC1C inverted
  TCCR1A |= (1 << COM1B1) | (1 << COM1C1) | (1 << COM1C0);
  // Prescaler 1 (16 MHz)
  TCCR1B |= (1 << CS10);
  // Mode 9 (Phase- and frequency correct PWM)
  TCCR1B |= (1 << WGM13);
  TCCR1A |= (1 << WGM10);
  
  // Counter TOP 16-bit
  OCR1A = 0xFFFF;
  // Initialize compare match registers for zero output
  OCR1B = OCR1A;
  OCR1C = OCR1A - OCR1B;
}

//Init PWM for drives
 void init_drive_pwm(){
  //Initialisation of timer 4 for drive 1
  //Einstellung des Prescalers auf 1
  TCCR4B |= (1<<CS40);
  //Activate FastPWM
  TCCR4A |= (1<<WGM41)|(1<<WGM40);
  //Set pin-mode to normal
  TCCR4A |= (1<<COM4A1);
  
  //Initialisation of timer 3 for drive 2
  //Einstellung des Prescalers auf 1
  TCCR3B |= (1<<CS30);
  //Activate FastPWM
  TCCR3A |= (1<<WGM31)|(1<<WGM30);
  //Set pin-mode to normal
  TCCR3A |= (1<<COM3A1);  
}

//Init ADC for distance sensors
void init_adc(){
  //Active ADC
  ADCSRA |= (1<<ADEN);
  //Set prescaler to 64
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1);
  //Set reference voltage to 5V
  ADMUX |= (1<<REFS0);
}
