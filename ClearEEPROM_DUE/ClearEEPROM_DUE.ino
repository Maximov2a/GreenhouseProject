//--------------------------------------------------------------------------------------------------------------------------------
// какую AT24CX используем ?
#define AT24CX_TYPE 1 // 1 - AT24C32, 2 - AT24C64, 3 - AT24C128, 4 - AT24C256, 5 - AT24C512
//--------------------------------------------------------------------------------------------------------------------------------
#include "AT24CX.h"
#include <Wire.h>
//--------------------------------------------------------------------------------------------------------------------------------
#if AT24CX_TYPE == 1
AT24C32 eeprom;
const unsigned int eepromSize = 4096;
#elif AT24CX_TYPE == 2
AT24C64 eeprom;
const unsigned int eepromSize = 4096*2;
#elif AT24CX_TYPE == 3
AT24C128 eeprom;
const unsigned int eepromSize = 4096*4;
#elif AT24CX_TYPE == 4
AT24C256 eeprom;
const unsigned int eepromSize = 4096*8;
#elif AT24CX_TYPE == 5
AT24C512 eeprom;
const unsigned int eepromSize = 4096*16;
#endif

//--------------------------------------------------------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(57600);
  Serial.println("Start AT24CX EEPROM cleaning...");

  Wire.begin();


  for(unsigned int i=0;i<eepromSize;i++)
    eeprom.write(i,(byte)0xFF);

  Serial.println("AT24CX EEPROM cleared!");

}
//--------------------------------------------------------------------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:

}
//--------------------------------------------------------------------------------------------------------------------------------

