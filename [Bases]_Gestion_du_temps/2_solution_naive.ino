/*

   ___|  _)  | _)       _)                         ___|                     
 \___ \   |  |  |   __|  |  |   |  __ `__ \       |       _ \    __|  __ \  
       |  |  |  |  (     |  |   |  |   |   |      |      (   |  |     |   | 
 _____/  _| _| _| \___| _| \__,_| _|  _|  _|     \____| \___/  _|     .__/  
                                                                     _|   
*/

#define PIN_LED_1 8
#define PIN_LED_2 7

// Definie l'interval de déclenchement des taches
unsigned long interval_tache_1 = 2000; // 2 secondes
unsigned long interval_tache_2 = 3000; // 3 secondes

// Définie la duree d'une tache
unsigned long duree_tache_1 = 1000; // 1 seconde
unsigned long duree_tache_2 = 500; // 0.5 seconde

// Stock la date de fin en cours d'une tache
unsigned long fin_tache_1 = duree_tache_1;
unsigned long fin_tache_2 = duree_tache_2;

// Stock la date du prochain début d'une tache
unsigned long debut_tache_1 = 0;
unsigned long debut_tache_2 = 0;

unsigned long temps_ecoule = 0;

// Etat de la tache : en cours d'activation 
bool tache_1_activation = false;
bool tache_2_activation = false;

// Etat de la tache : active 
bool tache_1_en_cours = false;
bool tache_2_en_cours = false;

// Etat de la tache : faire un relevé des timings
bool relever_timing_1 = false;
bool relever_timing_2 = false;

char message[60];

void setup() {
    //Communication série
    Serial.begin(9600);

    //LEDs en mode OUTPUT
    pinMode(PIN_LED_1, OUTPUT);
    pinMode(PIN_LED_2, OUTPUT);
  
}


void loop() {

    //Collecte le temps ecoulé en début de boucle
    temps_ecoule = millis();

    //Observe si la date de début à été atteinte
    if(debut_tache_1 <= temps_ecoule){

        //Calcule la prochaine date de debut
        debut_tache_1 += interval_tache_1;

        //Active la log
        relever_timing_1 = true;

        //Met la tache "en cours d'activation"
        tache_1_activation = true;
    }

    if(debut_tache_2 <= temps_ecoule){
        debut_tache_2 += interval_tache_2;
        relever_timing_2 = true;
        tache_2_activation = true;
    }

    // Observe si la tache est "en cours d'activation"
    if(tache_1_activation){
        // Desactive le mode "en cours d'activation"
        tache_1_activation = false;

        //Calcule la date de fin de la tache
        fin_tache_1 = temps_ecoule + duree_tache_1;

        //Met la tache "en cours"
        tache_1_en_cours = true;

        //Allume la LED
        digitalWrite(PIN_LED_1, HIGH);
    }

    if(tache_2_activation){
        tache_2_activation = false;
        fin_tache_2 = temps_ecoule + duree_tache_2;
        tache_2_en_cours = true;

        digitalWrite(PIN_LED_2, HIGH);
    }

    // Observe si la tache est "en cours"
    if(tache_1_en_cours){

        // Observe si la tache est périmée
        if(fin_tache_1 <= temps_ecoule){
            //Eteint la LED
            digitalWrite(PIN_LED_1, LOW);

            //Désactive la tache
            tache_1_en_cours = false;
        }
    }

    if(tache_2_en_cours){
        if(fin_tache_2 <= temps_ecoule){
            digitalWrite(PIN_LED_2, LOW);
            tache_2_en_cours = false;
        }
    }

    // Observe si la log est active
    if(relever_timing_1){
        // Désactive la log
        relever_timing_1 = false;

        // Construit une chaine de caractere dynamic
        sprintf(message, "debut_tache_1 : %lu", debut_tache_1);

        // Envoie la log sur le canal série
        Serial.println(message);
    }

    if(relever_timing_2){
        relever_timing_2 = false;
        sprintf(message, "debut_tache_2 : %lu", debut_tache_2);
        Serial.println(message);
    }

}
