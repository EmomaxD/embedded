#define CAN_BASE 0x40006400U

#define CAN_MCR   *((volatile uint32_t *)(CAN_BASE + 0x00U))  // CAN master control register
#define CAN_MSR   *((volatile uint32_t *)(CAN_BASE + 0x04U))  // CAN master status register
#define CAN_TSR   *((volatile uint32_t *)(CAN_BASE + 0x08U))  // CAN transmit status register
#define CAN_RF0R  *((volatile uint32_t *)(CAN_BASE + 0x0CU))  // CAN receive FIFO 0 register
#define CAN_IER   *((volatile uint32_t *)(CAN_BASE + 0x14U))  // CAN interrupt enable register
#define CAN_BTR   *((volatile uint32_t *)(CAN_BASE + 0x1CU))  // CAN bit timing register

#define CAN_TIR0  *((volatile uint32_t *)(CAN_BASE + 0x180U)) // CAN transmit mailbox 0 identifier register
#define CAN_TDT0R *((volatile uint32_t *)(CAN_BASE + 0x184U)) // CAN transmit mailbox 0 data length and time register
#define CAN_TDL0R *((volatile uint32_t *)(CAN_BASE + 0x188U)) // CAN transmit mailbox 0 data low register
#define CAN_TDH0R *((volatile uint32_t *)(CAN_BASE + 0x18CU)) // CAN transmit mailbox 0 data high register

#define CAN_RDL0R *((volatile uint32_t *)(CAN_BASE + 0x1B4U)) // CAN receive FIFO 0 data low register
#define CAN_RDH0R *((volatile uint32_t *)(CAN_BASE + 0x1B8U)) // CAN receive FIFO 0 data high register

void CAN_Config() {
    // Enable the CAN peripheral by configuring MCR and other necessary registers
    CAN_MCR |= (1 << 0);  // Set INRQ bit to enter initialization mode
    while (!(CAN_MSR & (1 << 0))) {}  // Wait until CAN is in initialization mode

    CAN_BTR = (0x4 << 24) | (0x3 << 20) | (0x1 << 16);  // Set prescaler, sync jump width, etc.

    CAN_MCR &= ~(1 << 0);  // Clear INRQ bit to enter normal mode
    while (CAN_MSR & (1 << 0)) {}  // Wait until CAN is in normal mode
}

void CAN_Send(uint32_t id, uint8_t *data, uint8_t length) {
    // Check if the mailbox is empty and ready for new transmission
    while (!(CAN_TSR & (1 << 26))) { }  // Wait until mailbox is ready

    // Configure message ID and data length
    CAN_TIR0 = (id << 21) | (0x0 << 1);  // Set message ID (standard ID) and data frame type
    CAN_TDT0R = length;  // Set data length

    // Copy the data to the CAN data registers
    for (int i = 0; i < length; i++) {
        if (i < 4) {
            CAN_TDL0R |= ((uint32_t)data[i] << (i * 8));  // First 4 bytes to lower data register
        } else {
            CAN_TDH0R |= ((uint32_t)data[i] << ((i - 4) * 8));  // Remaining bytes to higher data register
        }
    }

    CAN_TSR |= (1 << 26);  // Request transmission of the message
}

void CAN_Receive(uint8_t *data) {
    if (CAN_RF0R & 0x03) {  // Check if there is a message in FIFO0
        uint32_t low = CAN_RDL0R;
        uint32_t high = CAN_RDH0R;

        // Copy data from FIFO registers to the data buffer
        data[0] = low & 0xFF;
        data[1] = (low >> 8) & 0xFF;
        data[2] = (low >> 16) & 0xFF;
        data[3] = (low >> 24) & 0xFF;
        data[4] = high & 0xFF;
        data[5] = (high >> 8) & 0xFF;
        data[6] = (high >> 16) & 0xFF;
        data[7] = (high >> 24) & 0xFF;

        // Release FIFO slot after reading
        CAN_RF0R |= 0x03;  // Reset FIFO pointer
    }
}
