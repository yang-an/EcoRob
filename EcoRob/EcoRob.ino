/* 
 *  EcoRob main module
 *
 *  Contains globals and pin definitions.
 *
 *  BLOCKED RESOURCES:
 *  ------------------
 *  Timer0 (by adc)
 */

/***********global defines***********/
#define DIST_RIGHT    adc[0]
#define DIST_CENTER   adc[1]
#define BOOST_U_OUT   adc[2]
#define BOOST_U_IN    adc[3]
#define MOTOR_I_RIGHT adc[4]
#define MOTOR_I_LEFT  adc[5]
#define DIST_LEFT     adc[6]
#define AUX_IN        adc[7]
#define ADC_MAX_CH    8
//test
#define KP 200//(DIST_LEFT >> 2)
#define KI 10//(AUX_IN >> 3)

/**********global variables**********/
volatile uint16_t adc[8] = {0};


int main() {
  /* Init routine:
   *  1. Set pin modes and pullups
   *  2. Initialize components:
   *  - ADC
   *  - PWM generator for boost converter
   *  - PWM generator for motor drivers
   */
  Serial.begin(115200);
  init_pins();
  init_adc();
  init_boost_pwm();
  init_driver_pwm();
  sei();
  
  while (1) {
    static uint16_t leftBuf = 0, rightBuf = 0;
    leftBuf -= (leftBuf >> 4);
    rightBuf -= (rightBuf >> 4);
    leftBuf += DIST_LEFT;
    rightBuf += DIST_RIGHT;
    
    
    //driver_pwm_forward((leftBuf >> 5) + 64, (rightBuf >> 5) + 64);
    //driver_pwm_forward(127 - (rightBuf >> 5), 127 - (leftBuf >> 5));
    driver_pwm_forward(
      (127 - (rightBuf >> 6) + (leftBuf >> 6) + 64) >> 1,
      (127 - (leftBuf >> 6) + (rightBuf >> 6) + 64) >> 1
    );
    for (uint8_t i=0; i<(AUX_IN >> 4); i++)
      _delay_ms(1);
  }
    
}




