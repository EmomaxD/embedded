#include <avr/io.h>
#include <util/delay.h>

// PWM frekansını ayarlamak için Timer 0'ı kullanacağız

#define LED_PIN PB6  // LED'in bağlı olduğu PWM çıkış pini

void pwm_init() {
    // Timer 0'ı hızlı PWM modunda başlat
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); // Fast PWM, non-inverted mode
    TCCR0B = (1 << CS00); // No prescaling, timer frequency = clock frequency
    DDRD |= (1 << LED_PIN); // LED_PIN'i çıkış olarak ayarla
}

void pwm_set_duty_cycle(uint8_t duty_cycle) {
    OCR0A = duty_cycle; // PWM sinyalinin darbe genişliğini ayarla
}

int main(void) {
    pwm_init(); // PWM yapılandırmasını başlat

    while (1) {
        // LED'i yavaşça parlaklaştırma
        for (uint8_t brightness = 0; brightness <= 255; brightness++) {
            pwm_set_duty_cycle(brightness);
            _delay_ms(10); // Parlaklık değişimi arasında kısa bir gecikme
        }

        // LED'i yavaşça kısma
        for (uint8_t brightness = 255; brightness >= 0; brightness--) {
            pwm_set_duty_cycle(brightness);
            _delay_ms(10); // Parlaklık değişimi arasında kısa bir gecikme
        }
    }

    return 0;
}
