#include "led.h"

void Led_init(LED_TypeDef *led, GPIO_TypeDef * port, uint8_t pn){

	led->gpioPort=port;
	led->pin=pn;

	//Activation de l'horloge sur le port en question

	//déterminer le numéro du port 0--> GPIOA, 1-->GPIOB, etc.
	uint8_t nb_port;
	nb_port=(uint32_t)((uint32_t *)port - GPIOA_BASE)/ (uint32_t)0x400;
	//activation de l'hologe
RCC->APB2ENR|=(1<<(nb_port+2));

	//configuration de la pin en sortie
	if(	led->pin<8){
	led->gpioPort->CRL &= ~(3 << (4 * pn+2));	//CNF1 CNF0 = 00
	led->gpioPort->CRL &= ~(3 << 4 * pn);
	led->gpioPort->CRL |= (1 << 4 * pn);	
	}
else {
	  led->gpioPort->CRH &= ~(3 << (4 * pn+2));	//CNF1 CNF0 = 00
		led->gpioPort->CRH &= ~(3 << 4 * pn);
	  led->gpioPort->CRH |= (1 << 4 * pn);	
}
}


void Led_turnOn(LED_TypeDef *led){
led->gpioPort->ODR|=(1<<5);
}


void Led_turnOff(LED_TypeDef *led){
led->gpioPort->ODR&=~(1<<5);
}

void Led_toggle(LED_TypeDef *led){
led->gpioPort->ODR^=(1<<5);
}

uint8_t Led_isOn(LED_TypeDef *led){
if ((led->gpioPort->ODR&(1<<5)) != 0){
	return 1;
}
else{
	return 0;
}

}

uint8_t Led_isOff(LED_TypeDef *led){
if (( led->gpioPort->ODR & (1<<5)) == 0){
return 1;
}
else{
return 0;
}

}

