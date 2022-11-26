//
// SiliciumCorp Youtube
// Ce programme à pour but de simuler un verrou de coffre, qui utiliserait un rotary encoder comme moyen de saisi
// Vidéo Youtube : https://www.youtube.com/watch?v=J_Tn0zh51ec
//

/*
 * Dans ce code source, nous simulons l'ouverture d'un verou à l'aide d'un mot de passe saisi à l'aide d'un codeur rotatif.
 * Les mentions de porte ouverte/fermée ou de verou, font réference a une simulation où nous utilisons une LED rouge et verte afin
 * de remplacer une porte/verou fermé ou ouvert.
 */

//Déclaration des signatures des fonctions que l'on va utiliser
void handleRotaryEvent(int limitCounterHigh=20, int limitCounterLow=0);
bool checkPushButton();
void checkDoorLocked();

//Déclaration des pins du codeur rotatif
#define pinDT 2
#define pinCLK 3
//Déclaration du pin du boutton poussoir
#define pinPush 4

//Déclaration des 2 LED
#define redLED 9
#define greenLED 10

//Compteur génerale qui évolue en fonction de la position du codeur rotatif
int currentCounter = 0;
//Variable pour la lecture des états du codeur rotatif
byte readStateCLK;
byte readStateDT;
byte oldStateCLK;
int integrity = 0;
int integrityCheck = 1;

//Variable pour la gestion du mot de passe a saisir à l'aide du codeur rotatif
bool attemptInProgress = false;
bool doorLocked = true;

byte currentDigit = 0;
byte numbersLock[] = {4, 13, 10, 5};
byte numbersAttempted[] = {0, 0, 0, 0};

char message[50];
bool eventPushButton = false;

void setup() {
    //Initialisation de la communication Serie
    Serial.begin (9600);

    //On declare les Pins du codeur rotatif en ENTREE (INPUT)
    pinMode (pinDT, INPUT);
    pinMode (pinCLK, INPUT);

    digitalWrite(pinCLK, HIGH);
    digitalWrite(pinDT, HIGH);

    //On declare le Pin du bouton poussoir en ENTREE (INPUT)
    pinMode (pinPush, INPUT);

    //On déclare les 2 LED en SORTIE (OUTPUT)
    pinMode (redLED, OUTPUT);
    pinMode (greenLED, OUTPUT);

    //On récupere la situation initiale du codeur rotatif
    oldStateCLK = digitalRead(pinCLK);

    //On appel la fonction permettant la mise a jour des LED
    checkDoorLocked();
}

void loop() {
    //Si l'utilisateur n'a pas encore activer le process de saisi du mot de passe et que le verou est toujours fermé
    if(!attemptInProgress && doorLocked){
        if(checkPushButton()){
            attemptInProgress = true;
            Serial.println("Listening to user entry...");
        }
    }

    //Si l'utilisateur a commencer la phase de saisi du mot de passe et que le verou est toujours fermé
    if(attemptInProgress && doorLocked){

        //Appel de la fonction qui permet la gestion des evenements sur le codeur rotatif
        handleRotaryEvent();

        //Si le boutton poussoir à été appuyé
        if(checkPushButton()){
            //On indique a l'utilisateur le nombre qui à été saisi et enregistré
            sprintf(message, "Digit %i recorded with %i", currentDigit+1, currentCounter);
            Serial.println(message);

            //On stocke la valeur actuelle du compteur pour ue comparaison future
            numbersAttempted[currentDigit] = currentCounter;

            //On incremente l'index de stockage
            currentDigit++;

            //Si l'index de stockage est arrivé à 4 cela indique que la procedure de saisi est terminé
            if(currentDigit > 3){

                //Boucle qui va permettre la comparaison des 4 nombres saisis par l'utilisateur avec les 4 nombres du mot de passe.
                doorLocked = false;
                for(byte i = 0; i < 4; i++){
                    if(numbersLock[i] != numbersAttempted[i]){
                        doorLocked = true;
                    }
                }
                //Si une erreur a été constaté dans la routine précédente, alors on indique l'echec aupres de l'utilisateur
                if(doorLocked){
                    Serial.println("Failed to open the lock");
                }
                    //Dans le cas contraire on indique le succes de l'opération
                else{
                    Serial.println("Succes");
                }
                //Mise à jour de la LED de couleur
                checkDoorLocked();
                //Remise a zero des variables servant a l'enregistrement du mot de passe.
                attemptInProgress = false;
                currentDigit = 0;
                currentCounter = 0;
            }
        }
    }
    //Si l'utilisateur a ouvert le verou et qu'il rappui sur le bouton poussoir cela va refermer le verou
    if(!doorLocked){
        if(checkPushButton()){
            Serial.println("Closing door");
            doorLocked = true;
            checkDoorLocked();
        }
    }
}

//Fonction permettant de capter la pression sur un bouton poussoir
//Mais uniquement lors du relachement du bouton.
//Cela permet un appuie long sur le bouton poussoir sans craindre la répétition d'une detection multiple
bool checkPushButton(){
    if(eventPushButton){
        if(!digitalRead(pinPush)){
            return false;
        }
        else{
            eventPushButton = false;
            return true;
        }
    }
    else if(!digitalRead(pinPush)){
        eventPushButton = true;
        return false;
    }
    return false;
}


//Fonction qui sert a controller et comprendre les actions qui surviennent sur le codeur rotatif.
void handleRotaryEvent(int limitCounterHigh=20, int limitCounterLow=0){
    //Lecture de l'état de CLK
    readStateCLK = digitalRead(pinCLK);

    //Si CLK est different de son état précédent
    if(readStateCLK != oldStateCLK){

        //On ajoute a integrity la valeur de integrityCheck (qui est soit égal à 1 ou -1)
        integrity += integrityCheck;
        //On inverse integrityCheck. 1 devient -1 et vice versa
        integrityCheck *= (-1);

        //Si integrity est égal à 1
        if(integrity){
            //On lis cette fois le pin DT
            readStateDT = digitalRead(pinDT);
            //Si DT est à 1
            if(readStateDT){
                //On est dans le cas de tourner dans le sens des aiguilles d'une montre
                //On incremente le compteur générale
                currentCounter ++;
                //Parti qui permet de limiter le compteur sur une limite haute indepassable
                if(currentCounter > limitCounterHigh){
                    currentCounter = limitCounterHigh;
                }
            }
            else{
                //On est dans le cas de tourner dans le sens contraire des aiguilles d'une montre
                //On décrémente le compteur générale
                currentCounter --;

                //Parti qui permet de limiter le compteur sur une limite basse indepassable
                if(currentCounter < limitCounterLow){
                    currentCounter = limitCounterLow;
                }
            }
            //On affiche le compteur
            Serial.println(currentCounter);
        }
    }
    //On remplace l'ancien etat de oldStateCLK par le dernier état de CLK
    oldStateCLK = readStateCLK;

}

//Fonction qui permet en fonction de l'etat de la variable doorLocked de mettre a jour l'etat des LED rouge et verte.
void checkDoorLocked(){
    if(doorLocked){
        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, LOW);
    }
    else{
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, HIGH);
    }
}