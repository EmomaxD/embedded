#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB5  // Arduino'nun D13 pinine karşılık gelir.

int main(void) {
    // LED pinini çıkış olarak ayarlıyoruz.
    DDRB |= (1 << LED_PIN);

    while (1) {
        // LED'i yak.
        PORTB |= (1 << LED_PIN);
        _delay_ms(1000);

        // LED'i söndür.
        PORTB &= ~(1 << LED_PIN);
        _delay_ms(1000);
    }

    return 0;
}
