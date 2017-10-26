/*
 * LED display for indicating different values between 0 and 100.
 * 
 * Uses the eight LEDs for displaying values between 0 and 100.
 */

 void cycle_led_display (uint8_t value){
  if (value == 0) PORTK |= 0b11111111;
  else if (value >  0 && value <= 12) PORTK = 0b01111111;
  else if (value > 12 && value <= 25) PORTK = 0b00111111;
  else if (value > 25 && value <= 37) PORTK = 0b00011111;
  else if (value > 37 && value <= 50) PORTK = 0b00001111;
  else if (value > 50 && value <= 62) PORTK = 0b00000111;
  else if (value > 62 && value <= 75) PORTK = 0b00000011;
  else if (value > 75 && value <= 87) PORTK = 0b00000001;
  else PORTK = 0b00000000;
  //PORTK = 0b00001111;
}
