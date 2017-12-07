/*

*/

#define maxSpeed 15
#define minSpeed -15
#define maxAngle 15
#define minAngle -15

void init_driver_pwm() {
  /* Initialize timers for motor driver PWM */
  //Initialisation of timer 4 for drive 1
  //Einstellung des Prescalers auf 1
  TCCR4B |= (1 << CS40);
  //Activate Phase-correct PWM, 10-bit
  TCCR4A |= (1 << WGM41) | (1 << WGM40);
  //Set pin-mode to normal
  TCCR4A |= (1 << COM4A1);

  //Initialisation of timer 3 for drive 2
  //Einstellung des Prescalers auf 1
  TCCR3B |= (1 << CS30);
  //Activate Phase-correct PWM, 10-bit
  TCCR3A |= (1 << WGM31) | (1 << WGM30);
  //Set pin-mode to normal
  TCCR3A |= (1 << COM3A1);
}

uint8_t drive_pwm_calculator (float normDistance) {
  //Calculation of PWM for  drive
  uint8_t pwm = 0;
  pwm = (1 - normDistance) * 1024;
  return pwm;
}

/*
int drive_power_test(){
  char wert_a[3];
  int i = 0;
  int int_wert1 = 0;
  Serial.print("Bitte den ersten Wert eingeben");
  while (Serial.available() > 0 && i<4){
    wert_a[i] = Serial.read();
    i++;
    Serial.print("test");
  }
  Serial.flush();
  int_wert1 = atoi(wert_a);
  _delay_ms(1000);
  Serial.println(int_wert1);
}
*/

void drive_pwm_set () {
  
}

void drive_pwm_forward(uint16_t pwmLeft, uint16_t pwmRight) {
  //Set compare registers to calculated pwm values
  //Enable Motor Left setzen
  PORTH |= (1 << PORTH4);
  //Enable Motor Right setzten
  PORTE |= (1 << PORTE4);
  //PWM Signal auf PH3
  OCR4A = pwmLeft;
  OCR4C = OCR4A;
  //PWM Signal auf PE3
  OCR3A = pwmRight;
  OCR3C = OCR3A;
  //PH5 und PE5 sind auf GND 

  //Serial.print("OCR4A: ");
  //Serial.println(OCR4A);
  //Serial.print("OCR3A: ");
  //Serial.println(OCR3A);

  //Serial.println(35000);
}

//ggf pruefen
void drive_set_direction(uint8_t valueDirection) {
  //valueDirection==0 enspricht forwearts fahrt
  if (valueDirection == 0) {
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3C1);
    TCCR4A |= (1 << COM4A1);
    TCCR4A &= ~(1 << COM4C1);
  }
  else {
    TCCR3A &= ~(1 << COM3A1);
    TCCR3A |= (1 << COM3C1);
    TCCR4A &= ~(1 << COM4A1);
    TCCR4A |= (1 << COM4C1);
  }
}

void drive(int8_t valueAngle, int8_t valueSpeed){
  int8_t angleCurrent = 0;
  int8_t speedCurrent = 0;
  int16_t pwmLeft, pwmRight;

  //Limit angle-value
  if (valueAngle < minAngle) angleCurrent = minAngle;
  else if (valueAngle > maxAngle) angleCurrent = maxAngle;
  else angleCurrent = valueAngle;

  //Limit speed-value
  if (valueSpeed < minSpeed) speedCurrent = minSpeed;
  else if (valueSpeed > maxSpeed) speedCurrent = maxSpeed;
  else speedCurrent = valueSpeed;

  //Set driving direction
  if (speedCurrent >= 0) drive_set_direction(1);
  else drive_set_direction(0);


  pwmLeft  = abs(speedCurrent) * 1024 / maxSpeed;
  pwmRight = abs(speedCurrent) * 1024 / maxSpeed;

  pwmLeft = (pwmLeft + (angleCurrent * 1024 / maxAngle)) / 2;
  pwmRight = (pwmRight + (-angleCurrent * 1024 / maxAngle)) / 2;

  /*Serial.print("PWM-Left: ");
  Serial.println(pwmLeft);
  Serial.print("PWM-Right: ");
  Serial.println(pwmRight);
  _delay_ms(1000);*/
  
  drive_pwm_forward(pwmLeft, pwmRight);
  
}






