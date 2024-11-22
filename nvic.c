#include "headers/nvic.h"

void EXTI0_1_IRQ_handler(void) {
    if (EXTI->PR & (1<<BUTTON_PIN)) {
        // Clear the EXTI status flag and toggle the led_on variable
        EXTI->PR |= (1<<BUTTON_PIN);
        
        led_on = !led_on;
    }
}