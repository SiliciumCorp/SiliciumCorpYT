//
// SiliciumCorp Youtube Channel
// Ce programme à pour but de passer en revue les bases du concept du signal PWM.
// Vidéo Youtube : https://www.youtube.com/watch?v=awcMiS3cGvk
//

//Declaration des 3 ports PWM correspondant à chaque couleur
int redpin = 11;
int greenpin = 10;
int bluepin = 9;

//Utiliser dans la boucle principal pour interpreter la couleur à emettre
int redLevel = 0;
int greenLevel = 0;
int blueLevel = 0;

//Valeur de la quantité de lumiere emise par la LED correspondante
int redAmount = 0;
int greenAmount = 0;
int blueAmount = 0;

void setup() {
    //Initialiation de la communication série
    Serial.begin(9600);

    //Parametrage des ports en mode SORTIE
    pinMode(redpin, OUTPUT);
    pinMode(greenpin, OUTPUT);
    pinMode(bluepin, OUTPUT);

    //On commence par eteindre completement la LED
    analogWrite(redpin, 0);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);

}

void loop()
{
    //Boucle pour naviguer entre 3 niveaux de rouge
    for(redLevel = 0; redLevel < 3; redLevel++){
        //Conversion du niveau de rouge en valeur analogique comprise entre 0 et 255
        redAmount = map(redLevel, 0, 2, 0, 255);

        //Boucle pour naviguer entre 3 niveaux de vert
        for(greenLevel = 0; greenLevel < 3; greenLevel++){
            //Conversion du niveau de vert en valeur analogique comprise entre 0 et 255
            greenAmount = map(greenLevel, 0, 2, 0, 255);

            //Boucle pour naviguer entre 3 niveaux de bleue
            for(blueLevel = 0; blueLevel < 3; blueLevel++){
                //Conversion du niveau de bleu en valeur analogique comprise entre 0 et 255
                blueAmount = map(blueLevel, 0, 2, 0, 255);

                //On envoie sur le moniteur serie la valeur actuelle de chaque couleur
                Serial.print("R:");
                Serial.print(redAmount);
                Serial.print(" G:");
                Serial.print(greenAmount);
                Serial.print(" B:");
                Serial.println(blueAmount);

                //On ecrit la valeur analogique sur les ports de l'Arduino
                analogWrite(redpin, redAmount);
                analogWrite(greenpin, greenAmount);
                analogWrite(bluepin, blueAmount);

                //Pause de 500ms avant de passer à la couleur suivante
                delay(500);
            }
        }
    }
}