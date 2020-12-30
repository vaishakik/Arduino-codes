#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>





#include <SoftwareSerial.h>
SoftwareSerial esp(9,10); // RX | TX
#define FIREBASE_HOST "shiv3-e3f47.firebaseio.com"
#define FIREBASE_AUTH "Y0554vDycXHABcmJ4hLJKAwCeV17uh7ejdyXdHM"
String data;

String ssid = "Why?shock! mobile";   //Wi-Fi ID
String password ="kuppast9"; //Wi-Fi Password

void setup() 
{

  
  Serial.begin(9600);
  esp.begin(9600); //Important, Dont Change
  Serial.println("Initializing");
  delay(1000); //Giving time for Wi-Fi module to start
  Serial.println("Initialized");
  //Connect to Wi-Fi
  Serial.print("Connecting to -");
  Serial.println(ssid);
 
  esp.flush();
  esp.print("WIFICON|");
  esp.print(ssid);
  esp.print(",");
  esp.print(password);
  esp.println("|");
  delay(500);
 
   while (!esp.available()) {// wait for serial respone from Wi-Fi Module
    Serial.print(".");
    delay(500);
  }
  if(esp.available()){
    data = esp.readString();
    delay(150);
    Serial.println(data);
  }
  esp.flush();
  delay(3000); 


   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   Firebase.set("Testing", 0);

   Firebase.setInt("Testing", 88);
}

void loop()
{
}

