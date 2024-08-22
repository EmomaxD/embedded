#include <avr/io.h>
#include <util/delay.h>

// UART initialization function
void uart_init(uint16_t baudrate) {
    // Baud rate setting (e.g., 9600)
    uint16_t ubrr_value = F_CPU / 16 / baudrate - 1;
    UBRR0H = (ubrr_value >> 8); // UBRR high byte
    UBRR0L = ubrr_value;        // UBRR low byte

    // Enable RX and TX
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // 8-bit data, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Function to transmit a character via UART
void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait until the buffer is ready
    UDR0 = data;                      // Send the data
}

// Function to receive a character via UART
char uart_receive(void) {
    while (!(UCSR0A & (1 << RXC0))); // Wait until data is received
    return UDR0;                     // Return the received data
}

// Main program
int main(void) {
    uart_init(9600); // Initialize UART with 9600 baud rate

    // Set PB5 (Arduino D13) as output for LED
    DDRB |= (1 << PB5);

    while (1) {
        char command = uart_receive(); // Read command via UART

        // Check the received command
        if (command == '1') {
            PORTB |= (1 << PB5); // Turn LED on
            uart_transmit('A');  // Send acknowledgment
        } else if (command == '0') {
            PORTB &= ~(1 << PB5); // Turn LED off
            uart_transmit('K');   // Send acknowledgment
        }
    }

    return 0;
}
