#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <string>
//#include <SoftwareSerial.h>

//SoftwareSerial arduinomega(3,1);  //Rx,Tx

// Preset
#define FIREBASE_HOST "test-future-of-heat-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "p5SgqxdrZ40qbpaN5iH2YWfNqOpdYjVYkNaphcAR"
#define WIFI_SSID "ESP"
#define WIFI_PASSWORD "TeamHeat"

FirebaseData fbdo;
String ele_home = "/electric_homes";
String ele_vehicle = "/electric_vehicles";
String weather = "/weather";
String message;
//Variables
unsigned int load[12];
unsigned int homenum;
unsigned int vehicnum;
unsigned int weathernum;
unsigned int enable;

unsigned int holdhomenum=0;
unsigned int holdvehicnum=0;
unsigned int holdweathernum=0;

//Serial Communication

void setup() 
{

  Serial.begin(9600);
  //Serial.swap();
  
  //WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //Firebase.reconnectWiFi(true);
}

void loop ()
{
  if(Firebase.getInt(fbdo,"/active"))
  {
    enable = fbdo.intData();
  }

  while (enable == 1)
 { 
   if(Firebase.getInt(fbdo,ele_home))
  {
    //Serial.print("Electric homes:");
    //Serial.println(fbdo.intData());
    homenum = fbdo.intData();
  }

    if(Firebase.getInt(fbdo, ele_vehicle))
  {
    //Serial.print("Electric vehicles:");
    //Serial.println(fbdo.intData());
    vehicnum = fbdo.intData();
  }

  if(Firebase.getInt(fbdo, weather))
  {
    //Serial.print("Weather Severity:");
    //Serial.println(fbdo.intData());
    weathernum = fbdo.intData();
  }
  message = "<" + String(homenum)+ "," + String(vehicnum)+ "," + String(weathernum)+">\n";
  if (homenum != holdhomenum || holdvehicnum != vehicnum || holdweathernum != weathernum)
  {
    Serial.print(message);
  }
  holdhomenum = homenum;
  holdvehicnum = vehicnum;
  holdweathernum = weathernum;
 }
}
