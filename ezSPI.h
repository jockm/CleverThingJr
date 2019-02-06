#ifndef EZSPI_H
#	define EZSPI_H

#	include <stdint.h>
#	include <stdbool.h>

#	ifndef EZSPI_MASTER_INSTANCE
#		define EZSPI_MASTER_INSTANCE SPI_MASTER_0
#	endif

#	include "spi_master.h"


#	ifndef EZSPI_MSB
#		define EZSPI_MSB true
#	endif

	extern volatile bool  ezSPIBusy;

	void ezSPIInit(uint8_t mosiPin, uint8_t misoPin, uint8_t sckPin, uint8_t ssPin);
	int16_t ezSPIWrite(uint8_t val);
	int16_t ezSPIBulkWrite(uint8_t *txBuf, uint16_t txLen, uint8_t *rxBuf, uint16_t rxLen);
	
	inline bool ezSPIDone() {
		return !ezSPIBusy;
	}
	
#endif
