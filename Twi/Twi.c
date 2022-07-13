/*
 * Twi.c
 *
 * Created: 6/24/2022 10:04:41 PM
 *  Author: mahdy
 */ 
#include "Twi.h"
#include "Led.h"

void M_Twi_Init(void)
{
	#if   TWI_MODE    ==   TWI_MASTER
	TWBR = 12; // to Select Fscl = 400Khz;
	#elif TWI_MODE    ==   TWI_SLAVE
	TWAR = ( 0x01 << 1 | 0)       // to set slave addr = 0x01 , and disable general Recog.  
	#endif
	
	SetBit(TWCR, 2); // to enable TWI circuit 
}

void M_Twi_StartCondition(void)
{
	SetBit(TWCR, 5);
	ClrBit(TWCR, 6);
	SetBit(TWCR, 7);  //to clear flag
	while(GetBit(TWCR, 7) == 0);
	while( ( TWSR & 0xF8 ) != 0x08);
}

void M_Twi_SendSlaveAddressWrite(u8 Local_u8_Address)
{
	TWDR = ( Local_u8_Address << 1 );
	ClrBit(TWCR, 5);

	SetBit(TWCR, 7);  //to clear flag
	while(GetBit(TWCR, 7) == 0);
	while( ( TWSR & 0xF8 ) != 0x18);
}

void M_Twi_SendSlaveAddressRead(u8 Local_u8_Address)
{
	TWDR = ( ( Local_u8_Address << 1 ) | 1 );
	ClrBit(TWCR, 5);//

	SetBit(TWCR, 7);  //to clear flag
	while(GetBit(TWCR, 7) == 0);
	while( ( TWSR & 0xF8 ) != 0x40);
}

void M_Twi_SendByte(u8 Local_u8_Data)
{
	TWDR = Local_u8_Data;
	ClrBit(TWCR, 5);
	SetBit(TWCR, 7);  //to clear flag
	while(GetBit(TWCR, 7) == 0);
	while( ( TWSR & 0xF8 ) != 0x28);
}
u8   M_Twi_ReadByte(u8 Local_u8_State)
{
	if(Local_u8_State)
	{
		
		ClrBit(TWCR, 5);
		ClrBit(TWCR, 4);
		SetBit(TWCR, 6);
		SetBit(TWCR, 7);  //to clear flag
		while(GetBit(TWCR, 7) == 0);
		while( ( TWSR & 0xF8 ) != 0x50 );
	}
	else
	{
		TWCR=(1<<2)|(1<<7);	/* Enable TWI and clear interrupt flag */
		while(!(TWCR&(1<<7)));	/* Wait until TWI finish its current job */
	}
	return TWDR;
}

void M_Twi_RepeatedStart(void)
{
	SetBit(TWCR, 5);
	SetBit(TWCR, 7);  //to clear flag	
	while(GetBit(TWCR, 7) == 0);
	while( ( TWSR & 0xF8 ) != 0x10);
}
      
void M_Twi_StopCondition(void)
{
	SetBit(TWCR, 4);
	SetBit(TWCR, 7);  //to clear flag
	//while(GetBit(TWCR, 7) == 0);
	//while( ( TWSR & 0xF8 ) != 0x08);
}

void M_Twi_Ack(void)
{
	SetBit(TWCR, 6);
	SetBit(TWCR, 7);  //to clear flag
	while(GetBit(TWCR, 7) == 0);
	//while( ( TWSR & 0xF8 ) != 0x08);
}
