/*
int main(){
  init();
  Serial.begin(9600);
  Port_Init();
  Adc_Init();
  Timer_Init();
  uint16_t distanceLeft;
  uint16_t distanceRight;
  uint16_t rpmLeft;
  uint8_t rpmLeftHigh;
  uint8_t rpmLeftLow;
  uint16_t rpmRight;
  uint8_t rpmRightHigh;
  uint8_t rpmRightLow;
  float normDisLeft;
  float normDisRight;

  //Zyklische Routine
  while(1){
    distanceLeft = Read_DistanceLeft();
    distanceRight = Read_DistanceRight();
    normDisLeft = Norm_Distance(distanceLeft);
    normDisRight = Norm_Distance(distanceRight);
    Serial.print(distanceLeft);
    Serial.print(" ");
    Serial.print(normDisLeft);
    Serial.print(" ");
    Serial.print(distanceRight);
    Serial.print(" ");
    Serial.println(normDisRight);

    //Regler für Motoransteuerung
    //Vorberechnung für Motor 1
    rpmLeft = (1 - normDisLeft) * 1024;
    //Vorberechnung für Motor 2
    rpmRight = (1 - normDisRight) * 1024;
    
    OCR4A = rpmLeft;
    OCR3A = rpmRight;

    Led_Display(100);
       
    _delay_ms(2);
  }
}

//Konfiguration der Ports
void Port_Init(){
  //Konfiguration der digitalen Ausgänge
  //LEDs (Register K)
  DDRK |= 0xff;
  //Konfiguration der PWM-Ausgänge
  //PWM-Ausgang Motor 1
  DDRH |= (1<<DDH3);
  //PWM-Ausgang Motor 2
  DDRE |= (1<<DDE3);
  
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

//Konfiguration der Timer
void Timer_Init(){
  //Konfiguration Timer 4 für Motor 1
  //Reset des Vergleich-Registers
  // TCCR4A = 0;
  //Einstellung des Prescalers auf 1
  TCCR4B |= (1<<CS40);
  //Aktivierung FastPWM
  TCCR4A |= (1<<WGM41)|(1<<WGM40);
  //Einstellung Pin-Modus auf Normal
  TCCR4A |= (1<<COM4A1);
  
  //Konfiguration Timer 3 für Motor 2
  //Reset des Vergleich-Registers
  // TCCR3A = 0;
  //Einstellung des Prescalers auf 1
  TCCR3B |= (1<<CS30);
  //Aktivierung FastPWM
  TCCR3A |= (1<<WGM31)|(1<<WGM30);
  //Einstellung Pin-Modus auf Normal
  TCCR3A |= (1<<COM3A1);  
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

//Normierung des Abstandswert
float Norm_Distance (uint16_t value){
  float normDistance = 0.0;
  normDistance = (float)value/625;
  return normDistance;
}

//Paket: Balkenanzeige LEDs
void Led_Display (uint8_t percent){
  if (percent = 0) DDRK |= 0b11111111;
  else if (percent >  0 && percent <= 12) DDRK = 0b01111111;
  else if (percent > 12 && percent <= 25) DDRK = 0b00111111;
  else if (percent > 25 && percent <= 37) DDRK = 0b00011111;
  else if (percent > 37 && percent <= 50) DDRK = 0b00001111;
  else if (percent > 50 && percent <= 62) DDRK = 0b00000111;
  else if (percent > 62 && percent <= 75) DDRK = 0b00000011;
  else if (percent > 75 && percent <= 87) DDRK = 0b00000001;
  else DDRK = 0b00000000;
}
*/
