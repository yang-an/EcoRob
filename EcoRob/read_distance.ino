/*
 * Read sensors for distance-measurement
 */

float read_distance_left(){
  //Select channel 0
  ADMUX &= ~(1<<MUX0);
  //Start conversion
  ADCSRA |= (1<<ADSC);
  //Wait for end of conversion
  while (ADCSRA & (1<<ADSC));
  return norm_distance(ADC);
}

float read_distance_right(){
  //Select channel 0
  ADMUX |= (1<<MUX0);
  //Start conversion
  ADCSRA |= (1<<ADSC);
  //Wait for end of conversion
  while (ADCSRA & (1<<ADSC));
  return norm_distance(ADC);
}

float norm_distance (uint16_t distance_){
  float normDistance = 0.0;
  normDistance = (float)distance_/625;
  return normDistance;
}
