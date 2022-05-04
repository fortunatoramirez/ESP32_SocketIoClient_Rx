#include <WiFi.h>
#include <SocketIoClient.h>

#define ONBOARD_LED 2

const char*       ssid     = "NOMBRE_DE_LA_RED"; 
const char*       password = "CONTRASENA";
const char*       server   = "IP.DEL.SER.VIDOR";
const uint16_t    port     = 5001; //Puerto del servidor

SocketIoClient socketIO;

void setup() {
  pinMode(ONBOARD_LED,OUTPUT);
  Serial.begin(115200);
  conectar_WiFiSTA();
  socketIO.begin(server, port);
  socketIO.on("desde_servidor",procesar_mensaje_recibido);
}

void loop() {
  socketIO.loop();
  //delay(100);
}

void conectar_WiFiSTA()
{
   delay(10);
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
   Serial.println("");
   Serial.print("Conectado a STA:\t");
   Serial.println(ssid);
   Serial.print("My IP Address:\t");
   Serial.println(WiFi.localIP());
}

void procesar_mensaje_recibido(const char * payload, size_t length) {
 Serial.printf("Mensaje recibido: %s\n", payload);
 String paystring = String(payload);
 if(paystring == "ON")
 {
  digitalWrite(ONBOARD_LED,HIGH);
 }
 else if(paystring == "OFF")
 {
  digitalWrite(ONBOARD_LED,LOW);
 }
}
