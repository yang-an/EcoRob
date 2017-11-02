/*
 * 
 */

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

