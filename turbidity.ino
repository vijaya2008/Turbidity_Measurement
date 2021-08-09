#include <Wire.h> 
#include <LiquidCrystal.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sensorPin = A0;
float volt;
float ntu;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop()
{
    
    volt = 0;
    for(int i=0; i<80; i++)
    {
        volt += ((float)analogRead(sensorPin)/1023)*5;
    }
    volt = volt/80;
    volt = round_to_dp(volt,1);
    if(volt < 2.5){
      ntu = 3000;
    }if( volt > 4.1){
      ntu = 0;
    }
    else{
      ntu = -1120.4*sq(volt)+5742.3*volt-4353.8; 
    }
    Serial.print(volt);
    Serial.println(" V");
    lcd.setCursor(0,0);
    lcd.print(volt);
    lcd.print(" V");
    Serial.print(ntu);
    Serial.println(" NTU");
    lcd.setCursor(0,1);
    lcd.print(ntu);
    lcd.print(" NTU");
    delay(100);
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
