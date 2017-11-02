/* 
 * Initialize all pins needed by EcoRob
 */

void init_pins() {
  /* BLOCK B: Buttons and Boost DIG IN */
  // pullups for buttons (PB3..0)
  PORTB |= 0x0F;
  // Timer1 outputs
  DDRB |= (1 << PB7) | (1 << PB6);
  
  /* BLOCK D: motor current sense */
  ;

  /* BLOCK E: motor PWM */
  // Timer3 outputs
  DDRE |= (1 << PE5) | (1 << PE4) | (1 << PE3);
  
  /* BLOCK F: ADC */
  ;
  
  /* BLOCK H: motor PWM */
  // Timer4 outputs
  DDRH |= (1 << PH5) | (1 << PH4) | (1 << PH3);
  
  /* BLOCK K: LEDs */
  // LED output pins
  DDRK |= 0xFF;
}
