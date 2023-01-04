#define PIN_LED_1 8
#define PIN_LED_2 7

// Structure en vue de stocker tout les parametres propre a une Tache
struct Tache{
    int pin = 0;
    unsigned long interval = 0;
    unsigned long duree = 0;
    unsigned long debut = 0;
    unsigned long fin = 0;
    bool relever_timing = false;
    bool en_activation = false;
    bool en_cours = false;
};

// Déclaration des 2 taches
Tache tache_1;
Tache tache_2;

unsigned long temps_ecoule;

void setup() {

    //Communication série
    Serial.begin(9600);

    //LED setting mode OUTPUT
    pinMode(PIN_LED_1, OUTPUT);
    pinMode(PIN_LED_2, OUTPUT);

    //Parametrage des taches
    tache_1.pin = PIN_LED_1;
    tache_2.pin = PIN_LED_2;

    tache_1.interval = 3000;
    tache_2.interval = 2000;

    tache_1.duree = 1000;
    tache_2.duree = 500;
  
}

// Fonction qui attend une tache et le temps ecoulé pour prendre des décisions.
// Notez ici que tache est passée par référence afin de l'editer et la mettre à jour en memoire

void verif_tache(Tache &tache, unsigned long temps_ecoule){

    //Observe si la date de début à été atteinte
    if(tache.debut <= temps_ecoule){
        //Calcule la prochaine date de debut
        tache.debut += tache.interval;

        //Active la log
        tache.relever_timing = true;

        //Met la tache "en cours d'activation"
        tache.en_activation = true;
    }

    // Observe si la tache est "en cours d'activation"
    if(tache.en_activation){
        // Desactive le mode "en cours d'activation"
        tache.en_activation = false;

        //Calcule la date de fin de la tache
        tache.fin = temps_ecoule + tache.duree;

        //Met la tache "en cours"
        tache.en_cours = true;

        //Allume la LED
        digitalWrite(tache.pin, HIGH);
    }

    // Observe si la tache est "en cours"
    if(tache.en_cours){
        // Observe si la tache est périmée
        if(tache.fin <= temps_ecoule){
            //Eteint la LED
            digitalWrite(tache.pin, LOW);

            //Désactive la tache
            tache.en_cours = false;
        }
    }

    // Observe si la log est active
    if(tache.relever_timing){
        // Désactive la log
        tache.relever_timing = false;

        // Envoie la log sur le canal série
        Serial.print("Next time ");
        Serial.println(tache.debut);
    }
}

void loop() {
    //Collecte le temps ecoulé en début de boucle
    temps_ecoule = millis();

    //Soumet tache1 et tache2 à la vérification et mis à jour de leurs etat.
    verif_tache(tache_1, temps_ecoule);
    verif_tache(tache_2, temps_ecoule);
}
