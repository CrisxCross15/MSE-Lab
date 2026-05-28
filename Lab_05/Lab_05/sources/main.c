#include "timer.h"
#include "LCD_driver.h"

int main(void)
{
    timer_init();
    lcd_init();

    lcd_print_string("Hello World!");

    while (1) { }

    return 0;
}