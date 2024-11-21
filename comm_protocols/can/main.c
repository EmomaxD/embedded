#include "CAN.h"
#include <stdio.h>

int main(void) {
    CAN_Config();     // Initialize CAN
    
    // Simulate sending engine data (e.g., RPM, Temperature)
    uint8_t engineData[] = {0x25, 0x50};  // Example: 0x25 = RPM, 0x50 = Temperature
    CAN_Send(ECU_ENGINE_ID, engineData, 2);
    
    // Simulate sending battery data (e.g., voltage, charge level)
    uint8_t batteryData[] = {0x0A, 0x64};  // Example: 0x0A = Voltage, 0x64 = Charge level
    CAN_Send(ECU_BATTERY_ID, batteryData, 2);
    
    uint32_t receivedId;
    uint8_t receivedData[8];
    uint8_t receivedLength;

    while (1) {
        if (CAN_Receive(&receivedId, receivedData, &receivedLength)) {
            if (receivedId == ECU_ENGINE_ID) {
                // Handle engine data
                printf("Received Engine Data: RPM=0x%02X, Temperature=0x%02X\n", receivedData[0], receivedData[1]);
            } else if (receivedId == ECU_BATTERY_ID) {
                // Handle battery data
                printf("Received Battery Data: Voltage=0x%02X, Charge=0x%02X\n", receivedData[0], receivedData[1]);
            }
        }
    }
}
