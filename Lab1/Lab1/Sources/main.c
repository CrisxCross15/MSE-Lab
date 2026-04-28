#include <stdint.h>
#include "GPIO_Driver.h"
#include "button.h"

/* ── SysTick ──────────────────────────────────────────────────────────────── */
#define SYSTICK_BASE  (0xE000E010UL)
#define SYST_CSR  (*(volatile uint32_t *)(SYSTICK_BASE + 0x00UL))
#define SYST_RVR  (*(volatile uint32_t *)(SYSTICK_BASE + 0x04UL))
#define SYST_CVR  (*(volatile uint32_t *)(SYSTICK_BASE + 0x08UL))

#define CPU_FREQ_HZ  16000000UL

#define LED_PORT  GPIOA
#define LED_PIN   5

volatile unsigned long ms_ticks = 0;

void SysTick_Handler(void)
{
    ms_ticks++;
}

unsigned long get_ms(void)
{
    return ms_ticks;
}

int main(void)
{
    /* ── SysTick: 1 ms ── */
    SYST_RVR = (CPU_FREQ_HZ / 1000UL) - 1UL;
    SYST_CVR = 0;
    SYST_CSR = (1UL << 2) | (1UL << 1) | (1UL << 0);

    /* ── LED ── */
    GPIO_ClockEnable(0);
    GPIO_PinMode(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT);
    GPIO_WritePin(LED_PORT, LED_PIN, 0);

    /* ── Botón ── */
    Button_Init();

    uint8_t led_state = 0;

    for (;;)
    {
        if (Button_WasClicked(get_ms()))
        {
            led_state ^= 1;
            GPIO_WritePin(LED_PORT, LED_PIN, led_state);
        }
    }
}