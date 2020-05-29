#include "button.h"
#include "stm32f1xx_ll_exti.h"

void Button_init(BUTTON_TypeDef *button, GPIO_TypeDef * port, uint8_t pn,
		uint8_t pl) {

	button->gpioPort = port;
	button->pin = pn;
	button->pull = pl;

	//Activation de l'horloge sur le port en question

	//déterminer le numéro du port 0--> GPIOA, 1-->GPIOB, etc.
	uint8_t nb_port;
	nb_port = ((uint32_t) port - GPIOA_BASE) / 0x400;
	//activation de l'hologe
			RCC->APB2ENR|=(1<<(nb_port+2));
	//configuration de la pin en entrée
			if(	button->pin<8)
	button->gpioPort->CRL &= ~(3 << 4 * pn);
else 
		button->gpioPort->CRH &= ~(3 << 4 * pn);
	//configuration du type de pull
	/*button->gpioPort->PUPDR &= ~(0b11 << 2 * pn);
	button->gpioPort->PUPDR |= (pl << 2 * pn);*/
			if (button->pull==LL_GPIO_PULL_NO) //CF1 CNF0=01
			{
					if(	button->pin<8)
						button->gpioPort->CRL |= (1 << (4 * pn+2));
						else 
						button->gpioPort->CRH |= (1 << (4 * pn+2));
			}	
			if (button->pull==LL_GPIO_PD) //CF1 CNF0=10, ODR=0
			{
					if(	button->pin<8){
						button->gpioPort->CRL &=~ (3 << (4 * pn+2));
						button->gpioPort->CRL |= (2 << (4 * pn+2));
					}
						else {
						button->gpioPort->CRH &=~ (3 << (4 * pn+2));	
						button->gpioPort->CRH |= (2 << (4 * pn+2));
						}
						
						button->gpioPort->ODR&=~(1<<pn);
						
			}	
			
			if (button->pull==LL_GPIO_PU) //CF1 CNF0=10, ODR=1
			{
					if(	button->pin<8){
						button->gpioPort->CRL &=~ (3 << (4 * pn+2));
						button->gpioPort->CRL |= (2 << (4 * pn+2));
					}
						else {
						button->gpioPort->CRH &=~ (3 << (4 * pn+2));	
						button->gpioPort->CRH |= (2 << (4 * pn+2));
						}
						button->gpioPort->ODR|=(1<<pn);					
			}			
}


uint8_t Button_State(BUTTON_TypeDef *button) {
if ((button->gpioPort->ODR & (1<<5)) != 0){
return 1;
}
else{return 0;}
}

void Button_enableIRQ(BUTTON_TypeDef *button, uint8_t trigger) {

	//détermination du numéro d'EXTI
	uint8_t nb_EXTI = button->pin / 4;
	//déterminer le numéro du port 0--> GPIOA, 1-->GPIOB, etc.
	uint8_t nb_port;
	nb_port = ((uint32_t) button->gpioPort - GPIOA_BASE) / 0x400;

	//activation de l'interruption externe
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[nb_EXTI] &= ~(15 << 4 * (button->pin % 4));
	AFIO->EXTICR[nb_EXTI] |= (nb_port << 4 * (button->pin % 4));

	//activation d'EXTI dans IMR pour qu’elle ne soit pas masquée
	EXTI->IMR |= (1 << button->pin); 

        //activation du type du trigger (front montant/descendant)
	switch (trigger) {
	case LL_EXTI_TRIGGER_RISING:
	//activation de l'interruption sur front montant dans RTSR
		break;
	case LL_EXTI_TRIGGER_FALLING:
	//activation de l'interruption sur front descendant dans FTSR
		break;
	case LL_EXTI_TRIGGER_RISING_FALLING:
		//activation de l'interruption sur front montant
		//activation de l'interruption sur front descendant
		break;
	}

        /*activer un vecteur d’interruption EXTI parmi les vecteurs disponibles selon le numéro de pin*/

	if (button->pin ==0) {
		NVIC_EnableIRQ(EXTI0_IRQn); 
		NVIC_SetPriority(EXTI0_IRQn, 0); 
	} 
    }



