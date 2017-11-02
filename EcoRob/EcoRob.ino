/* 
 *  EcoRob main module
 */

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



