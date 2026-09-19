#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "USART_interface.h"

#define PASS_LENGTH   4
#define MAX_ATTEMPTS  3

#define GREEN_LED     PB0
#define BUZZER        PB1
#define RED_LED       PB2

const char SECRET_PASS[PASS_LENGTH + 1] = "1234";

void Inde_Init(void) {
    DDRB = (1 << GREEN_LED) | (1 << BUZZER) | (1 << RED_LED);
    PORTB = (1 << RED_LED); 
}

void CLR(void) {
    USART_voidSendString("\033[2J\033[H");
}

int main(void) {
    USART_voidInit();
    Inde_Init();

    uint8_t attempts = 0;
    char input[PASS_LENGTH + 1];

    CLR();
    USART_voidSendString("=====================================\r\n");
    USART_voidSendString("   SECURE SMART DOOR LOCK SYSTEM     \r\n");
    USART_voidSendString("=====================================\r\n");

    while (1) {
        if (attempts >= MAX_ATTEMPTS) {
            USART_voidSendString("\r\n[SYSTEM LOCKED OUT] Too many failed attempts!\r\n");           
            PORTB |= (1 << BUZZER);
            _delay_ms(3000);
            PORTB &= ~(1 << BUZZER);           
            attempts = 0;
            USART_voidSendString("System Reset. Try again.\r\n");
        }

 
        memset(input, 0, sizeof(input));       
        USART_voidSendString("\r\nEnter Password (4 digits): ");
        
        uint8_t I = 0;
        while (I < PASS_LENGTH) {
            uint8_t ch = USART_u8ReceiveChar();


            if (ch == '\n') continue;
            if (ch == '\r') break;

 
            if ((ch == 8 || ch == 127)) {
                if (I > 0) {
                    I--;
                    USART_voidSendString("\b \b");
                }
                continue;
            }

            if (ch >= '0' && ch <= '9') {
                input[I++] = ch;
                USART_voidSendChar('*');
            }
        }
        input[I] = '\0';


        if (strcmp(input, SECRET_PASS) == 0) {
                        USART_voidSendString("\r\n[ACCESS GRANTED] Unlocking Door...\r\n");            
            PORTB &= ~(1 << RED_LED);
            PORTB |= (1 << GREEN_LED);            
            _delay_ms(3000);            
            PORTB &= ~(1 << GREEN_LED);
            PORTB |= (1 << RED_LED);
            
            USART_voidSendString("[DOOR LOCKED] System Closed.\r\n");
            attempts = 0;
        } else {
            attempts++;
            USART_voidSendString("\r\n[ACCESS DENIED] Incorrect Password!\r\n");
            
            PORTB |= (1 << BUZZER);
            _delay_ms(1000);
            PORTB &= ~(1 << BUZZER);
            
            USART_voidSendString("Attempts remaining: ");
            USART_voidSendChar((MAX_ATTEMPTS - attempts) + '0');
            USART_voidSendString("\r\n");
        }
    }

    return 0;
}
