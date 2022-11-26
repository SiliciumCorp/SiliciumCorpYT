//
// SiliciumCorp Youtube
// Ce programme à pour but d'afficher un compteur qui s'incremente chaque seconde.
// Executer ce programme apres avoir retiré la piste sur la carte Arduino met en évidence l'absence de réinitialisation.
// Video YOUTUBE : https://www.youtube.com/watch?v=OPJG6oxAMO8
//

//Declaration d'un compteur et initialisation à 0
int compteur = 0;

//Fonction de setup initiale de l'Arduino
void setup() {
    //On amorce la communication série
    Serial.begin(9600);

    //On envoie "Initialisation" sur la console
    Serial.println("Initialisation");
}

//Boucle principale de l'Arduino
void loop() {
    //On affiche la situation actuelle du compteur
    Serial.println(compteur);

    //On incrémente le compteur de 1
    compteur += 1;

    //On pause pendant 1 seconde
    delay(1000);
}