#include "GPIO_Driver.h"

/* Habilita el clock de un puerto: 0=GPIOA, 1=GPIOB, 2=GPIOC ... */
void GPIO_ClockEnable(uint8_t port)
{
    RCC_AHB1ENR |= (1UL << port);
}

/* Configura el modo de un pin (INPUT u OUTPUT) */
void GPIO_PinMode(GPIO_RegDef_t *pGPIO, uint8_t pin, uint8_t mode)
{
    pGPIO->MODER &= ~(3UL << (pin * 2));          /* limpia los 2 bits */
    pGPIO->MODER |=  ((uint32_t)mode << (pin * 2)); /* escribe el modo  */
}

/* Configura pull-up / pull-down de un pin */
void GPIO_PinPullUpDown(GPIO_RegDef_t *pGPIO, uint8_t pin, uint8_t pupd)
{
    pGPIO->PUPDR &= ~(3UL << (pin * 2));
    pGPIO->PUPDR |=  ((uint32_t)pupd << (pin * 2));
}

/* Escribe un valor (0 o 1) en un pin de salida */
void GPIO_WritePin(GPIO_RegDef_t *pGPIO, uint8_t pin, uint8_t value)
{
    if (value)
        pGPIO->ODR |=  (1UL << pin);
    else
        pGPIO->ODR &= ~(1UL << pin);
}

/* Invierte el estado actual de un pin de salida */
void GPIO_TogglePin(GPIO_RegDef_t *pGPIO, uint8_t pin)
{
    pGPIO->ODR ^= (1UL << pin);
}

/* Lee el estado de un pin de entrada: retorna 0 o 1 */
uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIO, uint8_t pin)
{
    return (uint8_t)((pGPIO->IDR >> pin) & 1UL);
}