//
// SiliciumCorp Youtube
// Ce programme à pour but de presenter le composant PIC 74HC595 8 Bit-shift register
// Dans cette example on exploite un peu plus le shift grace a deux fonctions pour nous simplifier la tache.
//
// Vidéo Youtube : https://youtu.be/jFUmCvr2LKs
//

#include <math.h>
#define PIN_DS_DATA 4
#define PIN_STCP_LATCH 5
#define PIN_SHCP_CLOCK 6

#define NUMBER_OF_DISPLAY 2

//Valeur décimales qui représentées en binaire permettent 
//d'allumer les led correspondantes aux chiffres de 0 à 9
byte numbers[10] = {238, 40, 205, 109, 43, 103, 231, 44, 239, 111};



//Fonction qui convertie un entier en un tableau de nombre correspondant au different nombre de la variable numbers
byte* convert_number_to_array(int to_convert){
  //Initialise un tableau qui va stocker les differents nombres
  static byte to_display[NUMBER_OF_DISPLAY];

  //Commence la decoupe du nombre
  int rest = to_convert;

  //Boucle sur chaque digit du nombre a decouper
  for(byte i = 0; i < NUMBER_OF_DISPLAY; i++){
    //Recupere le digit en cours, et stocke le reste pour le prochain tour de boucle
    int digit = rest / pow(10, ((NUMBER_OF_DISPLAY - 1) - i));
    rest = fmod(rest , pow(10, ((NUMBER_OF_DISPLAY - 1) - i)));
    to_display[i] = numbers[digit];
  }
  return to_display;
}


void update_shift(byte* to_display){
  //On s'assure que la gachette est a l'etat LOW
  digitalWrite(PIN_STCP_LATCH, LOW);
  //Serial.println(to_display[0]);
  //Serial.println(to_display[1]);
  //On boucle sur tableau donné QUI DOIT ETRE DE TAILLE = NUMBER_OF_DISPLAY 
  //Si vous donné un tableau trop petit, erreur de type : index out of range
  //Si vous donné un tableau trop grand, la lecture sera tronqué à la taille de NUMBER_OF_DISPLAY
  //Dans la mesure du possible, toujours evité l'allocation dynamique de memoire sur une bestiole comme Arduino
  for (byte display_index = 0; display_index < NUMBER_OF_DISPLAY; display_index++) {
    shiftOut(PIN_DS_DATA, PIN_SHCP_CLOCK, MSBFIRST, to_display[display_index]);
  }

  //On inverse l'etat de la gachette pour mettre à jour le registre
  digitalWrite(PIN_STCP_LATCH, HIGH);
}

void setup() {
   //On définie les 3 ports en mode OUTPUT
  pinMode(PIN_STCP_LATCH, OUTPUT);
  pinMode(PIN_SHCP_CLOCK, OUTPUT);
  pinMode(PIN_DS_DATA, OUTPUT);
}

void loop() {
  // On genere 1 tableau qui est le resultat de la fonction convert_number_to_array
  byte* nombre_1 = convert_number_to_array(42);

  // On envoie le tableau fraichement generé à la fonction update_shift pour qu'elle mette à jour tout les shifts déclarés
  update_shift(nombre_1);

  // On attend une tite seconde
  delay(1000);

  // On reproduit l'opération ci dessus plus rapidement de 0 à 100
  byte* nombre_dynamique;
  for (byte j = 0; j < 100; j++){
    nombre_dynamique = convert_number_to_array(j);
    update_shift(nombre_dynamique);
    delay(100);
  }
  
  byte clear[2] = {0, 0};
  update_shift(clear);
  delay(3000);

}

/* 

Des pistes à explorer pour aller plus loin :

- Fabriquer les classes ShiftRegister, et ShiftRegisterManager pour permettre une gestion aisée et dynamique des shift register
- Implementer une fonction qui permet d'exploiter le point
- Si votre classe permet de stoker les etats individuels des shift register, vous pouvez ajouter une fonctionalité qui 
  permettrait d'editer un display de maniere individuelle sans toucher aux autres.


*/
