//
// SiliciumCorp Youtube
// Ce programme à pour but de controller que le bouton poussoir raccordé à l'Arduino est correctement branché
// Vidéo Youtube : https://www.youtube.com/watch?v=49QmuGBwh7M
//


const int pinBouton = 2;     // Port sur lequel est branché le bouton poussoir
int etatBouton = 0;         // variable pour stoker la lecture du status du bouton poussoir

void setup() {
    // On initialise la LED intégrée sur le port 13 de l'Arduino
    pinMode(LED_BUILTIN, OUTPUT);

    // On initialise le bouton poussoir en mode INPUT
    pinMode(pinBouton, INPUT);
}

void loop() {
    // On lit l'état actuel du bouton poussoir. Attention selon le montage, le bouton poussoir peut être inversé
    etatBouton = digitalRead(pinBouton);

    // Si on lit la valeur HIGH (=1) alors on allume la LED intégrée
    if (etatBouton == HIGH) {
        // Allumage de la LED :
        digitalWrite(LED_BUILTIN, HIGH);
    }
        //Sinon, si la valeur est autre que HIGH alors on éteint la LED intégrée
    else {
        // Eteignage de la LED :
        digitalWrite(LED_BUILTIN, LOW);
    }
}