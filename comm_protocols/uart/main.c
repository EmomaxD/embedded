#include "UART.h"
#include <stdio.h>

int main(void) {
    UART_Config();  // Initialize UART

    // Send a welcome message
    char welcomeMessage[] = "UART Communication Started!\r\n";
    for (int i = 0; welcomeMessage[i] != '\0'; i++) {
        UART_Send(welcomeMessage[i]);
    }

    uint8_t receivedData;

    while (1) {
        if (UART_DataAvailable()) {
            receivedData = UART_Receive();  // Receive data byte
            UART_Send(receivedData);        // Echo the received data back
        }
    }
}
