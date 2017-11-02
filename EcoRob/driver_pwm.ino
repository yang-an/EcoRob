/*
 * 
 */

void init_driver_pwm(){
  /* Initialize timers for motor driver PWM */
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

uint8_t cycle_drive_pwm_calculator (float normDistance_){
  //Calculation of PWM for  drive
  uint8_t pwm = 0;
  pwm = (1 - normDistance_) * 1024;
  return pwm;
}

void cycle_drive_pwm(uint16_t pwmLeft_, uint16_t pwmRight_){
  //Set compare registers to calculated pwm values
  OCR4A = pwmLeft_;
  OCR3A = pwmRight_;
}

