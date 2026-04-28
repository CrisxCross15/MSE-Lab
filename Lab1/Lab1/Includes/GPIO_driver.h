#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

/* ── Direcciones base ─────────────────────────────────────────────────────── */
#define RCC_BASE    (0x40023800UL)
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30UL))

#define GPIOA_BASE  (0x40020000UL)
#define GPIOB_BASE  (0x40020400UL)
#define GPIOC_BASE  (0x40020800UL)

/* ── Estructura que representa un puerto GPIO completo ────────────────────── */
typedef struct
{
    volatile uint32_t MODER;    /* offset 0x00 */
    volatile uint32_t OTYPER;   /* offset 0x04 */
    volatile uint32_t OSPEEDR;  /* offset 0x08 */
    volatile uint32_t PUPDR;    /* offset 0x0C */
    volatile uint32_t IDR;      /* offset 0x10 */
    volatile uint32_t ODR;      /* offset 0x14 */
    volatile uint32_t BSRR;     /* offset 0x18 */
} GPIO_RegDef_t;

/* ── Punteros a cada puerto ───────────────────────────────────────────────── */
#define GPIOA  ((GPIO_RegDef_t *) GPIOA_BASE)
#define GPIOB  ((GPIO_RegDef_t *) GPIOB_BASE)
#define GPIOC  ((GPIO_RegDef_t *) GPIOC_BASE)

/* ── Modos de pin ─────────────────────────────────────────────────────────── */
#define GPIO_MODE_INPUT   0U
#define GPIO_MODE_OUTPUT  1U

/* ── Pull-up / Pull-down ──────────────────────────────────────────────────── */
#define GPIO_PUPD_NONE    0U
#define GPIO_PUPD_PULLUP  1U

/* ── Prototipos ───────────────────────────────────────────────────────────── */
void     GPIO_ClockEnable(uint8_t port);
void     GPIO_PinMode(GPIO_RegDef_t *pGPIO, uint8_t pin, uint8_t mode);
void     GPIO_PinPullUpDown(GPIO_RegDef_t *pGPIO, uint8_t pin, uint8_t pupd);
void     GPIO_WritePin(GPIO_RegDef_t *pGPIO, uint8_t pin, uint8_t value);
void     GPIO_TogglePin(GPIO_RegDef_t *pGPIO, uint8_t pin);
uint8_t  GPIO_ReadPin(GPIO_RegDef_t *pGPIO, uint8_t pin);

#endif /* GPIO_DRIVER_H */