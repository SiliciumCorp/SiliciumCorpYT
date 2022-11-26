//
// SiliciumCorp Youtube
// Ce programme à pour but de presenter une première approche compréhensive du protocole de communication avec le DHT11
//
// Vidéo Youtube : https://www.youtube.com/watch?v=x0fqwdBF8Es
//
#define PIN_DHT 7

//Variable qui contiendra les 5 octets recu du DHT
byte data_DHT[5];

//Variable qui contiendra les messages a afficher de l'humidité et de la température
char message[42];

//Déclaration des signatures des fonctions que nous utilisons
void wakeUpDHT();
void readDataFromDHT();
byte readSingleByte();
bool checkDataIntegrity();

void setup() {
    //Amorce de la communication série
    Serial.begin(9600);

    //Paramétrage initale du port en mode INPUT
    pinMode(PIN_DHT, OUTPUT);

    //On met le port à haut pour une durée initiale de sécurité
    digitalWrite(PIN_DHT, HIGH);
    delay(1000);
}

void loop() {
    //On reveil le DHT
    wakeUpDHT();

    //Reveillé, on lit les 5 octets qu'il va nous envoyer
    readDataFromDHT();

    //On affiche les valeurs recu sur le moniteur série
    if(checkDataIntegrity()){
        sprintf(message, "Humidité : %u.%u%% - Température : %u.%u°C", data_DHT[0], data_DHT[1], data_DHT[2], data_DHT[3]);
        Serial.println(message);

    }
    else{
        Serial.println("read error");
    }

    //On attend 1 seconde avant de relire
    delay(1000);
}

void wakeUpDHT(){
    //On coupe le courant sur la port de données
    digitalWrite(PIN_DHT, LOW);

    //On attend une periode de plus de 18 ms
    delay(20);

    //On repasse à l'état haut (STEP 01)
    digitalWrite(PIN_DHT, HIGH);

    //On attend 30µs
    delayMicroseconds(30);

    //On change le mode du port (STEP 02)
    pinMode(PIN_DHT, INPUT);

    //Boucle qui attend que se soit le DHT qui change la tension à LOW (BOUCLE 01)
    while(digitalRead(PIN_DHT) == HIGH);

    //Boucle qui attend que se soit le DHT qui change la tension à HIGH (BOUCLE 02) (environ 80µs)
    while(digitalRead(PIN_DHT) == LOW);

    //Boucle qui attend que se soit le DHT qui change la tension à LOW (BOUCLE 03) (environ 80µs)
    while(digitalRead(PIN_DHT) == HIGH);
}

void readDataFromDHT(){
    //On amorce la lecture de 5 octets que l'on va recevoir du DHT
    for(byte i = 0; i < 5; i++){
        data_DHT[i] = readSingleByte();
    }
    //Une fois la lecture des 5 octets terminé on se remet dans l'etat pour la prochaine lecture
    pinMode(PIN_DHT, OUTPUT);

    //En remetant le port à l'etat haut, on force DHT à se remetre à dormir.
    digitalWrite(PIN_DHT, HIGH);
}

byte readSingleByte(){
    //Variable qui va stocker l'octet en cours de lecture
    byte byte_read = 0;

    //Pour former un octet entier on va avoir besoin de lire 8bits consécutifs
    for (byte i = 0; i < 8; i++) {
        //Boucle qui attend que le DHT change la tension à HIGH (BOUCLE 01)
        while(digitalRead(PIN_DHT) == LOW);

        //Attente de 40µs
        delayMicroseconds(40);

        //Si apres 40µs le signal est toujours à HIGH on peux en conclure que le bit que l'on vient
        //de recevoir est un 1, dans le cas contraire, c'etait un 0 et on a juste à ignorer ce tour
        //de boucle
        if(digitalRead(PIN_DHT) == HIGH){
            //on utilise 2 opérateurs binaire pour enregistrer le résultat dans l'octet en cours
            byte_read |= (1 << (7 - i));
            //si le signal est a HIGH, nous devons attendre la fin pour passer au prochain tour de boucle
            while(digitalRead(PIN_DHT) == HIGH);
        }
    }
    //L'octet entierement lu, nous renvoyons le résultat
    return byte_read;
}

bool checkDataIntegrity(){
    //Si la donnée n'est pas corrompu, data_DHT[4] est censé etre la somme du reste du tableau
    if(data_DHT[4] - data_DHT[3] - data_DHT[2] - data_DHT[1] - data_DHT[0] == 0){
        return true;
    }
    return false;
}