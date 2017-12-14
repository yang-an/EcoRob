/*
 * PWM generator for driver circuit
 * 
 * Create two PWM signals, one for each driver channel
 * (left/right). Direction of driving is controlled
 * by applying PWM signal to correct input pin of the
 * driver IC (IN1 or IN2).
 */

#define DRIVER_MAXSPEED 15  // 25% of possible maxspeed
#define DRIVER_MINSPEED -15
#define DRIVER_MAXANGLE 15
#define DRIVER_MINANGLE -15

void init_driver_pwm() {
  /* Initialize timers for motor driver PWM */
  //Initialisation of timer 4 for drive 1
  //Einstellung des Prescalers auf 1
  TCCR4B |= (1 << CS40);
  //Activate Fast PWM, 8-bit (mode 5)
  TCCR4A |= (1 << WGM40);
  TCCR4B |= (1 << WGM42);
  //Set non-inverting output mode
  TCCR4A |= (1 << COM4A1);

  //Initialisation of timer 3 for drive 2
  //Einstellung des Prescalers auf 1
  TCCR3B |= (1 << CS30);
  //Activate Fast PWM, 8-bit (mode 5)
  TCCR3A |= (1 << WGM30);
  TCCR3B |= (1 << WGM32);
  //Set non-inverting output mode
  TCCR3A |= (1 << COM3A1);
}

uint8_t driver_pwm_calculator (float normDistance) {
  //Calculation of PWM for  drive
  uint8_t pwm = 0;
  pwm = (1 - normDistance) * 1024;
  return pwm;
}

void driver_pwm_forward(uint16_t pwmLeft, uint16_t pwmRight) {
  //Set compare registers to calculated pwm values
  //Enable Motor Left setzen
  PORTH |= (1 << PORTH4);
  //Enable Motor Right setzten
  PORTE |= (1 << PORTE4);
  //PWM Signal auf PH3
  OCR4A = pwmRight;
  OCR4C = OCR4A;
  //PWM Signal auf PE3
  OCR3A = pwmLeft;
  OCR3C = OCR3A;
  //PH5 und PE5 sind auf GND 
}

void driver_set_direction(uint8_t valueDirection) {
  /* Set direction of movement */
  if (valueDirection == 1) {
    // backwards: apply signals to 
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
  if (valueAngle < DRIVER_MINANGLE) angleCurrent = DRIVER_MINANGLE;
  else if (valueAngle > DRIVER_MAXANGLE) angleCurrent = DRIVER_MAXANGLE;
  else angleCurrent = valueAngle;

  //Limit speed-value
  if (valueSpeed < DRIVER_MINSPEED) speedCurrent = DRIVER_MINSPEED;
  else if (valueSpeed > DRIVER_MAXSPEED) speedCurrent = DRIVER_MAXSPEED;
  else speedCurrent = valueSpeed;

  //Set driving direction
  if (speedCurrent >= 0) driver_set_direction(1);
  else driver_set_direction(0);


  pwmLeft  = abs(speedCurrent) * 255 / DRIVER_MAXSPEED;
  pwmRight = abs(speedCurrent) * 255 / DRIVER_MAXSPEED;

  pwmLeft = (pwmLeft + (angleCurrent * 255 / DRIVER_MAXANGLE)) / 2;
  pwmRight = (pwmRight + (-angleCurrent * 255 / DRIVER_MAXANGLE)) / 2;

  /*Serial.print("PWM-Left: ");
  Serial.println(pwmLeft);
  Serial.print("PWM-Right: ");
  Serial.println(pwmRight);
  _delay_ms(1000);*/
  
  driver_pwm_forward(pwmLeft, pwmRight);
}

