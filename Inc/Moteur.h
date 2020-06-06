#include "stdio.h"
#include "stdlib.h"
#include "usart.h"
#include "gpio.h"
/*
Notes :

fonctions n�cessaires :

- faire avancer la voiture
- faire tourner la voiture � droite
- faire tourner la voiture � gauche
- faire reculer la voiture


fonction d'initilisation :
d'autres fonctions selon la fonctionnalit�s

Programmer les signaux � envoyer aux drivers
pour la direction : envoyer 0 ou 1 sur le GPO
L'horloge : pwm
Le mode : pas complet, demi pas etc

Signaux aux drivers
controle de la vitesse de rotation, signal PDW , on joue sur la fr�quence, sur la direction, le driver a une entr�e direction
un pas complet, un demi-pas, ...

simulation : sur logic analyser

consulter le fichier de simulation

savoir le GPO de la pin, 
commander en direction, en vitesse
entrer DIR pour la direction
STEP pour la vitesse
*/
typedef struct
{
GPIO_TypeDef * gpioPort;
uint8_t STEP;
uint8_t DIR;

}Driver;


void EntrerDirection();
void Avancer();
void Reculer();
void TournerAGauche();
void TounerADroite();