
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <time.h>

#define WIDTH 128
#define HEIGHT 64

#include  <Adafruit_NeoPixel.h>
#define LED_PIN D4
#define NUM_LED 4
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB


Adafruit_NeoPixel LED(NUM_LED,LED_PIN,NEO_GRB+NEO_KHZ800);

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);

Adafruit_BME280 bmp;

WiFiManager WM;
const char* ssid = "CalendrierNassim"; 
const char* password = "calendrier";

const int decalage = 1;  
const int delaiDemande = 5 * 60; 

unsigned long derniereDemande = millis(); // moment de la plus récente demande au serveur NTP
unsigned long derniereMaJ = millis(); // moment de la plus récente mise à jour de l'affichage de l'heure

time_t maintenant;
struct tm * timeinfo;

unsigned long heure_courante = millis();
unsigned long dernier_affichage = millis();

bool gros=false;
void setup() {
  
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20, 10);
  display.print("O R E ");
  display.setTextSize(1);
  display.setCursor(0,40);
  display.println("   En attente d'une ");
  display.setCursor(0,50);
  display.print("    connexion WiFi");
  display.display();
  delay(4000);

  WiFi.mode(WIFI_STA); 
 while(!WM.autoConnect(ssid, password))
 {
  Serial.print(".");
 }
  Serial.print("Connecte");
 configTime(decalage * 3600, 0, "ntp.unice.fr"); 
 while (time(nullptr) <= 100000) {
  // Serial.print(".");
  delay(1000);
 }
 time(&maintenant);
  while(!bmp.begin(0x76))
  {
    Serial.println("PAS TROUVE");
    delay(1000);
  }
LED.begin();
ledScenario();
}


void loop() {
  heure_courante=millis();
  if((heure_courante-dernier_affichage)>2000)
  {
    gros=!gros;
    dernier_affichage=millis();
  }
  if (gros)
  {
    bigDisplay();
  }
  else 
  {
    updateDisplay();
  }
if ((millis() - derniereDemande) >=  delaiDemande * 1000 ) {
    time(&maintenant);
    derniereDemande = millis();
  }
  // est-ce que millis() a débordé?
 if (millis() < derniereDemande ) {
    time(&maintenant);
    derniereDemande = millis();
  }
  // est-ce le moment de raffraichir la date indiquée?
  if ((millis() - derniereMaJ) >=   1000 ) {
    maintenant = maintenant + 1;
    afficheHeureDate();
    derniereMaJ = millis();
  }
  
}
void bigDisplay() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  timeinfo = localtime(&maintenant);
  if ((timeinfo->tm_hour ) < 10) {
    display.print("0");
  }
  display.print(timeinfo->tm_hour );  // heure entre 0 et 23
  display.print(":");
  if (timeinfo->tm_min < 10) {
    display.print("0");
  }
  display.print(timeinfo->tm_min);   // timeinfo->tm_min: minutes (0 - 59)
  display.display();
}
void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(25,2);
  display.print("Temperature : ");
  display.setTextColor(WHITE);
  display.setCursor(20,32);
  display.setTextSize(2);
  display.print(bmp.readTemperature());
  display.println(" C");
    display.display();
    delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(30, 2);
  display.print("Pression:");
  display.setCursor(20,32);
  display.setTextSize(2);
  display.print(int(bmp.readPressure()/100.0)); 
  display.println(" hPa");
  display.display();
  delay(2000);
  display.clearDisplay();
   display.setTextSize(1);
  display.setCursor(30,2);
  display.print("Humidite :");
  display.setCursor(25,32);
  display.setTextSize(2);
  display.print(bmp.readHumidity());
  display.print(" %");
   display.display();
  delay(2000);
  display.setCursor(0,55);
 display.clearDisplay();
  afficheHeureDate();
  display.display();
}
void afficheHeureDate() {
  timeinfo = localtime(&maintenant);
  display.setCursor(30, 20);
  display.setTextSize(2);
  if (timeinfo->tm_mday < 10) {
    display.print("0");
  }
  display.print(timeinfo->tm_mday);  // timeinfo->tm_mday: jour du mois (1 - 31)
  display.print("-");
  if ((timeinfo->tm_mon + 1) < 10) {
    display.print("0");
  }
  display.print(timeinfo->tm_mon + 1);    // timeinfo->tm_mon: mois (0 - 11, 0 correspond à janvier)
  display.setCursor(35,35);
  display.print(timeinfo->tm_year + 1900);  // timeinfo->tm_year: tm_year nombre d'années écoulées depuis 1900
  delay(2000);
}
void ledScenario(){
  LED.setPixelColor(0,LED.Color(0,255,255));
  LED.setPixelColor(1,LED.Color(0,255,255));
  LED.setPixelColor(2,LED.Color(0,255,255));
  LED.setPixelColor(3,LED.Color(0,255,265));
  LED.show();
}
