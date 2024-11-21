#include <windows.h>
#include <stdio.h>

void send_data(HANDLE hSerial, const char* data) {
    DWORD bytes_written;
    BOOL result = WriteFile(hSerial, data, strlen(data), &bytes_written, NULL);
    if (!result) {
        printf("Error sending data: %d\n", GetLastError());
    } else {
        printf("Bytes sent: %lu\n", bytes_written);
    }
}

int main() {
    // Configure serial port
    HANDLE hSerial = CreateFile(
        "COM4",                // Port name
        GENERIC_WRITE,         // Write access
        0,                     // No sharing
        NULL,                  // Default security attributes
        OPEN_EXISTING,         // Open existing port
        0,                     // Default attributes
        NULL);                 // No template

    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error opening port: %d\n", GetLastError());
        return 1;
    }

    // Set serial port parameters
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error getting port state: %d\n", GetLastError());
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;      // Baud rate
    dcbSerialParams.ByteSize = 8;             // Data bits
    dcbSerialParams.StopBits = ONESTOPBIT;    // Stop bits
    dcbSerialParams.Parity = NOPARITY;         // Parity

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Error setting port state: %d\n", GetLastError());
        CloseHandle(hSerial);
        return 1;
    }

    // Send data
    while (1) {
        send_data(hSerial, "1");  // Turn on LED
        Sleep(2000);              // Wait 2 seconds
        send_data(hSerial, "0");  // Turn off LED
        Sleep(2000);
    }

    // Close port
    CloseHandle(hSerial);

    return 0;
}
