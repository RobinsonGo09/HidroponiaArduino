#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
//DHTP11
#include <DHT.h>
#include <DHT_U.h>
#define Type DHT11
int dhtPin = 2;
DHT HT(dhtPin, Type);
int humidity;
float tempC;
float tempF;
int dt (3000);
//Sensor humedad
int humedadPin = A0;
int humedadSuelo;

void setup(){
 display.begin(SSD1306_SWITCHCAPVCC); // Inicia el display OLED
 display.clearDisplay(); // Borrar imagen en el OLED
 display.setTextSize(1); // Tamaño del texto
 display.setTextColor(WHITE); // Definir color del texto (WHITE-BLACK)
 display.setCursor(25,15); // Definir posición Columna (25) Fila (15)
 display.println("Bienvenidos"); // Carga la información al buffer
 display.display(); // Actualiza display con datos en Buffer
 delay(3000); // Demora de 3 segundos.
  Serial.begin(9600);
 HT.begin();
}
void loop() {

  humidity = HT.readHumidity();
  tempC = HT.readTemperature();
  tempF = HT.readTemperature(true);
  humedadSuelo = analogRead(humedadPin);
  humedadSuelo = constrain (humedadSuelo, 0, 1023); /* Rango de medición */
  humedadSuelo = map (humedadSuelo, 0, 1023, 100,0); /* valores porcentuales dentro del rango */
  Serial.print("Humedad Relativa: ");
  Serial.print(humidity);
  Serial.print("% / Temperatura: ");
  Serial.print(tempC);
  Serial.print("ºC / ");
  Serial.print(tempF);
  Serial.println("ºF");
  display.clearDisplay(); // Borrar imagen en el OLED
  display.setTextSize(1);
  display.setCursor(0,0); // Definir posición Columna (0) Fila (0)
  display.print("Humedad Relativa: ");
  display.print(humidity); // Carga la información al buffer
  display.print("%");
  display.setCursor(0,10); // Definir posición inicio texto Columna (0) Fila (15)
  display.print("Temperatura: ");
  display.print(tempC); // Carga la información al buffer
  display.print(" C");
  display.setCursor(0,20); // Definir posición inicio texto Columna (0) Fila (15)
  display.print("Humedad suelo: ");
  display.print(humedadSuelo); // Carga la información al buffer
  display.print("%");
  display.display(); // Actualiza display con datos en Buffer
  delay(2000); // Demora de 2 segundos
}
