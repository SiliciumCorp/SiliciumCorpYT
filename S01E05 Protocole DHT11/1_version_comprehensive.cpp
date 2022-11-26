//
// SiliciumCorp Youtube Channel
// Ce programme à pour but de presenter une première approche compréhensive du protocole de communication avec le DHT11
//
// Vidéo Youtube : https://www.youtube.com/watch?v=x0fqwdBF8Es
//

#define PIN_DHT 7
unsigned long init_chronos = 0;
unsigned long chronos_step_1 = 0;
unsigned long chronos_step_2 = 0;

int elapsed_step_1 = 0;
int elapsed_step_2 = 0;

void wakeUpDHT();

void setup() {
    //Amorce de la communication série
    Serial.begin(9600);

    //Paramétrage initale du port en mode INPUT
    pinMode(PIN_DHT, OUTPUT);

    //On met le port à haut pour une durée de sécurité
    digitalWrite(PIN_DHT, HIGH);
    delay(1000);

    //On appelle notre fonction de test
    wakeUpDHT();
}

void loop() {

}

void wakeUpDHT(){
    //On coupe le courant sur le port de données (STEP 00)
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

    //On lance le chronometre #CHRONOS_00 (Attention, sur une UNO, micros() est précis a 4 microseconde)
    init_chronos = micros();

    //Boucle qui attend que se soit le DHT qui change la tension à HIGH (BOUCLE 02)
    //Devrai durer environ 80µs
    while(digitalRead(PIN_DHT) == LOW);

    //On collecte le premier relevé du chonometre #CHRONOS_01
    chronos_step_1 = micros();

    //Boucle qui attend que se soit le DHT qui change la tension à LOW (BOUCLE 03)
    //Devrai durer environ 80µs
    while(digitalRead(PIN_DHT) == HIGH);

    //On collecte le deuxieme relevé du chonometre #CHRONOS_02
    chronos_step_2 = micros();

    //A ce stade le DHT va commencer à envoyer de la data.
    //Pour cette premiere demonstration on ignore la data mais on affiche les valeurs de chronometre
    elapsed_step_1 = chronos_step_1 - init_chronos;
    elapsed_step_2 = chronos_step_2 - chronos_step_1;

    Serial.println(elapsed_step_1);
    Serial.println(elapsed_step_2);
}