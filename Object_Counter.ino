/*
 * Created on 2 August 2019
 * 
 * 
 * 
 * 
 */

 
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

#include <LiquidCrystal.h>

//LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int upButton = 7;
int downButton = 8;
int selectButton = 9;
int Sensor = 10; //Sensor Input

int Option = 1; //Variable for Menu control
int Count  = 0; //Variable for counting pieces

int TimeBeforeSensor = 0;  //Variable for capture the time before beggining sensor reading
//begin measuring.

unsigned long Time = 0;

float Efficiency = 0;


int vel1 = 5;
int vel2 = 2;


void setup() {
  //lcd.init();
  //lcd.backlight();

  lcd.begin(16, 2);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  pinMode(Sensor, INPUT_PULLUP);
  Menu();
}

void loop() {

  MenuControl();
  //Time();


}







void Menu()
{
  switch (Option) {        //option instead of 1
    case 1:

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("->Sabor 1");
      lcd.setCursor(0, 1 );
      lcd.print("  Sabor 2");
      break;
    case 2:

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Sabor 1");
      lcd.setCursor(0, 1 );
      lcd.print("->Sabor 2");
      break;
  }
}

void MenuControl()
{
  if (!digitalRead(upButton))
  {
    Option++;
    delay(100);
    Menu();
  }
  if (!digitalRead(downButton))
  {
    Option--;
    delay(100);
    Menu();
  }
  if (!digitalRead(selectButton))
  {
    TimeBeforeSensor = millis();
    OptionSelection();
  }
  if (Option >= 3)
  {
    Option = 1;
    delay(100);
    Menu();
  }

  if (Option <= 0)
  {
    Option = 2;
    delay(100);
    Menu();
  }
}

void Counter()
{

  if (!digitalRead(Sensor))
  {
    Count++;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total Pieces");
  lcd.setCursor(0, 1);
  lcd.print(Count);
  lcd.setCursor(9, 1);
  lcd.print("T:");
  lcd.setCursor(11, 1);
  lcd.print((millis()-TimeBeforeSensor)*1000);

  delay(400);

  if (Option == 1)
  {
    Opcion1();
  }
  else if (Option == 2)
  {
    Opcion2();
  }


}


/*

  void Time();    //Display the total Effiency after finishing the 24 hours
  {
  if ((micros - TimeBeforeSensor) >= 15000) //wait 15000mS.
  {
    lcd.clear
    lcd.setCursor(0, 0);
    lcd.print("Sabor ");
    lcd.print(Option);
    lcd.setCursor(0, 1)
    Effiency = (Count / Vel) * 100;
    lcd.print("E: ");
    lcd.print(Effiency);
  }
  }
*/

void OptionSelection()
{
  switch (Option) {
    case 1:
      Opcion1();
      break;
    case 2:
      Opcion2();
      break;
  }
}

void Opcion1() //Vel1 Selection
{
  if ((millis() - TimeBeforeSensor) >= 12000) //Display the total Effiency after finishing the 24 hours
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sabor ");
    lcd.print(Option);
    lcd.setCursor(0, 1);
    Efficiency = ((float)Count / vel1) * 100.0;
    lcd.print("n: ");
    lcd.print(Efficiency);
    lcd.print("%");
    Stop();
  }
  Counter();

}

void Opcion2() // Vel2 Selection
{
  if ((millis() - TimeBeforeSensor) >= 10000) //Display the total Effiency after finishing the 24 hours
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sabor ");
    lcd.print(Option);
    lcd.setCursor(0, 1);
    Efficiency = ((float)Count / vel2) * 100.0;
    lcd.print("n: ");
    lcd.print(Efficiency);
    lcd.print("%");
    Stop();
  }
  Counter();
}


void Stop()
{
  while (digitalRead(selectButton))
  {
    delay(100);
  }
  Menu();
  Counter = 0;
  Option = 3;
}















