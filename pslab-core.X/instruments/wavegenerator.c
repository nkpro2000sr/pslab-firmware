#include <xc.h>
#include "../commands.h"
#include "../bus/uart1.h"
#include "../mcc_generated_files/tmr4.h"
#include "../mcc_generated_files/dma.h"
#include "../mcc_generated_files/oc3.h"
#include "../mcc_generated_files/pin_manager.h"

#define WAVE_TABLE_FULL_LENGTH          512
#define WAVE_TABLE_SHORT_LENGTH         32
#define HIGH_RESOLUTION                 1
#define LOW_RESOLUTION                  0

int __attribute__((section(".sine_table1"))) sine_table_1[] = {
    256, 252, 249, 246, 243, 240, 237, 234, 230, 227, 224, 221, 218, 215, 212,
    209, 206, 203, 200, 196, 193, 190, 187, 184, 181, 178, 175, 172, 169, 166,
    164, 161, 158, 155, 152, 149, 146, 143, 141, 138, 135, 132, 130, 127, 124,
    121, 119, 116, 114, 111, 108, 106, 103, 101, 98, 96, 93, 91, 89, 86, 84, 82,
    79, 77, 75, 73, 70, 68, 66, 64, 62, 60, 58, 56, 54, 52, 50, 48, 47, 45, 43,
    41, 40, 38, 36, 35, 33, 32, 30, 29, 27, 26, 25, 23, 22, 21, 19, 18, 17, 16,
    15, 14, 13, 12, 11, 10, 9, 8, 8, 7, 6, 6, 5, 4, 4, 3, 3, 2, 2, 2, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 6, 6, 7,
    8, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 29,
    30, 32, 33, 35, 36, 38, 40, 41, 43, 45, 47, 48, 50, 52, 54, 56, 58, 60, 62,
    64, 66, 68, 70, 73, 75, 77, 79, 82, 84, 86, 89, 91, 93, 96, 98, 101, 103,
    106, 108, 111, 114, 116, 119, 121, 124, 127, 130, 132, 135, 138, 141, 143,
    146, 149, 152, 155, 158, 161, 164, 166, 169, 172, 175, 178, 181, 184, 187,
    190, 193, 196, 200, 203, 206, 209, 212, 215, 218, 221, 224, 227, 230, 234,
    237, 240, 243, 246, 249, 252, 256, 259, 262, 265, 268, 271, 274, 277, 281,
    284, 287, 290, 293, 296, 299, 302, 305, 308, 311, 315, 318, 321, 324, 327,
    330, 333, 336, 339, 342, 345, 347, 350, 353, 356, 359, 362, 365, 368, 370,
    373, 376, 379, 381, 384, 387, 390, 392, 395, 397, 400, 403, 405, 408, 410,
    413, 415, 418, 420, 422, 425, 427, 429, 432, 434, 436, 438, 441, 443, 445,
    447, 449, 451, 453, 455, 457, 459, 461, 463, 464, 466, 468, 470, 471, 473,
    475, 476, 478, 479, 481, 482, 484, 485, 486, 488, 489, 490, 492, 493, 494,
    495, 496, 497, 498, 499, 500, 501, 502, 503, 503, 504, 505, 505, 506, 507,
    507, 508, 508, 509, 509, 509, 510, 510, 510, 511, 511, 511, 511, 511, 511,
    511, 511, 511, 511, 511, 510, 510, 510, 509, 509, 509, 508, 508, 507, 507,
    506, 505, 505, 504, 503, 503, 502, 501, 500, 499, 498, 497, 496, 495, 494,
    493, 492, 490, 489, 488, 486, 485, 484, 482, 481, 479, 478, 476, 475, 473,
    471, 470, 468, 466, 464, 463, 461, 459, 457, 455, 453, 451, 449, 447, 445,
    443, 441, 438, 436, 434, 432, 429, 427, 425, 422, 420, 418, 415, 413, 410,
    408, 405, 403, 400, 397, 395, 392, 390, 387, 384, 381, 379, 376, 373, 370,
    368, 365, 362, 359, 356, 353, 350, 347, 345, 342, 339, 336, 333, 330, 327,
    324, 321, 318, 315, 311, 308, 305, 302, 299, 296, 293, 290, 287, 284, 281,
    277, 274, 271, 268, 265, 262, 259
};
int __attribute__((section(".sine_table1_short"))) sine_table_1_short[] = {
    32, 26, 20, 14, 9, 5, 2, 1, 0, 1, 2, 5, 9, 14, 20, 26, 32, 38, 44, 50, 55,
    59, 62, 63, 64, 63, 62, 59, 55, 50, 44, 38
};
int __attribute__((section(".sine_table2"))) sine_table_2[] = {
    256, 252, 249, 246, 243, 240, 237, 234, 230, 227, 224, 221, 218, 215, 212,
    209, 206, 203, 200, 196, 193, 190, 187, 184, 181, 178, 175, 172, 169, 166,
    164, 161, 158, 155, 152, 149, 146, 143, 141, 138, 135, 132, 130, 127, 124,
    121, 119, 116, 114, 111, 108, 106, 103, 101, 98, 96, 93, 91, 89, 86, 84, 82,
    79, 77, 75, 73, 70, 68, 66, 64, 62, 60, 58, 56, 54, 52, 50, 48, 47, 45, 43,
    41, 40, 38, 36, 35, 33, 32, 30, 29, 27, 26, 25, 23, 22, 21, 19, 18, 17, 16,
    15, 14, 13, 12, 11, 10, 9, 8, 8, 7, 6, 6, 5, 4, 4, 3, 3, 2, 2, 2, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 6, 6, 7,
    8, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 29,
    30, 32, 33, 35, 36, 38, 40, 41, 43, 45, 47, 48, 50, 52, 54, 56, 58, 60, 62,
    64, 66, 68, 70, 73, 75, 77, 79, 82, 84, 86, 89, 91, 93, 96, 98, 101, 103,
    106, 108, 111, 114, 116, 119, 121, 124, 127, 130, 132, 135, 138, 141, 143,
    146, 149, 152, 155, 158, 161, 164, 166, 169, 172, 175, 178, 181, 184, 187,
    190, 193, 196, 200, 203, 206, 209, 212, 215, 218, 221, 224, 227, 230, 234,
    237, 240, 243, 246, 249, 252, 256, 259, 262, 265, 268, 271, 274, 277, 281,
    284, 287, 290, 293, 296, 299, 302, 305, 308, 311, 315, 318, 321, 324, 327,
    330, 333, 336, 339, 342, 345, 347, 350, 353, 356, 359, 362, 365, 368, 370,
    373, 376, 379, 381, 384, 387, 390, 392, 395, 397, 400, 403, 405, 408, 410,
    413, 415, 418, 420, 422, 425, 427, 429, 432, 434, 436, 438, 441, 443, 445,
    447, 449, 451, 453, 455, 457, 459, 461, 463, 464, 466, 468, 470, 471, 473,
    475, 476, 478, 479, 481, 482, 484, 485, 486, 488, 489, 490, 492, 493, 494,
    495, 496, 497, 498, 499, 500, 501, 502, 503, 503, 504, 505, 505, 506, 507,
    507, 508, 508, 509, 509, 509, 510, 510, 510, 511, 511, 511, 511, 511, 511,
    511, 511, 511, 511, 511, 510, 510, 510, 509, 509, 509, 508, 508, 507, 507,
    506, 505, 505, 504, 503, 503, 502, 501, 500, 499, 498, 497, 496, 495, 494,
    493, 492, 490, 489, 488, 486, 485, 484, 482, 481, 479, 478, 476, 475, 473,
    471, 470, 468, 466, 464, 463, 461, 459, 457, 455, 453, 451, 449, 447, 445,
    443, 441, 438, 436, 434, 432, 429, 427, 425, 422, 420, 418, 415, 413, 410,
    408, 405, 403, 400, 397, 395, 392, 390, 387, 384, 381, 379, 376, 373, 370,
    368, 365, 362, 359, 356, 353, 350, 347, 345, 342, 339, 336, 333, 330, 327,
    324, 321, 318, 315, 311, 308, 305, 302, 299, 296, 293, 290, 287, 284, 281,
    277, 274, 271, 268, 265, 262, 259
};
int __attribute__((section(".sine_table2_short"))) sine_table_2_short[] = {
    32, 26, 20, 14, 9, 5, 2, 1, 0, 1, 2, 5, 9, 14, 20, 26, 32, 38, 44, 50, 55,
    59, 62, 63, 64, 63, 62, 59, 55, 50, 44, 38
};

