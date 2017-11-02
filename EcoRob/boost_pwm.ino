/*
 * PWM generator for boost converter
 * 
 * Create two PWM signals, shifted by 180 degrees. For this,
 * we use Mode 9 (phase- and frequency-correct) on Counter1,
 * using OCR1A as TOP (tunable PWM resolution)
 */

void cycle_boost_pwm(uint8_t delay_) {
  uint16_t ocr_old = 0;
  /* Cycle PWM from 0% to 100% duty cycle */
  for(uint16_t ocr = 0x0; ocr >= ocr_old; ocr += 0x0100) {
    OCR1B = ocr;
    OCR1C = OCR1A - OCR1B  ;
    _delay_ms(delay_);
    Serial.println(ocr); //Diag
    ocr_old = ocr;
  }
}
