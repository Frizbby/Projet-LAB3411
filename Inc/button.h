#include "stm32f103xb.h"
#define LL_GPIO_PULL_NO 0
#define LL_GPIO_PD 1
#define LL_GPIO_PU 2
typedef struct
{
GPIO_TypeDef * gpioPort;
uint8_t pin;
uint8_t pull;

}BUTTON_TypeDef;

void Button_init(BUTTON_TypeDef *button, GPIO_TypeDef * port, uint8_t pn, uint8_t pl);

uint8_t Button_State(BUTTON_TypeDef *button);

void Button_enableIRQ(BUTTON_TypeDef *button, uint8_t trigger);
