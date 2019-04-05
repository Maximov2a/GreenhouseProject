#include "FreqCount.h"
//-----------------------------------------------------------------------------------------------------
// частота, при которой влажность - 0% (датчик на воздухе)
#define ZERO_PERCENT_FREQUENCY 350000
// частота, при которой влажность - 100% (датчик в воде)
#define HUNDRED_PERCENT_FREQUENCY 50000
// С пина D5 снимается частота
// На пин D6 подаётся ШИМ
//-----------------------------------------------------------------------------------------------------
#define _DEBUG
//-----------------------------------------------------------------------------------------------------
unsigned long currentFrequency;
int8_t currentSoilMoisture;
//-----------------------------------------------------------------------------------------------------
void writePWM()
{
    byte pwm = 1;
    if( currentSoilMoisture > 0)
    {
      pwm = map(currentSoilMoisture,0,100,1,254);
    }

#ifdef _DEBUG
/*
    // потихоньку наращиваем влажность почвы
    static int incPWM = 0;
    incPWM++;
    if(incPWM > 254)
      incPWM = 1;
      
    pwm = incPWM;
*/    
    Serial.print("PWM: ");
    Serial.println(pwm);
#endif
    
    analogWrite(6,pwm);
}
//-----------------------------------------------------------------------------------------------------
void computeSoilMoisture()
{
    if(currentFrequency < 1)
    {
      currentSoilMoisture = -128;
      return;
    }

  
    if(currentFrequency > ZERO_PERCENT_FREQUENCY)
      currentFrequency = ZERO_PERCENT_FREQUENCY;

    if(currentFrequency < HUNDRED_PERCENT_FREQUENCY)
      currentFrequency = HUNDRED_PERCENT_FREQUENCY;

   currentSoilMoisture = 100 - map(currentFrequency,HUNDRED_PERCENT_FREQUENCY,ZERO_PERCENT_FREQUENCY,0,100);
}
//-----------------------------------------------------------------------------------------------------
void setup() 
{
  currentFrequency = 0;
  currentSoilMoisture = 0;
  
#ifdef _DEBUG  
  Serial.begin(57600);
#endif

  FreqCount.begin(1000);
}
//-----------------------------------------------------------------------------------------------------
void loop() 
{
  if (FreqCount.available()) 
  {
    currentFrequency = FreqCount.read();

#ifdef _DEBUG      
    Serial.print("Frequency: ");
    Serial.println(currentFrequency);
#endif
    computeSoilMoisture();
    writePWM();
#ifdef _DEBUG  
    Serial.print("Moisture: ");
    Serial.println(currentSoilMoisture);
#endif
  }

  delay(5000);
}
//-----------------------------------------------------------------------------------------------------


