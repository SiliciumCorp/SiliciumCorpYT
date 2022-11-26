//
// SiliciumCorp Youtube Channel
// Ce programme à pour but de partager des fonctions clés en main afin de manipuler des signaux PWM pour controller des leds RGB
// Passez en revues les fonctions et observez les usages qui en sont fait dans la loop principale.
// Résultats psychédéliques de l'usage de ces fonctions dans la video @8:20
// Vidéo Youtube : https://www.youtube.com/watch?v=awcMiS3cGvk
//

int redpin = 11;
int greenpin = 10;
int bluepin = 9;

//Déclaration d'une structure pour stocker une couleur sous ses 3 composants rouge, vert, bleu.
struct RGB {
    byte r;
    byte g;
    byte b;
};

//Facilite le parametrage d'une variable de type RGB
RGB getColor(byte red, byte green, byte blue){
    RGB new_color;
    new_color.r = red;
    new_color.g = green;
    new_color.b = blue;
    return new_color;
}

//Applique a la LED le signal correspondant à une couleur fournit en parametre
void applyColor(RGB color){
    analogWrite(redpin, color.r);  //Applique un signal PWM pour le rouge
    analogWrite(greenpin, color.g); //Applique un signal PWM pour le vert
    analogWrite(bluepin, color.b); //Applique un signal PWM pour le bleu
}

//Eteint la LED
void switchOff(){
    analogWrite(redpin, 0);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);
}

//Attend une seule couleur et permet de faire clignoter la LED
void flashOneColor(RGB color, int count_flash=1, int up_delay=150, int down_delay=150){
    for(int i = 0; i < count_flash; i++){
        applyColor(color);
        delay(up_delay);
        switchOff();
        delay(down_delay);
    }
}

//Permet de faire clignoter la LED dans des couleurs aléatoires
void flashRandomColor(int count_flash=1, int up_delay=150, int down_delay=150){
    RGB next_color;

    for(int i = 0; i < count_flash; i++){
        next_color.r = random(0,255);
        next_color.g = random(0,255);
        next_color.b = random(0,255);

        applyColor(next_color);
        delay(up_delay);
        switchOff();
        delay(down_delay);
    }
}

//Attend un tableau de couleurs et permet de faire clignoter la LED en faisant une rotation des couleurs du tableau.
void flashCycleColor(RGB cycle_color[], int size_cycle, int count_cycle=1, int up_delay=150, int down_delay=150){
    for (int c = 0; c < count_cycle; c++){
        for (byte i = 0; i < size_cycle; i++) {
            applyColor(cycle_color[i]);
            delay(up_delay);
            switchOff();
            delay(down_delay);
        }
    }
}

//Permet de faire une transition progressive entre 2 couleurs sur une periode de temps donné.
void twoColorTransition(RGB from_color, RGB to_color, int action_delay=1000){

    RGB current_color;

    //Calcule de la difference entre la couleur de destination et la couleur de point de départ
    long red_diff = from_color.r - to_color.r;
    long green_diff = from_color.g - to_color.g;
    long blue_diff = from_color.b - to_color.b;

    //Variable d'interuption de la boucle while ci dessous
    bool transitionProcess = true;

    //Variable utile pour le calcul du pourcentage de progression entre la couleur d'origine et la couleur de destination
    long elapsed_time = 0;
    long start_time = millis();

    //Commence la transition entre les 2 couleurs
    while(transitionProcess){

        //On regarde combien de temps s'est ecoulé depuis le lancement de la fonction de transition
        elapsed_time = millis() - start_time;

        //Si le temps ecoulé est supérieure au delai de l'action de transition, alors inutile de continuer
        if(elapsed_time >= action_delay){
            transitionProcess = false;
            elapsed_time = action_delay;
        }

        //ici on applique la proportion de temps ecoulé au temps ciblé pour savoir a quel niveau devrai etre la LED
        int red_add = (((double)elapsed_time / (double)action_delay) * (double)red_diff) * (-1.0);
        int green_add = (((double)elapsed_time / (double)action_delay) * (double)green_diff) * (-1.0);
        int blue_add = (((double)elapsed_time / (double)action_delay) * (double)blue_diff) * (-1.0);

        //On applique les corrections calculées a l'étape precedente a la couleur d'origine
        current_color.r = from_color.r + red_add;
        current_color.g = from_color.g + green_add;
        current_color.b = from_color.b + blue_add;

        //On applique la nouvelle couleur sur la LED
        applyColor(current_color);

        //On attend 17ms, (Correspond grossierement à une frequence de rafraichissement de 70 Hz)
        delay(17);
    }
}

//Declaration d'un lot de 5 couleurs de type RGB
RGB color_red;
RGB color_yellow;
RGB color_green;
RGB color_cyan;
RGB color_blue;
RGB color_purple;
RGB color_black;
RGB color_white;

