#define USART2_BASE 0x40004400U
#define USART2_SR   *((volatile uint32_t *)(USART2_BASE + 0x00U))  // Status register
#define USART2_DR   *((volatile uint32_t *)(USART2_BASE + 0x04U))  // Data register
#define USART2_BRR  *((volatile uint32_t *)(USART2_BASE + 0x08U))  // Baud rate register
#define USART2_CR1  *((volatile uint32_t *)(USART2_BASE + 0x0CU))  // Control register 1

#define F_CPU 16000000U  // Define your system clock (in Hz)
#define BAUD_RATE 9600U
#define USART_BRR_VALUE (F_CPU / BAUD_RATE)  // Macro to calculate BRR value

void UART_Config(void) {
    // Set the baud rate based on the macro
    USART2_BRR = USART_BRR_VALUE;

    // Enable USART, set word length to 8-bits, disable parity, and enable TX/RX
    USART2_CR1 = (1 << 13) | (1 << 3) | (1 << 2);  // Enable USART, TX and RX
}

void UART_Send(uint8_t data) {
    while (!(USART2_SR & (1 << 7))) {}  // Wait until TXE (Transmit Data Register Empty) is set
    USART2_DR = data;  // Write data to the data register
}

uint8_t UART_Receive(void) {
    while (!(USART2_SR & (1 << 5))) {}  // Wait until RXNE (Read Data Register Not Empty) is set

    // Optional: Check for errors (framing, overrun, etc.) before reading data
    if (USART2_SR & (1 << 3)) {
        // Handle framing error (optional, as needed)
    }
    if (USART2_SR & (1 << 4)) {
        // Handle overrun error (optional, as needed)
    }

    return (uint8_t)USART2_DR;  // Return received data
}
