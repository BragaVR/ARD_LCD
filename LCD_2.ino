#include <LiquidCrystal_I2C.h>
#include <FlexiTimer2.h>

//inizializzare le librerie

LiquidCrystal_I2C lcd(0x27, 16, 2);

int tempPin = 0;
float tempVal;
int hour, minute, second;


void setup() {
  lcd.init();
  lcd.backlight();
  startingAnimation();
  FlexiTimer2::set(1000,timerInt);
  FlexiTimer2::start();
  Serial.begin(115200);
  Serial.println("Inserire ore,minuti,secondi per settare il tempo");
  
}

void loop() {
  //prendi la temperatura
  tempVal = getTemp();
  if (second >= 60) {
    second = 0;
    minute++;
  if (minute >= 60) {
    minute = 0;
    hour++;
  if (hour >= 24) {
    hour = 0;
    }
  
   }
   
 }

  lcdDisplay();
  delay(200);

}

  void startingAnimation() {
    for (int i = 0; i < 16; i++) {
      lcd.scrollDisplayRight();
    }
    lcd.print("inizializzare....");
    for (int i=0; i < 16;i++) {
      lcd.scrollDisplayLeft();
      delay(300);
    }
    lcd.clear();
  }
  //timer interrotto dalla funzione flextimer
 void timerInt(){
  second++;
 }

 //porta seriale interrotta
 void serialEvent() {
  int inInt[3];
  while (Serial.available()) {
    for (int i = 0; i < 3;i++) {
      inInt[i] = Serial.parseInt();

    }

  // inserisci i dati ricevuti per confermare

  Serial.print("Il tuo input è: ");
  Serial.print(inInt[0]);
  Serial.print(", ");
  Serial.print(inInt[1]);
  Serial.print(", ");
  Serial.print(inInt[2]);
 //utilizza i dati ricevuti per aggiustare il tempo

 hour = inInt[0];
 minute = inInt[1];
 second = inInt[2];
// inserisci il tempo modificato

Serial.print("l'ora è: ");
Serial.print(hour/10);
Serial.print(hour % 10);
Serial.print(':');
Serial.print(minute/10);
Serial.print(minute % 10);
Serial.print(':');
Serial.print(second/10); 
Serial.print(second % 10);    
    }
  }

void lcdDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.print(tempVal);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("TIME: ");
  lcd.print(hour/10);
  lcd.print(hour % 10);
  lcd.print(':');
  lcd.print(minute / 10);
  lcd.print(minute % 10);
  lcd.print(':');
  lcd.print(second / 10);
  lcd.print(second % 10);  
  }
  float getTemp() {
    int adcVal = analogRead(tempPin);
    //calcolare voltaggio

    float v =adcVal * 5.0 / 1024;
    //calcolare resistenza

    float Rt = 10 * v / (5-v);

    float tempK = 1 / (log(Rt / 10) / 3950 + 1 / (273.15 + 25));


    return tempK - 273.15;
  
  

}
