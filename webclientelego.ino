//Valid Command List
//WIFICON|SSID,PASSWORD|
//WIFICON|IoTDemo,devilatitswork94|
//SERVERSET|SERVERADDR,URL|
//SENDDATA|DATA|
//READDATA

#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial WFserial(4, 5); // RX | TX

int incomingByte;
int wificonnect = 0;
int wificonnectstate = 0;

String serialcmd;
String data;


String url;
String finalurl;

char ssid[50] = "";
char password[50] = "";
char serveraddr[] = "";

String webline;
String ssidstring;
String passwordstring;
String serveraddrstring;

void setup() {
  Serial.begin(9600);
  WFserial.begin(9600);
  delay(1000);
  Serial.println("Initialization Complete");
}

void loop() {
  serialcmd = "";
  finalurl = "";
  //Read Serial buffer for inputs
  if (WFserial.available()){
        serialcmd = WFserial.readStringUntil('|');
        delay(100);

        if(serialcmd == "WIFICON"){
          wificonnect++;
         
          ssidstring = WFserial.readStringUntil(',');
          delay(100);    
          passwordstring = WFserial.readStringUntil('|');
          delay(100);
          Serial.println(ssidstring);
          Serial.println(passwordstring);
         
          if(wificonnect>0){
            WiFi.disconnect(true);  // Erases SSID/password
          }
         
          ssidstring.toCharArray(ssid,ssidstring.length()+1);
          delay(500);
          passwordstring.toCharArray(password,passwordstring.length()+1);
          delay(500);
         
          Serial.print("Connecting to ");
          Serial.println(ssid);
         
          WiFi.begin(ssid,password);
          delay(500);
         
          while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");    
          }

          Serial.print("WiFi-Connected-");
          Serial.println(ssid); 
          Serial.print("IP addr -");
          Serial.println(WiFi.localIP());
          WFserial.print("Connected -");
          WFserial.println(WiFi.localIP());
          wificonnectstate = 1;
        }

        if(serialcmd == "SERVERSET"){
          serveraddrstring = WFserial.readStringUntil(',');
          serveraddrstring.toCharArray(serveraddr,serveraddrstring.length()+1);
          delay(500);
             
          url = WFserial.readStringUntil('|');
          delay(100);
          Serial.print("Server set to ");
          Serial.println(serveraddr);
          Serial.print("URL set to ");
          Serial.println(url);
          WFserial.println("OK");
        }

        if(serialcmd == "SENDDATA"){
          data = WFserial.readStringUntil('|');
          delay(100); 

          finalurl = "/" + url + "?data=" + data;
          Serial.println(finalurl);
          WiFiClient client;
          if (client.connect(serveraddr,80)) {
            client.print(String("GET ") + finalurl + " HTTP/1.1\r\n" +
            "Host: "+serveraddr+"\r\n" +
            "Connection: close\r\n\r\n");
            Serial.println("!!!!DATA POSTED!!!!");
          }
            if (client.connected()) {
              client.stop();  // DISCONNECT FROM THE SERVER
              WFserial.println("OK");
            }
        }

        if(serialcmd == "READDATA"){
          Serial.println("Reading Data");
          finalurl = "/" + url;
          WiFiClient client;
          
          if (client.connect(serveraddr,80)) {
            client.print(String("GET ") + finalurl + " HTTP/1.1\r\n" +
            "Host: "+serveraddr+"\r\n" +
            "Connection: close\r\n\r\n");
          }

          while (!client.available()) {// wait for serial respone from Wi-Fi Module
            Serial.print(".");
            delay(500);
          }
          while(client.available()){
                if(client.read()=='~'){
                  webline = client.readStringUntil('~');
                }
                
          }
          Serial.print("Read Data is - ");
          Serial.println(webline);
          WFserial.println(webline);
          
          client.stop();
          client.flush();
          finalurl = "";
        }


        incomingByte = Serial.read();
        if (incomingByte == '\n') {
          //Read last char from buffer
        }
     
  }

  if(serveraddrstring != "" && wificonnectstate>0){
    //Pulse Check Routine
    WiFiClient client;
    if (!client.connect(serveraddr,80)) {
      Serial.println("Pulse Error");
      WFserial.println("Pulse Error");
      return;
    }
    else{
      Serial.println("Pulse Success");
    }
    delay(1000);
   
  }
 
}
