#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB5  // Corresponds to Arduino's D13 pin.

int main(void) {
    // Set the LED pin as an output.
    DDRB |= (1 << LED_PIN);

    while (1) {
        // Turn the LED on.
        PORTB |= (1 << LED_PIN);
        _delay_ms(1000);

        // Turn the LED off.
        PORTB &= ~(1 << LED_PIN);
        _delay_ms(1000);
    }

    return 0;
}
