
#include "StdTypes.h"
#include "UART_Interface.h"
#include "UART_Services.h"


void UART_SendString(c8 *str)
{
	u8 i;
	
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
}

void UART_ReceiveString(c8 *str)
{
	u8 i;
	
	str[0]=UART_Receive();
	for (i=0;str[i]!=0x0D;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
}

void UART_ReceiveStringDocklight(c8 *str)
{
	u8 i, prev,flag=1;
	
	str[0]=UART_Receive();
	prev=str[0];
	for (i=0;flag;)
	{
		i++;
		str[i]=UART_Receive();
		if (str[i]==0x0A && prev==0x0D)
		{
			flag=0;
		}
		prev=str[i];
	}
	str[i]=0;
	str[i-1]=0;
}

void UART_SendNumber(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
}

u8 UART_u8ReceiveNumber(void)
{
	u8 num=UART_Receive();
	return num;
}
u32 UART_ReceiveNumber(void)
{
	u32 num;
	
	u8 b0=UART_Receive();
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	num = (u32)b0 | ((u32)b1<<8) | ((u32)b2<<16) | ((u32)b3<<24);
	
	return num;
}

void UART_SendNumber2(u32 num)
{
	u8* p=(u8*)&num;
	
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
}

u32 UART_ReceiveNumber2(void)
{
	u32 num;
	u8* p=(u8*)&num;
	
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	
	return num;
}


u8 endianCheck(void)
{
	u32 num=1;
	u8*p=(u8*)&num;
	
	if (*p==1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

u32 endianConvert_u32(u32 num)
{
	u32 newnum;
	
	newnum=(num<<24) | (num>>24) | ((num<<8)&0x00FF0000) | ((num>>8)&0x00000FF00);
	
	return newnum;
}


void UART_SendStringCheckSum(c8*str)
{
	u8 l;
	u16 sum=0;
	
	for (l=0;str[l];l++)
	{
		sum+=str[l];
	}
	
	UART_Send(l);
	UART_SendString(str);
	
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
}

u8 UART_ReceiveStringCheckSum(c8*str){	u8 i,l,b0,b1;	u16 sum_calc=0, sum_rec=0;		l=UART_Receive();		for (i=0;i<l;i++)	{		str[i]=UART_Receive();		sum_calc+=str[i];	}		b0=UART_Receive();	b1=UART_Receive();	sum_rec=b0 | (b1<<8);		if (sum_calc == sum_rec)
	{
		return 1;
	}	else	{		return 0;	}}


/********************************** UART STACK ****************************/


static c8 UARTStackArr[UART_STACK_SIZE];
u8 sp,idxOfData;

c8 UART_GetDatainStack(void)
{
	u8 data;
	
	data=UARTStackArr[idxOfData++];
	
	return data;
}
StackStatus_t UART_Push(c8 data)
{
	StackStatus_t status = STACK_DONE;

	if(sp < UART_STACK_SIZE)
	{
		UARTStackArr[sp++] = data;
	}
	else
	{
		status = STACK_FULL;
	}
	return status;
}

StackStatus_t UART_Pop(c8* pdata)
{
	StackStatus_t status = STACK_DONE;;

	if(sp>0)
	{
		sp--;
		idxOfData--;
		*pdata = UARTStackArr[sp];
	}
	else
	{
		status = STACK_EMPTY;
	}
	return status;
}


/**********************************************************************/


/*
void UART_Send_StringPeriodic(c8 *string)
{
	static u8 i;
	
	if ((READ_BIT(UCSRA,UDRE)) && string[i])
	{
		UDR=string[i];
		i++;
	}
	else
	{
		i=0;
	}
}


void UART_Send_NumberPeriodic(u32 num)
{
	static u8 i=0;

	if ((READ_BIT(UCSRA,UDRE)) && i<=32)
	{
		UDR=(num>>i) & 0xFF;
		i+=8;
	}

}*/