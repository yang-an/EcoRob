/*
 * PWM generator for boost converter
 * 
 * Create two PWM signals, shifted by 180 degrees. For this,
 * we use Mode 9 (phase- and frequency-correct) on Counter1,
 * using OCR1A as TOP (tunable PWM resolution)
 */

#define TC1_TOP 0xFFFF;

void init_boost_pwm() {
  /* Initialize Timer1 for dual-phase PWM */
  // OC1B non-inverted, OC1C inverted
  TCCR1A |= (1 << COM1B1) | (1 << COM1C1) | (1 << COM1C0);
  // Prescaler 1 (16 MHz)
  TCCR1B |= (1 << CS10);
  // Mode 9 (Phase- and frequency correct PWM)
  TCCR1B |= (1 << WGM13);
  TCCR1A |= (1 << WGM10);
  
  // Counter TOP value (adjustable)
  OCR1A = TC1_TOP;
  
  // Initialize compare match registers for zero output
  OCR1B = OCR1A;
  OCR1C = OCR1A - OCR1B;
}

void cycle_boost_pwm(uint8_t step_, uint8_t delay_) {
  /* DEBUG: Cycle PWM from 0% to 100% duty cycle */
  for(uint16_t ocr = 0x0; ocr <  OCR1A-step_ ; ocr += step_) {
    OCR1B = ocr;
    OCR1C = OCR1A - OCR1B  ;
    _delay_ms(delay_);
    Serial.println(ocr); //Diag
  }
}
