
#include <LiquidCrystal.h>

double refV;
const int buttonPin1 = 10;
const int buttonPin2 = 9;
const int buttonPin3 = 8;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int speakerPin = 13;
double tL=35;
double tH=36;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  analogReference(DEFAULT);
  refV=5;
  delay(60000);
  Serial.begin(9600);
  Serial.print("%tL is: ");
  Serial.println(tL);
  Serial.print("%tH is: ");
  Serial.println(tH);
  Serial.println("%temp(C)     status        time");
  Serial.println("%------------------------------");
  Serial.println("%Beginning of Data:");
}

int x = 5000;
int loopCounter = 0;

void loop()
{
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  if (buttonState3 == HIGH && buttonState1 == HIGH && 50 <= tH && tH <= 55)
  {
    tL = 54;
    tH = 55;
    tone(13,500,1000);
    lcd.begin(16,1);
    lcd.print("Max tH: ");
    lcd.print(tH);
    delay(1000);
    lcd.clear();
    delay(100);
    lcd.print("Max tH: ");
    lcd.print(tH);
    delay(1000);
    lcd.clear();
    delay(100);
    lcd.print("Max tH: ");
    lcd.print(tH);
    delay(1000);
    lcd.clear();
    delay(100);
  }
  
  if (buttonState3 == HIGH && buttonState1 == HIGH && tH <= 50)
  {
    tL = tL + 5;
    tH = tH + 5;
    Serial.print("%tL changed to: ");
    Serial.println(tL);
    Serial.print("%tH changed to: ");
    Serial.println(tH);
    tone(13,400,300);
    delay(500);
  }
  if (buttonState3 == HIGH && buttonState2 == HIGH && 25 > tL && tL>= 20)
  {
    tL = 20;
    tH = 21;
    tone(13,500,1000);
    lcd.begin(16,1);
    lcd.print("Min tL: ");
    lcd.print(tL);
    delay(1000);
    lcd.clear();
    delay(100);
    lcd.print("Min tL: ");
    lcd.print(tL);
    delay(1000);
    lcd.clear();
    delay(100);
    lcd.print("Min tL: ");
    lcd.print(tL);
    delay(1000);
    lcd.clear();
    delay(100);
  }
  if (buttonState3 == HIGH && buttonState2 == HIGH && tL >= 25)
  {
    tL = tL - 5;
    tH = tH - 5;
    Serial.print("%tL changed to: ");
    Serial.println(tL);
    Serial.print("%tH changed to: ");
    Serial.println(tH);
    tone(13,100,300);
    delay(500);
  }
  if (buttonState3 == LOW && buttonState1 == HIGH && tH == 55)
  {
    tone(13,500,1000);
    lcd.begin(16,1);
    lcd.print("Max tH: ");
    lcd.print(tH);
    delay(1000);
    lcd.clear();
    delay(100);
    lcd.print("Max tH: ");
    lcd.print(tH);
    delay(1000);
    lcd.clear();
    delay(100);
    lcd.print("Max tH: ");
    lcd.print(tH);
    delay(1000);
    lcd.clear();
    delay(100);
  }
  
  if (buttonState3 == LOW && buttonState1 == HIGH && tH <= 54.5)
  {
    tL = tL + 0.5;
    tH = tH + 0.5;
    Serial.print("%tL changed to: ");
    Serial.println(tL);
    Serial.print("%tH changed to: ");
    Serial.println(tH);
    tone(13,300,100);
    delay(500);
  }
  if (buttonState3 == LOW && buttonState2 == HIGH && tL == 20)
  {
    tone(13,500,1000);
    lcd.begin(16,1);
    lcd.print("Min tL: ");
    lcd.print(tL);
    delay(1000);
    lcd.clear();
    delay(100);
    lcd.print("Min tL: ");
    lcd.print(tL);
    delay(1000);
    lcd.clear();
    delay(100);
    lcd.print("Min tL: ");
    lcd.print(tL);
    delay(1000);
    lcd.clear();
    delay(100);
  }
  
  if (buttonState3 == LOW && buttonState2 == HIGH && tL >= 20.5)
  {
    tL = tL - 0.5;
    tH = tH - 0.5;
    Serial.print("%tL changed to: ");
    Serial.println(tL);
    Serial.print("%tH changed to: ");
    Serial.println(tH);
    tone(13,200,100);
    delay(250);
  }
  if(loopCounter < x)
  {
    int acc=0;
    int N=10;
    for(int i = 0 ; i < N ; i++)
    {
      acc += analogRead(0);
    }
    double voltage = refV*acc/1023./(double(N));
    double tempC = 1. + voltage*100.;
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print(tL);
    lcd.print(" to ");
    lcd.print(tH);
    lcd.setCursor(0,1);
    lcd.print(tempC);
    Serial.print(tempC);
    Serial.print("          ");
    if(tempC < tL) digitalWrite(7, HIGH);
    if(tempC > tH) digitalWrite(7, LOW);
    int status = digitalRead(7);
    Serial.print(status);
    Serial.print("          ");
    long time;
    time = millis()-60000;
    Serial.println(time);
    ++loopCounter;
  } 
}
