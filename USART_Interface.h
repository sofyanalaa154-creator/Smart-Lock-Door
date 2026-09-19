#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

#include <stdint.h>

void USART_voidInit(void);
void USART_voidSendChar(uint8_t copy_u8Data);
uint8_t USART_u8ReceiveChar(void);
void USART_voidSendString(const char *copy_ptrString);

#endif
