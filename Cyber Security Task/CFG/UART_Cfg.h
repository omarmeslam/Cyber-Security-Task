 


#ifndef UART_CFG_H_
#define UART_CFG_H_

typedef enum{
	BR_2400=0,
	BR_4800,
	BR_9600,
	BR_14k4,
	BR_19k2,
	BR_28k8,
	BR_38k4,
	BR_57k6,
	BR_76k8,
	BR_115k2,
	BR_230k4,
	BR_250k,
	BR_05M
}BaudRate_type;

/* Baud Rate */
#define BAUD_RATE  BR_9600


typedef enum{
	DATA_5BIT,
	DATA_6BIT,
	DATA_7BIT,
	DATA_8BIT,
	DATA_9BIT
}DataBits_type;

#define  Data_BITS_TYPE  DATA_8BIT


/* Select stop bit */
#define  STOP_BIT_1bit  0
#define  STOP_BIT_2bit  1

#define  STOP_BIT_TYPE  STOP_BIT_1bit



/* parity */
typedef enum{
	NO_Parity,
	Even,
	Odd
	}ParityMode_type;
 
#define  PARITY_MODE  NO_Parity



/* select the type of speed */
#define  NORMAL_SPEED  1
#define  DOUBLE_SPEED  2

#define  SPEED  NORMAL_SPEED

#endif /* UART_CFG_H_ */