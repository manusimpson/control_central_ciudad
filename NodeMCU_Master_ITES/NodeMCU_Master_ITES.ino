#include <ESP8266WiFi.h>
#include <Wire.h>

#define LED 2

const char* ssid = "ITESLAB";
const char* password = "iteslab2015";

//const char* ssid = "Camp Krusty";
//const char* password = "simpson270";


WiFiServer server(80);

void setup() {
  pinMode(LED, OUTPUT);
  Wire.begin(5, 4);
  
  Serial.begin(9600);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  server.begin();
  Serial.println("NodeMCU Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");


}


void loop() {

   //SERVIDOR WEB
  
  delay(300);  
  WiFiClient client = server.available();
  if (!client) {
    digitalWrite(LED, 1);
    return;
  }
  digitalWrite(LED, 0);
  // Wait until the client sends some data
  Serial.println("Cliente nuevo Conectado!");
  while(!client.available()){
    delay(1);
  }

   // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/RELE=ON") != -1)  {
    Serial.println("Prendo");
    Wire.beginTransmission(8);
    Wire.write("{\"pin\":\"3\",\"estado\":\"1\"}");
    Wire.endTransmission();
    delay(300);
    consultoEstados();
  }
  if (request.indexOf("/RELE=OFF") != -1)  {
    Serial.println("Apago");
    Wire.beginTransmission(8);
    Wire.write("{\"pin\":\"3\",\"estado\":\"0\"}");
    Wire.endTransmission(8);
  }

    // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Rele: ");
 
  client.println("<br><br>");
  client.println("<a href=\"/RELE=ON\"\"><button>Prender</button></a>");
  client.println("<a href=\"/RELE=OFF\"\"><button>Apagar</button></a><br />");

  client.println("</html>");
 
  delay(1);
  Serial.println("No hay cliente conectados");
  Serial.println("");

}

void consultoEstados(){
  //ESCUCHO SLAVE
  Wire.requestFrom(8, 6);   // request 6 bytes from slave device #8
  
  while(Wire.available()) { // slave may send less than requested
    char c = Wire.read();   // receive a byte as character
    Serial.print(c);        // print the character
    delay(100);
  }
  Serial.println();
}
