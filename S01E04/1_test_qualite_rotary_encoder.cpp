//
// SiliciumCorp Youtube Channel
// Ce programme à pour but de tester la qualité de votre Rotary Encoder
// Vidéo Youtube : https://www.youtube.com/watch?v=J_Tn0zh51ec
//

//Déclaration des pins du codeur rotatif
#define pinDT 2
#define pinCLK 3

//Déclaration des pins des 2 LED
#define redLED 9
#define greenLED 10

byte readStateCLK = 0;
byte readStateDT = 0;
byte oldStateCLK = 0;
byte oldStateDT = 0;

int amountCLKHigh = 0;
int amountDTHigh = 0;

char message[50];

void setup() {
    //Initialisation de la communication Serie
    Serial.begin (9600);

    //On déclare les Pins du codeur rotatif en ENTREE (INPUT)
    pinMode (pinDT, INPUT);
    pinMode (pinCLK, INPUT);

    //On déclare les 2 LED en SORTIE (OUTPUT)
    pinMode (redLED, OUTPUT);
    pinMode (greenLED, OUTPUT);
}

void loop() {
    //Lecture de l'état de CLK
    readStateCLK = digitalRead(pinCLK);
    readStateDT = digitalRead(pinDT);

    //On allume la LED verte quand CLK est à HIGH
    digitalWrite(greenLED, readStateCLK);
    //On allume la LED rouge quand DT est à HIGH
    digitalWrite(redLED, readStateDT);

    //Si CLK ou DT sont constatés differents de leurs états précédents
    if(readStateCLK != oldStateCLK || readStateDT != oldStateDT){
        //On met a jour les compteurs d'etat de CLK et DT
        amountCLKHigh += readStateCLK;
        amountDTHigh += readStateDT;

        //On compose un message que l'on envoie sur le port serie contenant les différents états de CLK et DT ainsi que leurs compteurs respectifs
        sprintf(message, "CLK: %i - DT: %i [TOTAL] CLK: %i - DT: %i", readStateCLK, readStateDT, amountCLKHigh, amountDTHigh);
        Serial.println(message);

    }
    //On remplace les anciens états de oldStateCLK et oldStateDT par leurs derniers états respectifs
    oldStateCLK = readStateCLK;
    oldStateDT = readStateDT;
}
