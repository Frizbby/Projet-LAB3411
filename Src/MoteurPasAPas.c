#include "Moteur.h"
#include "stdio.h"

void EntrerDirection(){
		char direction;
		
		scanf("%c",&direction);
		//printf("Vous avez entré : %c\n",direction);
		if(direction=='z'){
			printf("Vous avez entré : z\n");
			Avancer();
		}
		if(direction=='q'){
			printf("Vous avez entré : q\n");
			TournerAGauche();
		}
		if(direction=='s'){
			printf("Vous avez entré : s\n");
			Reculer();
		}
		if(direction=='d'){
			printf("Vous avez entré : d\n");
			TounerADroite();
		}
}

void Avancer(){
	// Rappel : HCLK = 16MHz
TIM_TypeDef *timer = TIM1; // Adapter plus bas si TIM2 `aTIM4
float rapCyclique = 0.3;
uint32_t freqPWM = 1; // 0.2 `a100 Hz
uint8_t nTimer = 1; // Num´ero du timer. // Adapter plus bas si TIM2 `aTIM4
uint8_t canal = 1;
// Activation de l 'horloge du timer. !!! Valable que pour TIM1
RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_TIM1EN;
// Activation du canal
timer ->CCER = timer->CCER | 1 << (nTimer -1);
// Activation PWM en ´ecrivant 110 dans OCMx (x le num de canal) du registre CCMR1 ou CCMR2
uint8_t decal = 0;
uint16_t ocm = 6;
if (canal <= 2) {
decal = 4 + (canal - 1) * 4;
timer ->CCMR1 = (timer->CCMR1 & ~(7 << decal)) | ocm << decal;
}
else { // Canaux 3 et 4
decal = 4 + (canal - 3) * 4;
timer ->CCMR1 = (timer->CCMR1 & ~(7 << decal)) | ocm << decal;
}
timer ->PSC = 159;
timer ->ARR = 100000.0 / freqPWM;
// Rapport cyclique. Fraction calcul´ee entre 1 et valeur de ARR
uint16_t ccr = timer->ARR *3;
switch (canal){
case 1: timer ->CCR1 = ccr;
break;
case 2: timer ->CCR2 = ccr;
break;
case 3: timer ->CCR3 = ccr;
break;
case 4: timer ->CCR4 = ccr;
break;
}
// Active la sortie
timer ->BDTR |= (TIM_BDTR_MOE);
// D´emarrer le compteur
timer ->CR1 |= TIM_CR1_CEN;

// Activation de la broche de sortie en alternate fonction
// Cf manuel r´ef´erence chap 9.3 Alternate function I/O and debug configuration (AFIO)
// En choisissant le timer 1 et son canal 1, la sortie est sur PA8
GPIOA->CRH = ( GPIOA->CRH & ~GPIO_CRH_CNF8_Msk ) | 2 << GPIO_CRH_CNF8_Pos;
GPIOA->CRH = ( GPIOA->CRH & ~GPIO_CRH_MODE8_Msk ) | 1 << GPIO_CRH_MODE8_Pos;
GPIOA->CRH = ( GPIOA->CRH & ~GPIO_CRH_CNF9_Msk ) | 2 << GPIO_CRH_CNF9_Pos;
GPIOA->CRH = ( GPIOA->CRH & ~GPIO_CRH_MODE9_Msk ) | 1 << GPIO_CRH_MODE9_Pos;
}

void Reculer(){
	
}

void TournerAGauche(){

}

void TounerADroite(){

}
