
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "Car_Interface.h"
#include "ADC_Interface.h"
#include "Converter_Interface.h"
#include "Calculator_Interface.h"
#include "Sensors_Interface.h"
#include "FireSystem_Interface.h"
#include "TempFilter_Interface.h"
#include "Athermal_Interface.h"
#include "EX_Interrupt_Interface.h"
#include "TIMERS_Interface.h"
#include "RGB_Interface.h"
#include "Timer_Services.h"
#include "Ultrasonic_Interface.h"
#include "Stepper.h"
#include "NVM_Services.h"
#include "UART_Interface.h"
#include "UART_Services.h"
#include "SmartHome_Interface.h"
#include "BCM_Services.h"
#include "SPI_Interface.h"
#include "PingPong_Interface.h"
#include "LittleStory.h"
#include "ExEEPROM_Interface.h"


#define F_CPU 8000000
#include <util/delay.h>






int main(void)
{
    
 	DIO_Init();
	LCD_Init();
	SecureDiag_Init();
	
	
 
	while (1)
	{
		
		SecureDiag_Runnable();
		
	}
}