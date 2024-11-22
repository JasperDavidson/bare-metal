#include "headers/main.h"

// Define global variables
volatile unsigned char led_on = 0;

int main(void) {
    // Enable the GPIOB peripheral in "RCC_AHBENR"
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
 
    // Enable the system configuration peripheral
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Set SYSCFG to connect the button EXTI group to GPIOB
    SYSCFG->EXTICR[(BUTTON_PIN/4)] &= ~(0xF << ((BUTTON_PIN % 4) * 4));
    SYSCFG->EXTICR[(BUTTON_PIN/4)] |= (0x1 << ((BUTTON_PIN % 4) * 4));

    // Enables button EXTI line as an interrupt, only enables the falling-edge trigger
    EXTI->IMR |= (0x1 << BUTTON_PIN);
    EXTI->RTSR &= ~(0x1 << BUTTON_PIN);
    EXTI->FTSR |= (0x1 << BUTTON_PIN);

    // Enable the NVIC interrupt for EXTI0 and EXTI1 at minimum priority.
    NVIC_SetPriority(EXTI0_1_IRQn, 0x1);
    NVIC_EnableIRQ(EXTI0_1_IRQn);

    // Sets the button pin to input mode with a pull-up resistor
    GPIOB->MODER &= ~(0x3 << (BUTTON_PIN*2));
    GPIOB->PUPDR &= ~(0x3 << (BUTTON_PIN*2));
    GPIOB->PUPDR |= (0x1 << (BUTTON_PIN*2));

    // Sets the LED pin to output mode with push-pull output
    GPIOB->MODER &= ~(0x3 << (LED_PIN*2));
    GPIOB->MODER |= (0x1 << (LED_PIN*2));
    GPIOB->OTYPER &= ~(0x1 << LED_PIN);

    // Light the button only if it should be down
    while (1) {
        if (led_on) {
            GPIOB->ODR |= (1<<LED_PIN);
        } else {
            GPIOB->ODR &= ~(1<<LED_PIN);
        }
    }
}