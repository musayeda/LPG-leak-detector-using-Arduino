#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

int gasValue = A0; // smoke / gas sensor connected with analog pin A1 of the arduino 
int data = 0;
int buzzer = 11; //BUZZER

void setup()
{
pinMode(buzzer, OUTPUT); // BUZZER  
randomSeed(analogRead(0));
mySerial.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
lcd.begin(16,2);
pinMode(gasValue, INPUT);
lcd.print (" Gas Leakage ");
lcd.setCursor(0,1);
lcd.print (" Detector Alarm ");
delay(3000);
lcd.clear();
}

void loop()
{

data = analogRead(gasValue);

Serial.print("Gas Level: ");
Serial.println(data);
lcd.print ("Gas Scan is ON");
lcd.setCursor(0,1);
lcd.print("Gas Level: ");
lcd.print(data);
delay(1000);

if ( data > 500) //
{
SendMessage();
Serial.print("Gas detect alarm");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Exceed");
lcd.setCursor(0,1);
lcd.print("SMS Sent");
delay(1000);
tone(buzzer, 1000); // Send 1KHz sound signal...


}
else
{
Serial.print("Gas Level Low");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Normal");
noTone(buzzer);  

}
delay(1000);
lcd.clear();
}


void SendMessage()
{
Serial.println("I am in send");
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+8801319433552\"r");  //Replace x with mobile number
delay(1000);
//mySerial.println("AT+CMGS=\"+8801798504299\"\r"); // Replace x with mobile number
//delay(1000);
mySerial.println("Excess Gas Detected. Open Windows");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}
