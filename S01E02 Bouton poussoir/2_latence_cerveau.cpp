//
// SiliciumCorp Youtube
// Ce programme à pour but de vous chronometrer et detecter votre temps de réation
// Vidéo Youtube : https://www.youtube.com/watch?v=49QmuGBwh7M
//

int delaiSurprise = 0; //Variable pour les délais surprises
unsigned long tempsDebut; //Variable qui stock l'heure de début du challenge
int pinBoutton = 2; //Port sur lequel est branché le bouton poussoir

void setup() {
    //On amorce la communication série
    Serial.begin(9600);
    randomSeed(analogRead(0));
    //Initialisation de la LED sur l'Arduino
    pinMode(LED_BUILTIN, OUTPUT);

    //Initialisation du port sur l'Arduino connecté au bouton poussoir
    pinMode(pinBoutton, INPUT);

    //On choisit une période aléatoire d'attente surprise entre 6 et 20 sec
    delaiSurprise = random(6000, 20000);

    //Le programme attend une période qui correspond au délai surprise
    delay(delaiSurprise);

    //On allume la LED embarquée sur l'Arduino
    digitalWrite(LED_BUILTIN, HIGH);

    //On enregistre l'heure pour commencer le chronomètre
    tempsDebut = millis();
}

void loop() {
    //On lit le status sur le port du bouton poussoir
    if(digitalRead(pinBoutton) == LOW){

        //Calcul le temps final déduis de l'heure actuelle et de l'heure du début
        int tempsFinal = millis() - tempsDebut;

        //On envoie le résultat sur le moniteur série
        Serial.print("Temps écoulé : ");
        Serial.print(tempsFinal);
        Serial.println(" ms. Reset carte requis pour recommencer");

        //On attend 10 sec par sécurité pour éviter les appuies bouton intempestifs.
        delay(10000);
    }
}