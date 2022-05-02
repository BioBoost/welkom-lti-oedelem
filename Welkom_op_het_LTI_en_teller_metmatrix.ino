#include <Wire.h>               // Library voor i2c communicatie van arduino
#include "rgb_lcd.h"            // Library inladen voor het RGB LCD display
#include <Adafruit_NeoPixel.h>  // Library voor AdaFruit NeoPixels (slierten, matrices, ...)

// Hieronder geven we aan op welke I/O de NeoPixels zijn aangesloten.
#define NEOPIXEL_PIN  6

// Vervolgens dienen we aan te geven uit hoeveel NeoPixels de matrix bestaat.
// Voor jullie display is dit dus 8x8 = 64
#define NUMPIXELS     64

// Dit is een object dat de NeoPixel matrix voorstelt.
// We dienen hierbij volgende parameters mee te geven zodat
// de library weet wat voor soort NeoPixels we gebruiken, hoeveel
// LEDs er zijn en waar we ze hebben aangesloten op de Arduino.
// - NUMPIXELS: het aantal pixels in totaal (64 in ons geval)
// - NEOPIXEL_PIN: de pin (I/O) waarop de matrix is aangesloten (6 in dit geval)
// - NEO_GRB + NEO_KHZ800: het type (GRB) en hoe de communicatie dient te gebeuren (800KHz)
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Dit is een object dat het LCD display voorstelt.
// Via dit kan je communiceren met de hardware.
// Intern in de library wordt de I2C bus opgezet.
// Op de Arduino UNO zit maar 1 I2C poort. Dus vandaar
// dat je eigenlijk geen keuze hebt. Alle connectoren op
// het shield komen op dezelfde bus terecht.
rgb_lcd lcd;

// Dit zijn de 3 kleurcomponenten van de RGB LCD achtergrond.
// Deze zijn 'const' (constant) omdat we die tijdens het runnen
// van de code niet aanpassen.
const int colorR = 0;
const int colorG = 20;
const int colorB = 0;

// Deze variabel houdt het aantal bezoekers bij. We zetten deze
// hier (globaal) omdat we de waarde willen behouden over de verschillende
// iteraties van loop() heen. Moesten we de variabel in loop() zelf
// definiëren zou deze elke iteratie opnieuw worden gemaakt en op 0 worden gezet.
int tellerbezoekers = 0;

