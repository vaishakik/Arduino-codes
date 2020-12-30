//Valid Command List
//WIFICON|SSID,PASSWORD|
//WIFICON|IoTDemo,devilatitswork94|
//SERVERSET|SERVERADDR,URL|
//SENDDATA|DATA|
//READDATA|
#include <SoftwareSerial.h>

SoftwareSerial esp(9, 10); // RX | TX

int readbyte;

String data;

String ssid = "Rash";   //Wi-Fi ID //hotspot name of mine
String password = "Rashmi24"; //Wi-Fi Password  // my hotspot password

String server = "18.188.2.196"; // Your AWS EC2 instance  //my ip of instance
String url = "control.txt"; // text file //created in my cloud 
//String urlwrite = "testiot.php"; // Your php to write data into server

void setup() {
  Serial.begin(9600);
  esp.begin(9600); //Important, Dont Change
  Serial.println("Initializing");
  delay(1000); //Giving time for Wi-Fi module to start
  Serial.println("Initialized");
 
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
 

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
 
}

// the loop function runs over and over again forever
void loop() {
  esp.flush();
  if(Serial.available()){
    esp.flush();
    readbyte = Serial.read();
    if(readbyte=='1'){
      
       Serial.println("Reading-Data");
       esp.println("READDATA|");
       esp.flush();
       while (!esp.available()) {
          Serial.print("."); // wait for serial respone from Wi-Fi Module
          delay(1000);
        }
       
        while(esp.available()){
              data = esp.readStringUntil('\n');
              if(data)
              {
                 Serial.println(data);
              }
              else
              {
                 Serial.println("no data read");
              }
               Serial.print(data);
              data.trim();
              delay(100);
              esp.flush();
             if(data == "1")
            {
                digitalWrite(10, HIGH);
                digitalWrite(11, HIGH);
                digitalWrite(12,LOW);
                Serial.println("Motor runing");
                delay(2000);
                digitalWrite(10, HIGH);
                digitalWrite(11, LOW);
                digitalWrite(12,LOW);
                //digitalWrite(LED_BUILTIN, LOW);
                Serial.print("Data");
                Serial.print(data);
                Serial.println("Motor stopped");
              }
             if(data == "2"){
                //digitalWrite(LED_BUILTIN, LOW);
                //Serial.println("LED LOW");
                //Serial.print("Data is");
                //Serial.print(data);
             //   Serial.println("Data");
                   digitalWrite(10, HIGH);
                digitalWrite(11, LOW);
                digitalWrite(12,HIGH);
                Serial.println("Motor runing---unlocking");
                delay(2000);
                digitalWrite(10, HIGH);
                digitalWrite(11, LOW);
                digitalWrite(12,LOW);
              }

        }
    }
    //else if(readbyte=='2'){
      //esp.println("SENDDATA|~OK~|");
      //Serial.print("Data Sent Successfully");
    }
   
    /*//else if(readbyte=='3')
    //{
      //  Serial.print("Setting default Server to -");
        //Serial.print(server);
        //Serial.print(" & URL -");
        Serial.println(url);
        esp.flush();
        esp.print("SERVERSET|");
        esp.print(server);
        esp.print(",");
        esp.print(url);
        esp.println("|");
       
        delay(500);
     
        while (!esp.available()) {// wait for serial respone from Wi-Fi Module
          Serial.print(".");
          delay(500);
        }
        if(esp.available()){
          data = esp.readString();
          delay(150);
          Serial.println("Server Setting");
        }
    }
    else if(readbyte=='4')
    {
        Serial.print("Setting default Server to -");
        Serial.print(server);
        Serial.print(" & URL -");
        Serial.println(urlwrite);
        esp.flush();
        esp.print("SERVERSET|");
        esp.print(server);
        esp.print(",");
        esp.print(urlwrite);
        esp.println("|");
       
        delay(500);
     
        while (!esp.available()) {// wait for serial respone from Wi-Fi Module
          Serial.print(".");
          delay(500);
        }
        if(esp.available()){
          data = esp.readString();
          delay(150);
          Serial.println("Server Setting");
        }
    }
  }*/
  delay(2000);
}
