#include <Wire.h>           // Library voor i2c communicatie van arduino
#include "rgb_lcd.h"        // Library inladen voor het RGB LCD display

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

// De setup() functie wordt bij het starten 1-malig aangeroepen.
// Hier stellen we hardware in en kunnen we taken uitvoeren die
// enkel 1 maal moeten gebeuren tijdens het starten van de code
void setup() {

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

    //  Met setCursor(kolom, rij) kunnen we kiezen om tekst op
    // een andere plaats te zetten op het display.
    // We tellen hierbij vanaf 0. Dus 2de rij = 1.
    // Merk dat enkel de karakters van het display worden overschreven
    // via print(). Dus met andere woorden, de "Welkom" op de lijn erboven
    // blijft netjes staan
    lcd.setCursor(0, 1);

    // De cursor staat nu links onderaan (2de rij). Daar kunnen we dan de tekst
    // laten verschijnen met print().
    lcd.print("op het LTI");

    // Deze delay() is eigenlijk overbodig. Die mag weg.
    delay(1000);
}

// Loop wordt telkens opnieuw uitgevoerd. Dus als de functie klaar is
// wordt de functie opnieuw aangeroepen en start het terug van bovenaan.
// De loop() functie moet je hebben. Dat ligt bij Arduino vast.
// Stel dat je echt niet meer te doen hebt, plaats je daar niets in
// oftewel een delay(1000) bv.
void loop() {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    //lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    //lcd.print(millis() / 1000);


    // Hier gaan we meestal een delay() plaatsen omdat anders te code super-snel
    // wordt uitgevoerd. Wanneer je met een display ofzo werkt gaat dit er dan voor zorgen
    // dat de characters wazig worden.
    delay(100);
}       // Dit noemen we de curly-braces (accolades)
