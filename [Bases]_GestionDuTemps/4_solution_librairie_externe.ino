#include <arduino-timer.h>
#define PIN_LED_1 8
#define PIN_LED_2 7

// Structure en vue de stocker tout les parametres propre a une Tache
struct Tache{
    int pin;
    int duree;
};

// Déclaration des 2 taches
Tache tache_1;
Tache tache_2;

// Déclaration du gestionnaire des taches : timer
// 3 constructeurs existent, celui ci est l'un d'eux.
// int : nombre de taches
// micros | millis : précision du timer
// type argument attendu lors de l'appel d'un callback.
Timer<4, millis, Tache> timer;

// Callback appellé afin d'eteindre la LED définie sur tache.pin
bool extinction_led(Tache tache){
    //Extinction de la LED
    digitalWrite(tache.pin, LOW);
    
    //Auto destruction de la tache en memoire.
    return false;
}

// Callback appellé afin d'allumer la LED définie sur tache.pin
bool allumage_led(Tache tache) {
    //Allumage de la LED
    digitalWrite(tache.pin, HIGH);

    //Instanciation d'une tache a executer dans tache.duree
    timer.in(tache.duree, extinction_led, tache);

    //Réinstanciation automatique de la tache
    return true;
}

void setup() {
    //LED setting mode OUTPUT
    pinMode(PIN_LED_1, OUTPUT);
    pinMode(PIN_LED_2, OUTPUT);

    //Initialisation des deux taches avec leur pin de raccordement et la durée de la tache
    tache_1 = {PIN_LED_1, 1000};
    tache_2 = {PIN_LED_2, 500};

    //Déclaration aupres du gestionnaire de taches de deux taches a executer a interval régulier
    timer.every(3000, allumage_led, tache_1);
    timer.every(2000, allumage_led, tache_2);

}

void loop() {
    //Appel constant de "l'horloge interne" du gestionnaire des taches pour la mise à jour et lancement des taches.
    timer.tick();
}