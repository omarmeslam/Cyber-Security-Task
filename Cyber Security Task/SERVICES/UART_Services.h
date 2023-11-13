

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

/* 
* synch function
* blocking
*/
void UART_SendString(c8 *str);
void UART_ReceiveString(c8 *str);
void UART_ReceiveStringDocklight(c8 *str);

void UART_SendNumber(u32 num);
u32 UART_ReceiveNumber(void);
u8 UART_u8ReceiveNumber(void);

u8 endianCheck(void);
u32 endianConvert_u32(u32 num);

void UART_SendStringCheckSum(c8*str);
u8 UART_ReceiveStringCheckSum(c8*str);

void UART_Send_StringPeriodic(c8 *str);
void UART_Send_NumberPeriodic(u32 num);



#define  UART_STACK_SIZE  5

typedef enum{
	STACK_EMPTY,
	STACK_FULL,
	STACK_DONE

}StackStatus_t;

StackStatus_t UART_Push(c8 data);
StackStatus_t UART_Pop(c8* pdata);
c8 UART_GetDatainStack(void);

#endif /* UART_SERVICES_H_ */