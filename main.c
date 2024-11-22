#include "headers/main.h"

// Define global variables
volatile unsigned char led_on = 0;

int main(void) {
    // Enable the GPIOB peripheral in "RCC_AHBENR"
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
 
    // Enable the system configuration peripheral
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Set SYSCFG to connect the button EXTI group to GPIOB
    SYSCFG->EXTICR[(ROTARY_PIN_A/4)] &= ~(0xF << ((ROTARY_PIN_A % 4) * 4));
    SYSCFG->EXTICR[(ROTARY_PIN_A/4)] |= (0x1 << ((ROTARY_PIN_A % 4) * 4));

    // Enables button EXTI line as an interrupt, only enables the falling-edge trigger
    EXTI->IMR |= (1 << ROTARY_PIN_A);
    EXTI->RTSR &= ~(1 << ROTARY_PIN_A);
    EXTI->FTSR |= (1 << ROTARY_PIN_A);

    // Enable the NVIC interrupt for EXTI0 and EXTI1 at minimum priority.
    NVIC_SetPriority(EXTI0_1_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_1_IRQn);

    // Sets the button pin to input mode with a pull-up resistor
    GPIOB->MODER &= ~(0x3 << (ROTARY_PIN_A*2));
    GPIOB->PUPDR &= ~(0x3 << (ROTARY_PIN_A*2));
    GPIOB->PUPDR |= (1 << (ROTARY_PIN_A*2));

    // Sets the LED pin to output mode with push-pull output
    GPIOB->MODER &= ~(0x3 << (LED_PIN*2));
    GPIOB->MODER |= (0x1 << (LED_PIN*2));
    GPIOB->OTYPER &= ~(1 << LED_PIN);

    // Light the button only if it should be down
    while (1) {
        if (led_on) {
            GPIOB->ODR |= (1<<LED_PIN);
        } else {
            GPIOB->ODR &= ~(1<<LED_PIN);
        }
    }
}