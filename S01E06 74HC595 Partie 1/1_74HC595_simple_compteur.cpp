//
// SiliciumCorp Youtube
// Ce programme à pour but de presenter le composant PIC 74HC595 8 Bit-shift register
// Dans cette example on affiche les valeurs en binaire de 0 à 255 à l'aide de 8 LEDs connectées au circuit
//
// Vidéo Youtube : https://www.youtube.com/watch?v=26LAW78u0WQ
//

#define PIN_DS_DATA 4
#define PIN_STCP_LATCH 5
#define PIN_SHCP_CLOCK 6

void setup() {
    //On définie les 3 ports en mode OUTPUT
    pinMode(PIN_STCP_LATCH, OUTPUT);
    pinMode(PIN_SHCP_CLOCK, OUTPUT);
    pinMode(PIN_DS_DATA, OUTPUT);
}

void loop() {
    //On execute une boucle de 255 tours pour visiter
    //les 255 nombres qui peuvent être représentés dans un octet.
    for (byte number = 0; number < 256; number++) {
        //On s'assure que la gachette est a l'etat LOW
        digitalWrite(PIN_STCP_LATCH, LOW);

        //On utlise la fonction shiftOut de la librairie
        //arduino pour lui soumettre la valeur à transmettre au registre
        shiftOut(PIN_DS_DATA, PIN_SHCP_CLOCK, LSBFIRST, number);

        //On inverse l'etat de la gachette pour mettre à jour le registre
        digitalWrite(PIN_STCP_LATCH, HIGH);

        //Un delais d'une demi seconde avant le prochain tour de boucle
        delay(500);
    }
}