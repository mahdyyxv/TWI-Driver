/*
 * Twi.h
 *
 * Created: 6/24/2022 10:04:51 PM
 *  Author: mahdy
 */ 


#ifndef TWI_H_
#define TWI_H_


/***************************_INCLUDES_***************************/
#include "TwiCfg.h"
#include "StdTypes.h"
#include "BitMath.h"
#include "Reg.h"
/***************************_MACROS_***************************/
#define TWI_MASTER 1
#define TWI_SLAVE 2
/***************************_PROTOTYPES_***************************/

void M_Twi_Init(void);
void M_Twi_StartCondition(void);
void M_Twi_SendSlaveAddressWrite(u8);
void M_Twi_SendSlaveAddressRead(u8);
void M_Twi_SendByte(u8);
u8   M_Twi_ReadByte(u8);
void M_Twi_RepeatedStart(void);
void M_Twi_StopCondition(void);
void M_Twi_Ack(void);
void M_Twi_Nack(void);

#endif /* TWI_H_ */