//Declaration de tableau de type RGB pour stoker des cycles de couleur
RGB cycle_color_RYGCBP[6];
RGB cycle_color_RBG[3];
RGB cycle_color_RGBG[4];
RGB cycle_color_RBGB[4];

void setup() {
    Serial.begin(9600);

    randomSeed(analogRead(0));

    color_red = getColor(255, 0, 0);
    color_yellow = getColor(255, 2555, 0);
    color_green = getColor(0, 255, 0);
    color_cyan = getColor(0, 255, 255);
    color_blue = getColor(0, 0, 255);
    color_purple = getColor(255, 0, 255);
    color_black = getColor(0, 0, 0);
    color_white = getColor(255, 255, 255);

    cycle_color_RYGCBP[0] = color_red;
    cycle_color_RYGCBP[1] = color_yellow;
    cycle_color_RYGCBP[2] = color_green;
    cycle_color_RYGCBP[3] = color_cyan;
    cycle_color_RYGCBP[4] = color_blue;
    cycle_color_RYGCBP[5] = color_purple;

    cycle_color_RGBG[0] = color_red;
    cycle_color_RGBG[1] = color_green;
    cycle_color_RGBG[2] = color_blue;
    cycle_color_RGBG[3] = color_green;

    cycle_color_RBGB[0] = color_red;
    cycle_color_RBGB[1] = color_blue;
    cycle_color_RBGB[2] = color_green;
    cycle_color_RBGB[3] = color_blue;

    applyColor(color_white);
    delay(5000);
}

void loop() {

    /*flashRandomColor(50, 75, 75);
    switchOff();
    delay(2000);

    flashCycleColor(cycle_color_RYGCBP, 6, 10, 500, 150);
    switchOff();
    delay(2000);

    flashOneColor(color_green, 50, 75, 75);
    switchOff();
    delay(2000);*/

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_yellow, 30);
        twoColorTransition(color_yellow, color_green, 30);
        twoColorTransition(color_green, color_cyan, 30);
        twoColorTransition(color_cyan, color_blue, 30);
        twoColorTransition(color_blue, color_purple, 30);
        twoColorTransition(color_purple, color_red, 30);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_green, 55);
        twoColorTransition(color_green, color_blue, 55);
        twoColorTransition(color_blue, color_red, 55);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_green, 75);
        twoColorTransition(color_green, color_blue, 75);
        twoColorTransition(color_blue, color_red, 75);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_green, 95);
        twoColorTransition(color_green, color_blue, 95);
        twoColorTransition(color_blue, color_red, 95);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_green, 115);
        twoColorTransition(color_green, color_blue, 115);
        twoColorTransition(color_blue, color_red, 115);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_green, 135);
        twoColorTransition(color_green, color_blue, 135);
        twoColorTransition(color_blue, color_red, 135);
    }
    switchOff();
    delay(1000);


    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_blue, 115);
        twoColorTransition(color_blue, color_green, 115);
        twoColorTransition(color_green, color_red, 115);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_blue, 135);
        twoColorTransition(color_blue, color_green, 135);
        twoColorTransition(color_green, color_red, 135);
    }
    switchOff();
    delay(1000);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_blue, 55);
        twoColorTransition(color_blue, color_red, 55);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_blue, 115);
        twoColorTransition(color_blue, color_red, 115);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_blue, 135);
        twoColorTransition(color_blue, color_red, 135);
    }
    switchOff();
    delay(1000);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_green, 55);
        twoColorTransition(color_green, color_red, 55);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_green, 115);
        twoColorTransition(color_green, color_red, 115);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_red, color_green, 135);
        twoColorTransition(color_green, color_red, 135);
    }
    switchOff();
    delay(1000);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_blue, color_green, 55);
        twoColorTransition(color_green, color_blue, 55);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_blue, color_green, 115);
        twoColorTransition(color_green, color_blue, 115);
    }
    switchOff();
    delay(200);

    for(byte i = 0; i < 10; i++){
        twoColorTransition(color_blue, color_green, 135);
        twoColorTransition(color_green, color_blue, 135);
    }
    switchOff();
    delay(1000);

    flashCycleColor(cycle_color_RGBG, 4, 10, 55, 55);
    switchOff();
    delay(200);

    flashCycleColor(cycle_color_RBGB, 4, 10, 55, 55);
    switchOff();
    delay(200);

    flashCycleColor(cycle_color_RGBG, 4, 10, 100, 100);
    switchOff();
    delay(200);

    flashCycleColor(cycle_color_RBGB, 4, 10, 100, 100);
    switchOff();
    delay(200);

    flashCycleColor(cycle_color_RYGCBP, 6, 10, 100, 100);
    switchOff();
    delay(200);

    flashCycleColor(cycle_color_RYGCBP, 6, 10, 50, 50);
    switchOff();
    delay(1000);
}