response_t WAVEGENERATOR_LoadWaveForm1(void) {

    uint8_t i;

    for (i = 0; i < WAVE_TABLE_FULL_LENGTH; i++) {
        sine_table_1[i] = UART1_ReadInt();
    }

    for (i = 0; i < WAVE_TABLE_SHORT_LENGTH; i++) {
        sine_table_1_short[i] = UART1_Read();
    }

    return SUCCESS;
}

response_t WAVEGENERATOR_LoadWaveForm2(void) {

    uint8_t i;

    for (i = 0; i < WAVE_TABLE_FULL_LENGTH; i++) {
        sine_table_2[i] = UART1_ReadInt();
    }

    for (i = 0; i < WAVE_TABLE_SHORT_LENGTH; i++) {
        sine_table_2_short[i] = UART1_Read();
    }

    return SUCCESS;
}

response_t WAVEGENERATOR_SetSine1(void) {

    unsigned char wave_length;
    wave_length = UART1_Read();
    unsigned char resolution;
    resolution = UART1_Read();

    TMR4_Initialize();

    DMA_InterruptDisable(DMA_CHANNEL_2);
    DMA_InitializeChannel2();
    // DMA Reads from RAM address, writes to peripheral address
    DMA2CONbits.DIR = 1;

    if (resolution & HIGH_RESOLUTION) {
        OC3_PrimaryValueSet(WAVE_TABLE_FULL_LENGTH / 2);
        OC3_SecondaryValueSet(WAVE_TABLE_FULL_LENGTH);
        DMA_StartAddressAFullSet(DMA_CHANNEL_2,
                __builtin_dmapage(&sine_table_1),
                __builtin_dmaoffset(&sine_table_1));
        DMA_TransferCountSet(DMA_CHANNEL_2, WAVE_TABLE_FULL_LENGTH - 1);
    } else {
        OC3_PrimaryValueSet(WAVE_TABLE_SHORT_LENGTH / 2);
        OC3_SecondaryValueSet(WAVE_TABLE_SHORT_LENGTH);
        DMA_StartAddressAFullSet(DMA_CHANNEL_2,
                __builtin_dmapage(&sine_table_1_short),
                __builtin_dmaoffset(&sine_table_1_short));
        DMA_TransferCountSet(DMA_CHANNEL_2, WAVE_TABLE_SHORT_LENGTH - 1);
    }

    // Output Compare 3 continues to operate in CPU Idle mode
    OC3CON1bits.OCSIDL = 0;
    // Output Compare Clock Select is Peripheral clock
    OC3CON1bits.OCTSEL = 0b111;
    // Output Compare Fault B input (OCFB) is disabled
    OC3CON1bits.ENFLTB = 0;
    // Output Compare Fault A input (OCFA) is disabled
    OC3CON1bits.ENFLTA = 0;
    // No PWM Fault B condition on OCFB pin has occurred
    OC3CON1bits.OCFLTB = 0;
    // No PWM Fault A condition on OCFA pin has occurred
    OC3CON1bits.OCFLTA = 0;
    // TRIGSTAT is cleared only by software
    OC3CON1bits.TRIGMODE = 0;
    // Output set high when OC3TMR=0 and set low when OC3TMR=OC3R
    OC3CON1bits.OCM = 0b110;

    // Fault mode is maintained until the Fault source is removed and a new PWM period starts
    OC3CON2bits.FLTMD = 0;
    // PWM output is driven low on a Fault
    OC3CON2bits.FLTOUT = 0;
    // OC3 pin I/O state is defined by the FLTOUT bit on a Fault condition
    OC3CON2bits.FLTTRIEN = 0;
    // OC3 output is not inverted
    OC3CON2bits.OCINV = 0;
    // Cascade module operation is disabled
    OC3CON2bits.OC32 = 0;
    // Synchronizes OCx with the source designated by the SYNCSELx bits
    OC3CON2bits.OCTRIG = 0;
    // Timer source has not been triggered and is being held clear
    OC3CON2bits.TRIGSTAT = 0;
    // Output Compare 3 module drives the OC3 pin
    OC3CON2bits.OCTRIS = 0;
    // OC3RS compare event is used for synchronization
    OC3CON2bits.SYNCSEL = 0b11111;

    DMA_PeripheralAddressSet(DMA_CHANNEL_2, (volatile uint16_t) & OC3R);

    // Automatic DMA transfer initiation by DMA request
    DMA2REQbits.FORCE = 0;
    DMA_PeripheralIrqNumberSet(DMA_CHANNEL_2, DMA_PERIPHERAL_IRQ_TMR4);

    DMA_FlagInterruptClear(DMA_CHANNEL_2);
    DMA_InterruptEnable(DMA_CHANNEL_2);

    DMA_ChannelEnable(DMA_CHANNEL_2);

    TMR4_Period16BitSet(wave_length);
    T4CONbits.TCKPS = (resolution >> 1) & 3;

    // Link OC3 pin to output
    RPOR6bits.RP57R = RPN_OC3_PORT;

    TMR4_Start();

    return SUCCESS;
}

response_t WAVEGENERATOR_SetSine2(void) {
    
    unsigned char wave_length;
    wave_length = UART1_Read();
    unsigned char resolution;
    resolution = UART1_Read();

    return SUCCESS;
}