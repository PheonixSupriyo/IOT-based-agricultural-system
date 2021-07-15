
#include "DHT.h"                                                   //including DHT11 library
#define DHTTYPE DHT11                                              //defining DHT type 
#include <ESP8266WiFi.h>                                           //including ESP8266 library for connecting purpose of WIFI to nodemcu
#include <ArduinoJson.h>                                           //including ArduinoJson library
#include <FirebaseESP8266.h>                                       //including FirebaseESP8266 library for working purpose with google firebase  

#define FIREBASE_HOST "mini-project-c9d9c-default-rtdb.firebaseio.com"   //defining firebase host or project name of firebase
#define FIREBASE_AUTH "Sj8v5vrVmtfH8vvN3oBJkCg2JnUGSLKtYi7K7ol4"         //defining secret code of the firebase project   
FirebaseData firebaseData;                                              // Declare the Firebase Data object in the global scope
DHT dht(4,DHTTYPE);                                  //declaring the DHT data object for connecting digital pin 2(Aurduino pin 4) of nodemcu to dht11 for receiving data                
void setup() {
  // put your setup code here, to run once:  
unsigned long init_time=millis();                          //For observing time 

dht.begin();
Serial.begin(9600);           //for printing data on serial monitor
pinMode(5,OUTPUT);             //declaring pin 5 for output   
Serial.println("Humidity and temperature\n\n");

digitalWrite(5,HIGH);                             //PIN at HIGH logic
WiFi.begin("Supriyo","su123456789");              //WIFI name and password
while(WiFi.status()!=WL_CONNECTED)               //untill modemcu connected to wifi
{
  Serial.print("....  ");
 delay(500);
   
}
//Serial.println();
Serial.println("Nodemcu is connected!");   //when nodemcu get connected

Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);   //connecting with firebase
Serial.println(millis()-init_time);            //provide time for completion upto firebase connection


float h=dht.readHumidity();                   //to read humudity from dht11
float t=dht.readTemperature();                //to read temperature in celcius from DHT11
if (isnan(h)|| isnan(t))              //to check whether reading of data from DHT11 is a success or not
{
  Serial.println("Failed to read from DHT sensor");
  return;
}
Serial.print("current Humidity=");
Serial.print(h);                                    //printing humidity on serial monitor
Serial.print("  and ");
Serial.print("temperature=");
Serial.print(t);                                 //printing temperature on serial monitor
Serial.println("'c");
digitalWrite(5,LOW);                              //pin 5 at low logic

Firebase.pushFloat(firebaseData, "SUPRIYO/Humidity", h);    //puhsing humidity value to databse 
Firebase.pushFloat(firebaseData, "SUPRIYO/Temperature", t);    //pushing temperature to database
  
Serial.println(millis()-init_time);

Serial.println("going to deep sleep for 59 minutes and 45 seconds");  
ESP.deepSleep(3585e6);     //going for deep sleep

}
void loop()
{
}

 
