#ifndef EZI2C_H
#	define EZI2C_H

#	include <stdint.h>
#	include <stdbool.h>

#	include "twi_master.h"

	extern uint8_t	ezI2CAddr;
	extern uint8_t	ezI2CVal;
	extern bool	    ezI2CAvailable;

#	define ezI2CBegin()					(twi_master_init())
#	define ezI2CSetAddr(a)		(ezI2CAddr = a)
#	define ezI2CEndTransmission(stop)
#	define ezI2CRequestFrom(a,l)	
#	define ezI2CAvailable()				(ezI2CAvailable)

	void ezI2CWrite(uint8_t val);
	int16_t ezI2CWriteBulk(uint8_t *val, uint8_t len);
	
	int16_t ezI2CRead();
	int16_t ezI2CReadBulk(uint8_t *val, uint8_t len);

	inline void ezI2CWriteQ(uint8_t val) 
	{
		ezI2CVal = val;
		twi_master_transfer(ezI2CAddr, &ezI2CVal, 1, TWI_ISSUE_STOP);
	}
#endif
