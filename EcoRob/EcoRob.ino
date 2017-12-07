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

//test
volatile int32_t y = 0;
volatile int16_t xd = 0;

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
  
  while (1);
}



