/* 
 *  EcoRob main module
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
/***********global defines***********/

/**********global variables**********/
uint18_t adc[7] = {0};
/**********global variables**********/

int main() {
  init_ecorob();
  Serial.begin(9600);

  uint8_t disper;
  // main loop
  while (1) {
    cycle_drive_pwm(cycle_drive_pwm_calculator(read_distance_left()), 
                    cycle_drive_pwm_calculator(read_distance_right()));
    //cycle_boost_pwm(0);
    //cycle_led_display(25);
  }
}



