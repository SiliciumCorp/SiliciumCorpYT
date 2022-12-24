/*

   ___|  _)  | _)       _)                         ___|                     
 \___ \   |  |  |   __|  |  |   |  __ `__ \       |       _ \    __|  __ \  
       |  |  |  |  (     |  |   |  |   |   |      |      (   |  |     |   | 
 _____/  _| _| _| \___| _| \__,_| _|  _|  _|     \____| \___/  _|     .__/  
                                                                     _|   
*/

#ifndef RELAI_HEADER
#define RELAI_HEADER       //Evite les inclusions multiples
#include "Arduino.h"       //Charge la librairie Arduino par defaut
 
class DriverRelai                       // Objet relai
{
    private :
        int data_pin;                   //Acceuil la définition du Pin sur la carte arduino
        boolean current_state;          //Définie l'état actuel du relai
 
    public:
        DriverRelai(int);               //Constructeur : attend le pin du relai en parametre.
        void switchOff();               //Met en position NC
        void switchOn();                //Met en position NO
        
        void switchState();             //Inverse l'état actuel du relais
        boolean getCurrentState();      //Renvoie l'etat actuel de current_state
};
 
#endif