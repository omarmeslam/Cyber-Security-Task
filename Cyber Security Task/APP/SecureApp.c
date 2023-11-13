#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "TIMERS_Interface.h"
#include "LCD_Interface.h"
#include "UART_Services.h"
#include "SecureApp.h"


static u8 ServiceArr[8];
static u8 Service,SubService,flagSecurity,EncryptFlag,flagDone=0,flagRoutine;
static u8 routine[4];
static u8 LedRoutine[4]="AA00";
u8 RandomNum[4]={0};
u8 HashNum[4]={0};
u8 DecryptedNum[4]={0};

static u8 key=35;



void StringToInt(u8 *str)
{
	s32 i;
	u8 num=0;
    
	for(i=0; str[i]; i++)
	{
		
		
			num=str[i]-'0';
			if (i==0)
			{
				Service = (num<<4);
			}
			else if (i==1)
			{
				Service |= (num&0x0F);
			}
			else if (i==2)
			{
				SubService = (num<<4);
			}
			else if (i==3)
			{
				SubService |= (num&0x0F);
			}
			else if (i>=4)
			{
				routine[i-4]=str[i];	
			}
		
		
	}

}






void  SecureDiag_Init(void)
{
	UART_Init();
	TIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_8);

}


void  SecureDiag_Runnable(void)
{
	/*UART Receive*/
	UART_ReceiveString(ServiceArr);
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteString(ServiceArr);
	StringToInt(ServiceArr);
	
	
	if((flagSecurity==0) && (Service!=0x27))
	{
		LCD_GoTo(1,0);
		LCD_WriteString("7F3135");
		for(u8 i=0; ServiceArr[i]; i++)
		{
			ServiceArr[i]=0;
		}
		
	}
	else
	{
		if ((Service==0x31) && (SubService==0x01) && (EncryptFlag==1))
		{
			
			for (u8 i=0; i<4; i++)
			{
				if (routine[i]!=LedRoutine[i])
				{
					flagRoutine=1;
				}
			}
			if (flagRoutine==0)
			{
				for(u8 i=0; i<4; i++)
				{
					if (HashNum[i]!=DecryptedNum[i])
					{
						flagDone=1;
					}
				}
				if (flagDone==0)
				{
					DIO_WritePin(PINC6,HIGH);
					
				}
				
			}
			
		}
		else if ((Service==0x27) && (SubService==0x01))
		{
			/* Generate the random Number from the timer */
			RandomNum[0]=TCNT0*2;
			RandomNum[1]=TCNT0*3;
			RandomNum[2]=TCNT0*4;
			RandomNum[3]=TCNT0*5;
			
			/* Encrypt the random number */
			DecryptedNum[0]=RandomNum[0]^key;
			DecryptedNum[1]=RandomNum[1]^key;
			DecryptedNum[2]=RandomNum[2]^key;
			DecryptedNum[3]=RandomNum[3]^key;
			
			LCD_GoTo(1,0);
			LCD_WriteString("6701");
			LCD_GoTo(1,6);
			LCD_WriteString("0x");
			LCD_WriteHex(RandomNum[0]);
			LCD_WriteHex(RandomNum[1]);
			LCD_WriteHex(RandomNum[2]);
			LCD_WriteHex(RandomNum[3]);
			flagSecurity=1;
			
		}
		else if ((Service==0x27) && (SubService==0x02))
		{
			/* Encrypt Bytes */
			LCD_GoTo(0,6);
			LCD_WriteString("0x");
			HashNum[0]=RandomNum[0]^key;
			HashNum[1]=RandomNum[1]^key;
			HashNum[2]=RandomNum[2]^key;
			HashNum[3]=RandomNum[3]^key;
			LCD_WriteHex(HashNum[0]);
			LCD_WriteHex(HashNum[1]);
			LCD_WriteHex(HashNum[2]);
			LCD_WriteHex(HashNum[3]);
			
			LCD_GoTo(1,0);
			LCD_WriteString("6702");
			LCD_GoTo(1,6);
			LCD_WriteString("0x");
			LCD_WriteHex(DecryptedNum[0]);
			LCD_WriteHex(DecryptedNum[1]);
			LCD_WriteHex(DecryptedNum[2]);
			LCD_WriteHex(DecryptedNum[3]);
			
			EncryptFlag=1;
		}
		
	}
	

	
}