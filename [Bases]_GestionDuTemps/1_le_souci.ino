/*

   ___|  _)  | _)       _)                         ___|                     
 \___ \   |  |  |   __|  |  |   |  __ `__ \       |       _ \    __|  __ \  
       |  |  |  |  (     |  |   |  |   |   |      |      (   |  |     |   | 
 _____/  _| _| _| \___| _| \__,_| _|  _|  _|     \____| \___/  _|     .__/  
                                                                     _|   
*/

unsigned long temp_ecoule = 0;
char message[60];

void setup() {
    //Communication série
    Serial.begin(9600);

    //LED intégrée mode OUTPUT
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    //Allumage de la LED
    digitalWrite(LED_BUILTIN, HIGH);

    //Pause d'1 seconde
    delay(1000);

    //Collecte le temps ecoulé depuis le lancement du programme
    temp_ecoule = micros();

    //Envoie les nombres de 0 à 99 sur le port série pour simuler une grosse charge de travail
    for(int i = 0; i < 100; i++){
        Serial.print(i);
    }

    //Calcul et envoie le temps ecoulé pour la charge sur le port serie
    sprintf(message, "Temps ecoule : %lu", micros() - temp_ecoule);
    Serial.println(message);

    //Extinction de la LED
    digitalWrite(LED_BUILTIN, LOW);

    //Pause d'1 seconde
    delay(1000);
}