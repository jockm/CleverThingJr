#include "ezI2C.h"

uint8_t	ezI2CAddr;
uint8_t		ezI2CVal;
bool	    ezI2CAvailable;


void ezI2CWrite(uint8_t val) 
{
	ezI2CVal = val;
	twi_master_transfer(ezI2CAddr, &ezI2CVal, 1, TWI_ISSUE_STOP);
}

int16_t ezI2CWriteBulk(uint8_t *val, uint8_t len)
{
	if(!twi_master_transfer(ezI2CAddr, val, len, TWI_ISSUE_STOP)) {
		return -1;
	}

	return 0;
}


int16_t ezI2CRead()
{	
	if(twi_master_transfer(ezI2CAddr | TWI_READ_BIT, &ezI2CVal, 1, TWI_ISSUE_STOP)) {
		ezI2CAvailable = true;
	} else {
		ezI2CAvailable = false;
		return -1;
	}

	return ezI2CVal;
}

int16_t ezI2CReadBulk(uint8_t *val, uint8_t len)
{
	if(twi_master_transfer(ezI2CAddr | TWI_READ_BIT, val, len, TWI_ISSUE_STOP)) {
		ezI2CAvailable = true;
	} else {
		ezI2CAvailable = false;
		return -1;
	}

	return 0;
}
