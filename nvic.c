#include "headers/nvic.h"

void EXTI0_1_IRQ_handler(void) {
    // If the first rotary pin was already triggered (i.e. specific turn direction) turn the led on
    if (GPIOB->IDR & (1<<ROTARY_PIN_B)) {
        led_on = 1;
    } else {
        led_on = 0;
    }
}