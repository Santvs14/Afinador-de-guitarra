#define Eta 82.41
#define A 110.00
#define D 146.83
#define G 196.00
#define B 246.94
#define Era 329.63

#include <FreqMeasure.h> //Importar libreria para detectar frecuencias
/***/
#include <LiquidCrystal.h>    // importa libreria

//Conexion LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  //Arduino// pines LCD RS, E, D4, D5, D6, D7 de modulo 1602A

float Hz = 0;

const int pinMicrophone = 13;
int mic_Anag = A5;
int Valor_Micro1 = 0;
int Valor_Micro2 = 0;
int count = 1;
int ledAlto = 8;
int ledBien = 9;
int ledBajo = 10;
String afinador;
int p1 = 0; //Se define la posicion para mostrar el LCD

float frecuencia = 0;
int count1 = 0;

void setup() {

  
  pinMode(pinMicrophone, INPUT);
  pinMode(ledAlto, OUTPUT);
  pinMode(ledBien, OUTPUT);
  pinMode(ledBajo, OUTPUT);

  lcd.begin(16, 2);//No.Columnas y Filas
 

  lcd.print(" Bienvenido...");
  lcd.setCursor(0, 1);
  delay(2000);

  lcd.print(" Santiago VS");
  lcd.setCursor(0, 2);
  delay(2000);

  lcd.clear();
 Serial.begin (9600);//Mostrar en monitor

  FreqMeasure.begin();
  //Muestra las ondas de sondio y acciona un Led
  

}

void loop() {

Valor_Micro1 = analogRead(mic_Anag);
  Serial.println (Valor_Micro1);
  delay(1);
  Valor_Micro2 = analogRead(mic_Anag);
  Serial.println (Valor_Micro2);
  delay(1);

  if (Valor_Micro2 - Valor_Micro1 > 1) {
    digitalWrite(ledAlto, HIGH);
    delay(200);
    digitalWrite(ledAlto, LOW);
  } if (Valor_Micro2 - Valor_Micro1 > 1){
    digitalWrite(ledBien, HIGH);
    delay(200);
    digitalWrite(ledBien, LOW);
  }if (Valor_Micro2 - Valor_Micro1 > 1){
    digitalWrite(ledBajo, HIGH);
    delay(200);
    digitalWrite(ledBajo, LOW);
  }





  
  count1 = count1 +1;
  if(count1 > 30){
  if (FreqMeasure.available()) {    
    Hz = Hz + FreqMeasure.read();
    frecuencia = FreqMeasure.countToFrequency(Hz / count);
  
    //Afinar E.Sexta
    

      if (frecuencia < (163 - 2)) {
        lcd.print("E.sexta ");
        lcd.setCursor(7, 1);
        delay(10);
        lcd.print(Valor_Micro1);
         lcd.setCursor(0, 2);
        lcd.print("Bajo");
        lcd.setCursor(7, 2);
        delay(10);
         lcd.clear();

        digitalWrite(ledAlto, LOW);
        digitalWrite(ledBien, LOW);
        digitalWrite(ledBajo, HIGH);
        delay(10);
       digitalWrite(ledBajo, LOW);
       
        
       // lcd.print(frecuencia);
      }
      if (frecuencia <= (82.40 + 1) && frecuencia >= (163.37 - 1)) {
        lcd.print("E.sexta ");
        lcd.setCursor(7, 1);
        delay(10);
        lcd.print(Valor_Micro1);
         lcd.setCursor(3, 2);
        lcd.print("Afinada ");
        lcd.setCursor(7, 2);
        delay(10);
         lcd.clear();

        digitalWrite(ledAlto, LOW);
        digitalWrite(ledBien, HIGH);
        delay(10);
       digitalWrite(ledBien, LOW);
        digitalWrite(ledBajo, LOW);
        
        
      }
      if (frecuencia > (100) && frecuencia < (182)) {
         lcd.print("E.sexta ");
        lcd.setCursor(7, 1);
        delay(10);
        lcd.print(Valor_Micro1);
         lcd.setCursor(0, 2);
        lcd.print("Alto ");
        lcd.setCursor(4, 2);
        delay(10);
        lcd.clear();

        digitalWrite(ledAlto, HIGH);
        delay(10);
       digitalWrite(ledAlto, LOW);
        digitalWrite(ledBien, LOW);
        digitalWrite(ledBajo, LOW);
        
      }
    }
    //Afinar A.Quinta
      
  }
}
