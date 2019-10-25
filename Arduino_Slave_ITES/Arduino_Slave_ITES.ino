#include <Wire.h>
#include <ArduinoJson.h>

#define RELE1 3

//Variables
int releLuminarias = 0;

void setup() {
  Wire.begin(8);
  Wire.onReceive(eventoRecibido);
  Wire.onRequest(eventoRequerido);
  Serial.begin(9600);
  Serial.println("Inicia arduino uno");

  pinMode(RELE1,OUTPUT);

}

void loop() {
  delay(100);
}

void eventoRecibido(int n){
  // Recibimos un string json : {"pin" : "3", "estado" : "1" }
  Serial.println("Recibo evento");
  String strJson = "";
  while(Wire.available() > 0 ){
    char c = Wire.read();
    strJson += c;
    Serial.print("DEBUG: "); Serial.println(strJson);
  }

  StaticJsonDocument<100> doc;
  DeserializationError error = deserializeJson(doc, strJson);
  if(error){
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  int pin = atoi(doc["pin"]);
  switch(pin){
    case 3: 
            releLuminarias = atoi(doc["estado"]);
            Serial.print("DEBUG: pin "); Serial.println(pin);
            Serial.print("DEBUG: estado "); Serial.println(releLuminarias);
            digitalWrite(pin, releLuminarias);
        break;
    default:
            Serial.print("ERROR: Pin desconocido");
  }

}
void eventoRequerido(){
  Wire.write("R");
  Serial.write("evento Requerido");
  //Wire.write(releLuminarias);
  Serial.println(releLuminarias);
}
