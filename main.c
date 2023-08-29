/*
    Nom du projet : DIAGNOSTIC NUMÉRIQUE - Compteur 7-segment - CEGEP de Maisonneuve
    Auteur : Alexandre Gagne - Etienne Vibert
    Date : 2023-08-29

    Processeur : PIC18F25K80
    Compilateur : XC8
    IDE : MPLAB X 2.40
    Disclaimer : Le code ci-dessous a ete ecrit sous la contrainte de notre 
    professeur. Au secours!
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
// ************** REDEFINITION DES BROCHES ******************

//********SORTIES**************
#define DEL IO_RA5_LAT

#define BCD_A IO_RA0_LAT           // 
#define BCD_B IO_RA1_LAT           // 
#define BCD_C IO_RA2_LAT           // 
#define BCD_D IO_RA3_LAT           // 

#define DEL1 IO_RC1_LAT           // active high led
#define DEL2 IO_RC2_LAT           // active high led
#define DEL3 IO_RC3_LAT           // active high led
#define DEL4 IO_RC4_LAT           // active high led
#define DEL5 IO_RC5_LAT           // active high led

#define ANODE IO_RC0_PORT          // anode 7-segments

//********ENTREES****************

#define BOUTON IO_RB0_PORT           //pressed-low

//---------Prototypes------------

// Prototype pour le fonctionne des LEDS sur les pins du port C
//void tout_eteint();
//void tout_allume();
//void compteur();
//void Dels();

void cligne (unsigned nb); // Signal du debut du programme, la led cligne 5 fois.
void afficheur(int var_compteur); // Affiche un chiffre de 0 - 5

//--------Variables globales-------

int var_compteur = 0; // Integer, initialisation de la variable compteur avec la valeur 0.

//------------------ Programme principal ---------------------

void main(void) 
{
     SYSTEM_Initialize(); // Initialisation du programme

     unsigned maintien=0; // Maintien ne peux contenir que des valeurs positives.
     
     cligne (5); // Code de demarrage, cligne 5 fois
     
     while(1){
         if (BOUTON==0) {                       // Si le bouton est presse, 
             if (maintien == 0) {               // Si maintien = 0
                 afficheur(var_compteur);       // on affiche, var_comp
                 var_compteur++;                // incremente, var_comp
                 if (var_compteur > 5) {        // si var_comp plus grand que 5
                     var_compteur = 0;          // reinitialise var_comp = 0
                 }
                 maintien = 1;                  // maintien a 1 pour debounce
                 __delay_ms(250);               // delay 250ms
             }
         }
         else {
             maintien = 0;                      // maintien = 0, attente bouton.
         }
     }
}


//-------------------Fonctions --------------------

void cligne (unsigned nb) {
    for (unsigned i=0;i<nb;i++){
        DEL=1;
        __delay_ms(200);
        DEL=0;
        __delay_ms(200);
    }
    
}


void tout_allume() {
    //afficheur
    
    ANODE=0;
    
    BCD_A=0;
    BCD_B=0;
    BCD_C=0;
    BCD_D=0;
    
    //Dels
    
    DEL1=0;
    DEL2=0;
    DEL3=0;
    DEL4=0;
    DEL5=0;
}

void tout_eteint() {
    
    //afficheur
    
    ANODE=1;
        
    //Dels
    
    DEL1=1;
    DEL2=1;
    DEL3=1;
    DEL4=1;
    DEL5=1;
    
}

void compteur() {
    
    
    if (var_compteur==5){
        var_compteur=0;
    }
    else {
        var_compteur++;
    }
}

void afficheur(int var_compteur) {
    
    switch (var_compteur) {
        case 0:
            BCD_A=0;
            BCD_B=0;
            BCD_C=0;
            BCD_D=0;
            break;
            
        case 1:
            BCD_A=1;
            BCD_B=0;
            BCD_C=0;
            BCD_D=0;
            break;
            
        case 2:
            BCD_A=0;
            BCD_B=1;
            BCD_C=0;
            BCD_D=0;
            break;
            
        case 3:
            BCD_A=1;
            BCD_B=1;
            BCD_C=0;
            BCD_D=0;
            break;
            
        case 4:
            BCD_A=0;
            BCD_B=0;
            BCD_C=1;
            BCD_D=0;
            break;
            
        case 5:
            BCD_A=1;
            BCD_B=0;
            BCD_C=1;
            BCD_D=0;
            break;
    }
}

void Dels(int var_compteur) {
    
    switch (var_compteur) {
        
        case 0: 
            DEL1=0;
            DEL2=0;
            DEL3=0;
            DEL4=0;
            DEL5=0;
            break;
            
        case 1: 
            DEL1=1;
            DEL2=0;
            DEL3=0;
            DEL4=0;
            DEL5=0;
            break;
            
        case 2: 
            DEL1=1;
            DEL2=1;
            DEL3=0;
            DEL4=0;
            DEL5=0;
            break;
            
        case 3: 
            DEL1=1;
            DEL2=1;
            DEL3=1;
            DEL4=0;
            DEL5=0;
            break;
                  
        case 4: 
            DEL1=1;
            DEL2=1;
            DEL3=1;
            DEL4=1;
            DEL5=0;
            break;
            
        case 5: 
            DEL1=1;
            DEL2=1;
            DEL3=1;
            DEL4=1;
            DEL5=1;
            break;
    }
            
            
}