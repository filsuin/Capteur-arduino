# Système embarqué avec ESP8266 : Affichage OLED, Mesures BME280 et LED RGB

Ce projet implémente un système embarqué basé sur un microcontrôleur **ESP8266**, conçu pour afficher des informations en temps réel sur un écran OLED, mesurer les données environnementales à l'aide d'un capteur **BME280**, et fournir un retour visuel avec des **LED RGB**.

## Fonctionnalités

- **Connexion WiFi** : Connexion automatique au réseau via WiFiManager.
- **Synchronisation NTP** : Récupération et affichage de l'heure exacte via un serveur NTP.
- **Affichage OLED** : 
  - Heure et date en temps réel.
  - Température, pression atmosphérique et humidité relevées par le capteur BME280.
- **LED RGB** : Scénario lumineux simple avec des couleurs configurables.

## Matériel requis

- **ESP8266** (NodeMCU ou équivalent)
- **Écran OLED** (résolution 128x64, contrôlé via I2C)
- **Capteur BME280** (mesure température, pression et humidité)
- **LED WS2812B** (bande de 4 LED minimum)
- **Alimentation** (adaptée au microcontrôleur et aux LED)

## Dépendances

Le code utilise les bibliothèques suivantes (disponibles via le gestionnaire de bibliothèques Arduino) :
- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [Adafruit_BME280](https://github.com/adafruit/Adafruit_BME280_Library)
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [WiFiManager](https://github.com/tzapu/WiFiManager)

## Installation

1. Clonez ce dépôt sur votre machine :
   ```bash
   git clone https://github.com/votre-utilisateur/votre-repo.git
