#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>
#include<DHT.h>
#define FIREBASE_HOST "enter-host-name"
#define FIREBASE_AUTH "enter-auth"
#define WIFI_SSID "enter-wifi-ssid"
#define WIFI_PASSWORD "enter-wifi-passwd"
#define DHTPIN 2 //Data pin of DHT 11 , D4 in NodeMcu
#define DHTTYPE DHT11 /DHT11
DHT dht(DHTPIN,DHTTYPE);
void setup() {
 Serial.begin(115200);
 WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
 Serial.print("connecting");
 while(WiFi.status()!=WL_CONNECTED){
  Serial.print(".");
  delay(500);
 }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Temperature_Sensor();
 }
 
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
void Temperature_Sensor(){
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  while(WiFi.status()!=WL_CONNECTED){
  delay(500);
  Serial.print(".");
 }
  dht.begin();
  Serial.println("");
  Serial.println("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST);
  }


void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Humidity",h);
  delay(200);
}