// De setup() functie wordt bij het starten 1-malig aangeroepen.
// Hier stellen we hardware in en kunnen we taken uitvoeren die
// enkel 1 maal moeten gebeuren tijdens het starten van de code
void setup() {
    // Hier stellen we pin 4 in als INPUT. Hier kunnen we dan de knop aan
    // koppelen en inlezen.
    pinMode(4, INPUT);
  
    // Configureer het display object zodat het weet uit
    // hoeveel characters (16) en rijen (2) het display bestaat.
    // Dit moeten we doen omdat de library ook kan gebruikt worden
    // grotere en kleinere displays van Adafruit.
    lcd.begin(16, 2);

    // Hier stellen we de achtergrondkleur in op onze gekozen waarde.
    // Deze bestaat uit de Rood - Green - Blauw componenten
    lcd.setRGB(colorR, colorG, colorB);

    // Vervolgens tonen we de tekst "Welkom" op het display.
    // Dit komt standaard links bovenaan te staan
    lcd.print("Welkom");

    // Met setCursor(kolom, rij) kunnen we kiezen om tekst op
    // een andere plaats te zetten op het display.
    // We tellen hierbij vanaf 0. Dus 2de rij = 1.
    // Merk dat enkel de karakters van het display worden overschreven
    // via print(). Dus met andere woorden, de "Welkom" op de lijn erboven
    // blijft netjes staan
    lcd.setCursor(0, 1);

    // De cursor staat nu links onderaan (2de rij). Daar kunnen we dan de tekst
    // laten verschijnen met print().
    lcd.print("op het LTI");

    ////// NEOPIXELS //////

    // De NeoPixels dienen te worden geïnitialiseerd vooraleer we er iets mee doen.
    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

    // Door de clear() methode aan te roepen zorgen we er voor dat alle LEDs uit worden
    // gezet.
    pixels.clear();

    // Hier gaan we alle NeoPixels overlopen met een for-loop. We gaan hierbij
    // alle LEDs instellen op een licht blauwe kleur. Deze zal als achtergrond dienen.
    // Merk op dat de eerste LED zich op index 0 bevind, de 2de op index 1, ...

    for(int i = 0; i < NUMPIXELS; i++) {    // Een lus-structuur (itereren over elke LED)

        // Met de methode setPixelColor() kunnen we elke LED afzonderlijk een kleur geven.
        // Hierbij dienen we volgende informatie mee te geven:
        // - de index van de LED, hier i (een teller die loopt van 0 tot 63)
        // - de kleur van de LED, hier licht blauw
        pixels.setPixelColor(i, pixels.Color(0, 0, 1));

    }

    // Door hier een variable "green" te maken kunnen we deze
    // makkelijk meegegeven aan onderstaande code om de letters LTI te
    // vormen met een specifieke intensiteit.
    int green = 25;   // Dit kunnen we nu makkelijk aanpassen


    // Hier gaan we de letters LTI vormen. We dienen dit manueel voor de
    // verschillende LEDs te doen omdat de matrix niet heel groot is.
    // pixels.Color(r, g, b) laat toe om de kleur te zetten aan de hand van
    // de r, g en b componenten. Dit kan gaan van (0, 0, 0) voor zwart tot (255,255,255) voor fel wit.

    // De letter L
    pixels.setPixelColor(16, pixels.Color(0, green, 0));
    pixels.setPixelColor(24, pixels.Color(0, green, 0));
    pixels.setPixelColor(32, pixels.Color(0, green, 0));
    pixels.setPixelColor(40, pixels.Color(0, green, 0));
    pixels.setPixelColor(48, pixels.Color(0, green, 0));
    pixels.setPixelColor(49, pixels.Color(0, green, 0));
    pixels.setPixelColor(50, pixels.Color(0, green, 0));
    
    // De letter T
    pixels.setPixelColor(19, pixels.Color(0, green, 0));
    pixels.setPixelColor(20, pixels.Color(0, green, 0));
    pixels.setPixelColor(21, pixels.Color(0, green, 0));
    pixels.setPixelColor(28, pixels.Color(0, green, 0));
    pixels.setPixelColor(36, pixels.Color(0, green, 0));
    pixels.setPixelColor(44, pixels.Color(0, green, 0));
    pixels.setPixelColor(52, pixels.Color(0, green, 0));
    
    // De letter I
    pixels.setPixelColor(23, pixels.Color(0, green, 0));
    pixels.setPixelColor(39, pixels.Color(0, green, 0));
    pixels.setPixelColor(47, pixels.Color(0, green, 0));
    pixels.setPixelColor(55, pixels.Color(0, green, 0));

 
    // De LEDs gaan pas hun kleur krijgen nadat we de show() methode aanroepen.
    // Dan worden de eigenlijke NeoPixels aangestuurd vanuit de library.
    pixels.show();
}

// Loop wordt telkens opnieuw uitgevoerd. Dus als de functie klaar is
// wordt de functie opnieuw aangeroepen en start het terug van bovenaan.
// De loop() functie moet je hebben. Dat ligt bij Arduino vast.
// Stel dat je echt niet meer te doen hebt, plaats je daar niets in
// oftewel een delay(1000) bv.
void loop() {

    // Hieronder gaan we de knop inlezen die aan pin 4 hangt.
    // Wanneer de knop ingedrukt is gaan we de teller van het aantal bezoekers
    // met 1 verhogen.

    // Eerst lezen we de huidige staat in van de knop (ingedrukt of niet ingedrukt)
    int buttonState = digitalRead(4);

    // Als de staat van de knop HIGH is, dan wordt de knop ingedrukt.
    // Dan kunnen we dus het aantal bezoekers met 1 verhogen.
    if (buttonState == HIGH){
      tellerbezoekers = tellerbezoekers + 1;    // Bezoekersteller verhogen

      // Als je wil dat je de knop ingedrukt kan blijven houden en dat je pas
      // bij het loslaten verder gaat in de code kan je onderstaande code uit commentaar
      // halen (de twee slashes ervoor weg doen)

      // while (digitalRead(4) == HIGH) {}
      
      // De bovenstaande code zal een lus creëren die niets doet zolang de gebruiker
      // op de knop drukt. Laat hij/zij los, dan stopt de lus en gaat de code verder.
      // Merk op dat we hier digitalRead() aanroepen omdat we telkens een update willen
      // van de huidige stand van de knop. Moesten we hier "buttonState" gebruiken zo dit
      // gewoon HIGH zijn en blijven.
    }

    // Verschuif de display cursor naar het 15de karakter op de display in de 2de rij.
    // Met andere worden een beetje rechts onderaan
    lcd.setCursor(14, 1);

    // Nu kunnen we de bezoekersteller daar tonen
    lcd.print (tellerbezoekers);
  
    // Hier gaan we meestal een delay() plaatsen omdat anders te code super-snel
    // wordt uitgevoerd. Wanneer je met een display ofzo werkt gaat dit er dan voor zorgen
    // dat de characters wazig worden.
    delay(1000);
}

