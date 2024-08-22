#include <avr/io.h>
#include <util/delay.h>

// We will use Timer 0 to set the PWM frequency

#define LED_PIN PB6  // PWM output pin where the LED is connected

void pwm_init() {
    // Initialize Timer 0 in fast PWM mode
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); // Fast PWM, non-inverted mode
    TCCR0B = (1 << CS00); // No prescaling, timer frequency = clock frequency
    DDRD |= (1 << LED_PIN); // Set LED_PIN as an output
}

void pwm_set_duty_cycle(uint8_t duty_cycle) {
    OCR0A = duty_cycle; // Set the duty cycle of the PWM signal
}

int main(void) {
    pwm_init();

    while (1) {
        for (uint8_t brightness = 0; brightness <= 255; brightness++) {
            pwm_set_duty_cycle(brightness);
            _delay_ms(10);
        }

        for (uint8_t brightness = 255; brightness >= 0; brightness--) {
            pwm_set_duty_cycle(brightness);
            _delay_ms(10);
        }
    }

    return 0;
}
