/*
 * 
 */

 uint8_t cycle_diagnose_mode(){
  if ((PINB & 0b00000001) == 0) return 1;
  else if ((PINB & 0b00000010) == 0) return 2;
  else if ((PINB & 0b00000100) == 0) return 3;
  else if ((PINB & 0b00001000) == 0) return 4;
  else return 0;
 }

void cycle_diagnose_display(uint8_t mode){
  switch (mode){ 
    case 1: cycle_led_display(read_distance_left()*100); break;
    case 2: cycle_led_display(read_distance_right()*100); break;
    case 3: cycle_led_display(60); break;
    case 4: cycle_led_display(85); break;
    default: cycle_led_display(0); break;
  }
}

