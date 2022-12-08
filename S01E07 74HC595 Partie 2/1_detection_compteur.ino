//
// SiliciumCorp Youtube
// Ce programme à pour but de presenter le composant PIC 74HC595 8 Bit-shift register
// Dans cette example on envoie des valeurs decimales au shift register dans l'objectif de voir apparaitre les chiffres de 0 à 9
// Deux boucles permettent de tester la data dans les deux sens de lecture binaire
//
// Vidéo Youtube : https://youtu.be/jFUmCvr2LKs
//

#define PIN_DS_DATA 4
#define PIN_STCP_LATCH 5
#define PIN_SHCP_CLOCK 6

//Valeur décimales qui représentées en binaire permettent 
//d'allumer les led correspondantes aux chiffres de 0 à 9
byte numbers[10] = {238, 40, 205, 109, 43, 103, 231, 44, 239, 111};

void setup() {
   //On définie les 3 ports en mode OUTPUT
  pinMode(PIN_STCP_LATCH, OUTPUT);
  pinMode(PIN_SHCP_CLOCK, OUTPUT);
  pinMode(PIN_DS_DATA, OUTPUT);

  //On setup et initialise la led intégré à la carte qui servira de temoin
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {

  //On allume la led integrée == LSBFIRST
  digitalWrite(LED_BUILTIN, HIGH);

  //On execute une boucle de 10 tours pour visiter les 10 chiffres de 0 à 9
  for (byte i = 0; i < 10; i++) {
    //On s'assure que la gachette est a l'etat LOW
    digitalWrite(PIN_STCP_LATCH, LOW);
    
    //On utlise la fonction shiftOut de la librairie 
    //arduino pour lui soumettre la valeur à transmettre au registre
    shiftOut(PIN_DS_DATA, PIN_SHCP_CLOCK, LSBFIRST, numbers[i]);
    
    //On inverse l'etat de la gachette pour mettre à jour le registre
    digitalWrite(PIN_STCP_LATCH, HIGH);
    
    //Un delais d'une demi seconde avant le prochain tour de boucle
    delay(500);
  }

  //On allume la led integrée == MSBFIRST
  digitalWrite(LED_BUILTIN, LOW);

  //On execute une boucle de 10 tours pour visiter les 10 chiffres de 0 à 9 
  for (byte i = 0; i < 10; i++) {
    //On s'assure que la gachette est a l'etat LOW
    digitalWrite(PIN_STCP_LATCH, LOW);
    
    //On utlise la fonction shiftOut de la librairie 
    //arduino pour lui soumettre la valeur à transmettre au registre
    shiftOut(PIN_DS_DATA, PIN_SHCP_CLOCK, MSBFIRST, numbers[i]);
    
    //On inverse l'etat de la gachette pour mettre à jour le registre
    digitalWrite(PIN_STCP_LATCH, HIGH);
    
    //Un delais d'une demi seconde avant le prochain tour de boucle
    delay(500);
  }
}
