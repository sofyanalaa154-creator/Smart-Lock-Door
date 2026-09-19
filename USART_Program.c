#include <avr/io.h>
#include "USART_config.h"
#include "USART_interface.h"

/* ===================================================================
 * ATmega328P (Arduino Uno) Compatibility Layer for ATmega32 Register Names
 * =================================================================== */
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    #define UBRRH   UBRR0H
    #define UBRRL   UBRR0L
    #define UCSRB   UCSR0B
    #define RXEN    RXEN0
    #define TXEN    TXEN0
    #define UCSRC   UCSR0C
    #define URSEL   0      
    #define UMSEL   UMSEL00
    #define UCSZ1   UCSZ01
    #define UCSZ0   UCSZ00
    #define UPM1    UPM01
    #define UPM0    UPM00
    #define USBS    USBS0
    #define UCSRA   UCSR0A
    #define UDRE    UDRE0
    #define UDR     UDR0
    #define RXC     RXC0
#endif

void USART_voidInit(void) {

    uint16_t local_u16UBRR = (uint16_t)((F_CPU / (16UL * BAUD_RATE)) - 1);


    UBRRH = (uint8_t)(local_u16UBRR >> 8);
    UBRRL = (uint8_t)local_u16UBRR;


    UCSRB = (1 << RXEN) | (1 << TXEN);


    uint8_t local_u8UCSRC = 0;

#if defined(URSEL) && URSEL != 0
    local_u8UCSRC |= (1 << URSEL);
#endif


#if USART_MODE == SYNC
    local_u8UCSRC |= (1 << UMSEL);
#endif


#if DATA_FRAME == DATA_FRAME_8BITS
    local_u8UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);
#elif DATA_FRAME == DATA_FRAME_7BITS
    local_u8UCSRC |= (1 << UCSZ1);
#elif DATA_FRAME == DATA_FRAME_6BITS
    local_u8UCSRC |= (1 << UCSZ0);
#endif

#if NO_OF_PARITY == EVEN
    local_u8UCSRC |= (1 << UPM1);
#elif NO_OF_PARITY == ODD
    local_u8UCSRC |= (1 << UPM1) | (1 << UPM0);
#endif


#if NO_OF_STOP_BIT == STOP_2BITS
    local_u8UCSRC |= (1 << USBS);
#endif

    UCSRC = local_u8UCSRC;
}

void USART_voidSendChar(uint8_t copy_u8Data) {
    while (!(UCSRA & (1 << UDRE)));
    UDR = copy_u8Data;
}

uint8_t USART_u8ReceiveChar(void) {
    while (!(UCSRA & (1 << RXC)));
    return UDR;
}

void USART_voidSendString(const char *copy_ptrString) {
    while (*copy_ptrString != '\0') {
        USART_voidSendChar((uint8_t)(*copy_ptrString));
        copy_ptrString++;
    }
}
