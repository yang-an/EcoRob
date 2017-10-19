/* 
 *  EcoRob main module
 */

int main() {
  // set pin modes according to specification
  init_pins();
  
  init_boost_pwm();
  // main loop
  while (1) {
    cycle_boost_pwm(20);
  }
}

void init_pins() {
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

