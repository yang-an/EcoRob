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
#define ADC_MAX_CH    7

/**********global variables**********/
volatile uint16_t adc[7] = {0};

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
    Serial.print("L: ");
    Serial.print(DIST_LEFT);
    Serial.print(" | C: ");
    Serial.print(DIST_CENTER);
    Serial.print(" | R: ");
    Serial.println(DIST_RIGHT);
    _delay_ms(5);
  }
}



