#include "DHT.h"                                                   //including DHT11 library
#define DHTTYPE DHT11                                              //defining DHT type 
#include <ESP8266WiFi.h>                                           //including ESP8266 library for connecting purpose of WIFI to nodemcu
#include <ArduinoJson.h>                                           //including ArduinoJson library
#include <FirebaseESP8266.h>                                       //including FirebaseESP8266 library for working purpose with google firebase  

#define FIREBASE_HOST "mini-project-c9d9c-default-rtdb.firebaseio.com"   //defining firebase host or project name of firebase
#define FIREBASE_AUTH "Sj8v5vrVmtfH8vvN3oBJkCg2JnUGSLKtYi7K7ol4"         //defining secret code of the firebase project   
FirebaseData firebaseData;                                              // Declare the Firebase Data object in the global scope
DHT dht(2,DHTTYPE);                                  //declaring the DHT data object for connecting digital pin 4(Aurduino pin 2) of nodemcu to dht11 for receiving data                
void setup() {
  // put your setup code here, to run once:
dht.begin();
Serial.begin(9600);                    //for printing data on serial monitor
Serial.println("Humidity and temperature\n\n");
delay(700); 
WiFi.begin("Supriyo","su123456789");              //WIFI name and password
while(WiFi.status()!=WL_CONNECTED)                //untill modemcu connected to wifi
{
   Serial.print("....");
   delay(200);
   
}
Serial.println();
Serial.println("Nodemcu is connected!");   //when nodemcu get connected

Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);   //connecting with firebase

}

void loop() {
  // put your main code here, to run repeatedly:
float h=dht.readHumidity();                   //to read humudity from dht11
float t=dht.readTemperature();                //to read temperature in celcius from DHT11
if (isnan(h)||isnan(t))                       //to check whether reading of data from DHT11 is a success or not
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

//String fireHumid=String(h)+String("%");      //for string format
//String fireTemp=String(t)+String("'C");
delay(60000);              //for sending data to firebase inn an interval of 1 minute

Firebase.pushFloat(firebaseData, "SUPRIYO/Humidity", h);       //puhsing humidity value to databse 
Firebase.pushFloat(firebaseData, "SUPRIYO/Temperature", t);    //pushing temperature to database
//Firebase.pushString("/DHT11/Humidity",fireHumid);      //for uploading in string format
//Firebase.pushString("/DHT11/Temperature",fireTemp);

}

 
