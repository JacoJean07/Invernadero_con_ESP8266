
#include <DHT.h>
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <Arduino.h>



//credenciales wifi
const char *ssid = "Green Sense";
const char *password = "greensense123";

//credenciales del proyecto en firebase
const char *FIREBASE_HOST = "https://greensense-8ec25-default-rtdb.firebaseio.com";
const char *FIREBASE_AUTH = "NlbbsXkJVCiyVN4sQlowe2DholEAG9Qgu9E46irf";

// fire base data object in the global scope
FirebaseData firebaseData;

// Nodo "Riego" en Firebase
const char* RIEGO_PATH = "/Riego";

bool iterar = true;

int sensor = 2;
int temp, humedad;
const int humedadsuelo = A0;
const int relayPin = 4;

DHT dht(sensor, DHT11);

void setup()
{
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Apagar la bomba al inicio

  Serial.begin(115200);
  dht.begin();
  pinMode(humedadsuelo, INPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() !=WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
  }
  Serial.print("\nConectado al wifi");
  Serial.available();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  



String nodo = "realtime";

while (iterar)
{
  
  


  int SensorValue = analogRead(humedadsuelo);
  // Calcula el porcentaje de humedad
  int porcentajeHumedad = (SensorValue / 1023.0) * 100.0;
  
  humedad = dht.readHumidity();
  temp = dht.readTemperature();

  Serial.print("Temperatura: "); Serial.print(temp);
  Serial.print(" ºC, Humedad: "); Serial.print(humedad); Serial.println("%");
  Serial.print("Humedad del suelo: "); Serial.print(porcentajeHumedad); Serial.println("%");

// Leer el valor del nodo "Riego" en Firebase
  if (Firebase.getBool(firebaseData, RIEGO_PATH)) {
    if (firebaseData.to<bool>()) {
      // Si Riego es igual a 1, encender la bomba de agua
      digitalWrite(relayPin, LOW);
    } else {
      // Si Riego es igual a 0, apagar la bomba de agua
      digitalWrite(relayPin, HIGH);
    }
  } else {
    // Error al leer el valor de Riego desde Firebase
    Serial.println("Error al leer el valor de Riego desde Firebase.");
  }
  
  delay(1000);

  //escribir datos
  Firebase.setFloat(firebaseData, nodo + "/Temperatura", static_cast<int>(temp));
  Firebase.setFloat(firebaseData, nodo + "/Humedad_A", static_cast<int>(humedad));
  Firebase.setFloat(firebaseData, nodo + "/Humedad_Suelo", static_cast<int>(porcentajeHumedad));
}
}
