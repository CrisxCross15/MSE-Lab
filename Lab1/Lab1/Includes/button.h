#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include "GPIO_Driver.h"

#define BUTTON_PORT        GPIOC
#define BUTTON_PIN         13
#define DEBOUNCE_MS        20UL    /* tiempo de espera para ignorar rebotes */

void    Button_Init(void);
uint8_t Button_WasClicked(unsigned long current_ms);

#endif /* BUTTON_H */