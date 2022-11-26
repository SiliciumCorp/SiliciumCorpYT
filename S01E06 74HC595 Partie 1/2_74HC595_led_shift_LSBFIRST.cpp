//
// SiliciumCorp Youtube Channel
// Ce programme à pour but de presenter le composant PIC 74HC595 8 Bit-shift register
// Dans cette example on allume une seule des 8 LEDs en opérant un shift binaire et
// cela apparait comme une rotation continue de LED. Version LSBFIRST
//
// Vidéo Youtube : https://www.youtube.com/watch?v=26LAW78u0WQ
//
#define PIN_DS_DATA 4
#define PIN_STCP_LATCH 5
#define PIN_SHCP_CLOCK 6

byte led = 0;

void setup() {
    //On définie les 3 ports en mode OUTPUT
    pinMode(PIN_STCP_LATCH, OUTPUT);
    pinMode(PIN_SHCP_CLOCK, OUTPUT);
    pinMode(PIN_DS_DATA, OUTPUT);
}

void loop() {
    //On execute une boucle de 8 tours pour visiter les 8 LEDs
    for (byte i = 0; i < 8; i++) {
        //On affecte la variable led de la valeur 1 decallée au prorata de i
        led = 1 << i;

        //On s'assure que la gachette est a l'etat LOW
        digitalWrite(PIN_STCP_LATCH, LOW);

        //On utlise la fonction shiftOut de la librairie
        //arduino pour lui soumettre la valeur a transmettre au registre
        shiftOut(PIN_DS_DATA, PIN_SHCP_CLOCK, LSBFIRST, led);

        //On inverse l'etat de la gachette pour mettre a jour le registre
        digitalWrite(PIN_STCP_LATCH, HIGH);

        //Un delais d'une demi seconde avant le prochain tour de boucle
        delay(500);
    }
}