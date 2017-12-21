/*
 * PWM generator for boost converter
 * 
 * Create two PWM signals, shifted by 180 degrees. For this,
 * we use Mode 9 (phase- and frequency-correct) on Counter1,
 * using OCR1A as TOP (tunable PWM resolution)
 */

#define TC1_TOP                 319   // 16 MHz / 50 kHz - 1 = 319
#define BOOST_PWM_MAX           287   // 319 * 95% = 303
#define BOOST_CONTROLLER_GAIN   4    // fixed point 4.4 Bit
#define BOOST_OUTPUT_REF        785   // 12 V / (1k + 470) * 470 / 5 V * 1023 = 785
//#define BOOST_OUTPUT_REF        523   // 8 V / (1k + 470) * 470 / 5 V * 1023 = 785

void init_boost_pwm() {
  /* Initialize Timer1 for dual-phase PWM */
  // OC1B non-inverted, OC1C inverted
  TCCR1A |= (1 << COM1B1) | (1 << COM1C1) | (1 << COM1C0);
  // Prescaler 1 (16 MHz)
  TCCR1B |= (1 << CS10);
  // Mode 9 (Phase- and frequency correct PWM)
  TCCR1B |= (1 << WGM13);
  TCCR1A |= (1 << WGM10);
  
  // Counter TOP value (adjustable PWM frequency)
  OCR1A = TC1_TOP;
  
  // Initialize compare match registers for zero output
  OCR1B = OCR1A;
  OCR1C = OCR1A - OCR1B;
}

inline void set_boost_pwm_ocr(uint16_t ocr) { // inline to avoid a function call
  // shift right (11.5 fixed point)
  ocr >>= 5;
  // clamp max value
  OCR1B = ocr <=BOOST_PWM_MAX ? ocr : BOOST_PWM_MAX;
  OCR1C = TC1_TOP - OCR1B;
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

ISR(TIMER0_COMPA_vect)
{
  /* output voltage control loop
  sample frequency: 8 kHz (ADC sample clock)
  */
  static uint8_t isr_cntr = 0;
  int16_t xd = 0;
  static int16_t xdsum = 0;
  static int32_t y = 0;
  
  
  if(isr_cntr < ADC_MAX_CH) {
    /* there is no new measured output voltage yet
     * use the time to calculate "fuel" gauge
     */
    isr_cntr++;
    PORTK = 0xFF << (BOOST_U_IN >> 7);
  }
    
  else
  {
    isr_cntr = 0;
    xd = BOOST_OUTPUT_REF - BOOST_U_OUT;

    xdsum += xd;
    y = (int32_t)KP * xd + KI * xdsum;

    // anti-windup
    // shift left (11.5 fixed point)
    if(y > (BOOST_PWM_MAX << 5)) {
      y = BOOST_PWM_MAX << 5;
      xdsum = (BOOST_PWM_MAX << 5);
    }
    else if(y < 0) {
      y = 0;
      xdsum = 0;
    }
    set_boost_pwm_ocr((uint16_t)y);   // y is already limited -> can be converted to unsigned
  }
}
