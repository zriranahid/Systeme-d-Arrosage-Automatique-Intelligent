#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int pompe=9;
int LDR=0;
int lumiere;
const int seuil_nuit=100;
const int seuil_jour=150;
bool Dj=true;
int cpt=0;
int alarm=2;
void setup() {
    pinMode(pompe,OUTPUT);
  pinMode(LDR,INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("luminosite");
}
void loop() {
  lumiere=analogRead(LDR);
Serial.print(lumiere);
lcd.setCursor(0,1);
lcd.print("                ");
lcd.setCursor(0,1);
lcd.print(lumiere);
lcd.setCursor(6,1);
lcd.print("Lux");
if(lumiere<seuil_nuit && Dj==true)
{
  if(cpt==0)
  {
    tone(alarm,1000);
  delay(1000);
  noTone(alarm);
   digitalWrite(pompe,HIGH);
  delay(6000);
  digitalWrite(pompe,LOW);
  tone(alarm,1000);
  delay(1000);
  noTone(alarm);
  Dj=false;
  }
  if(cpt!=0) 
Dj=false;
}

if(lumiere>seuil_jour && Dj==false)
{
  cpt++;
  Dj=true;
}
if(cpt==2) cpt=0;

delay(1000);
}
