int main(){
  init();
  Serial.begin(9600);
  Port_Init();
  Adc_Init();
  uint16_t distanceLeft;
  uint16_t distanceRight;

//Zyklische Routine
  while(1){
    distanceLeft = Read_DistanceLeft();
    distanceRight = Read_DistanceRight();
    Serial.print(distanceLeft);
    Serial.print(" ");
    Serial.println(distanceRight);
    _delay_ms(500);
  }
}

//Konfiguration der Ports
void Port_Init(){
  //Konfiguration der digitalen Ausgänge
  //LEDs (Register K)
  DDRK |= 0xff;
}

//Konfiguration des ADC
void Adc_Init(){
  //Aktivieren des ADC
  ADCSRA |= (1<<ADEN);
  //Prescaler auf 64 einstellen
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1);
  //Referenzspannung auf 5V einstellen
  ADMUX |= (1<<REFS0);
}

//Auslesen Abstand Distanzsensor Links (AD0)
uint16_t Read_DistanceLeft(){
  //Kanal 0 des Multiplexers
  ADMUX &= ~(1<<MUX0);
  //Wandlung starten
  ADCSRA |= (1<<ADSC);
  //Warten auf Wandlungsende
  while (ADCSRA & (1<<ADSC));
  return ADC;
}

//Auslesen Abstand Distanzsensor Rechts (AD1)
uint16_t Read_DistanceRight(){
  //Kanal 0 des Multiplexers
  ADMUX |= (1<<MUX0);
  //Wandlung starten
  ADCSRA |= (1<<ADSC);
  //Warten auf Wandlungsende
  while (ADCSRA & (1<<ADSC));
  return ADC;
}

