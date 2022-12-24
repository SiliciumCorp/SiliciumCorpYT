/*

   ___|  _)  | _)       _)                         ___|                     
 \___ \   |  |  |   __|  |  |   |  __ `__ \       |       _ \    __|  __ \  
       |  |  |  |  (     |  |   |  |   |   |      |      (   |  |     |   | 
 _____/  _| _| _| \___| _| \__,_| _|  _|  _|     \____| \___/  _|     .__/  
                                                                     _|   
*/

#include "DriverRelai.h"

// On declare un objet de type DriverRelai
DriverRelai mon_relai(2);


void setup() {
  //On ammorce la connection serial
  Serial.begin(9600);
}

void loop() {
  
  //On force l'allumage du relai.
  mon_relai.switchOn();

  //Attente 2sec
  delay(2000);

  //On force l'extinction du relai.
  mon_relai.switchOff();

  //Attente 2sec
  delay(2000);

  //Boucle de 6 tours qui va inverser l'etat à chaque tour. (Dure au total 1.2 sec)
  //Sachant que le nombre de tour est pair, le relai doit resortir de cette boucle a l'etat ETEINT
  for (int i = 0; i < 6; i++){
    //On inverse l'etat.
    mon_relai.switchState();
    //Attente 0.2 sec
    delay(200);
  }

  //Envoie sur le port serie l'etat actuel du relai. 
  //Le membre current_state etant un boolean, est attendu le nombre 0 dans le moniteur serie
  Serial.println(mon_relai.getCurrentState());
  

}
