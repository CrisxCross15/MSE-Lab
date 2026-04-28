#include "button.h"

static uint8_t       btn_prev       = 1;
static unsigned long last_press_ms  = 0;

void Button_Init(void)
{
    GPIO_ClockEnable(2);
    GPIO_PinMode(BUTTON_PORT, BUTTON_PIN, GPIO_MODE_INPUT);
    GPIO_PinPullUpDown(BUTTON_PORT, BUTTON_PIN, GPIO_PUPD_NONE);
}

/* Retorna 1 UNA SOLA VEZ cuando detecta un click válido */
uint8_t Button_WasClicked(unsigned long current_ms)
{
    uint8_t btn_now  = (GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == 0) ? 1 : 0;
    uint8_t clicked  = 0;

    /* Flanco de bajada: botón acaba de presionarse */
    if (btn_prev == 0 && btn_now == 1)
    {
        /* Debounce: ignorar si no han pasado 20 ms desde el último click */
        if ((current_ms - last_press_ms) >= DEBOUNCE_MS)
        {
            clicked       = 1;
            last_press_ms = current_ms;
        }
    }

    btn_prev = btn_now;
    return clicked;
}