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

