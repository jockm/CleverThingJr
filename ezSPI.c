#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "common.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "spi_master.h"

#include "ezSPI.h"


volatile bool  ezSPIBusy;


static void ezSpiEventHandler(spi_master_evt_t spi_master_evt);


void ezSPIInit(uint8_t mosiPin, uint8_t misoPin, uint8_t sckPin, uint8_t ssPin)
{
    uint32_t err_code = NRF_SUCCESS;

    ezSPIBusy = false;

    //Configure SPI master.
    spi_master_config_t spi_config = SPI_MASTER_INIT_DEFAULT;

	spi_config.SPI_Pin_SCK = sckPin;
	spi_config.SPI_Pin_MISO = misoPin;
	spi_config.SPI_Pin_MOSI = mosiPin;
	spi_config.SPI_Pin_SS = ssPin;
	spi_config.SPI_Freq = SPI_FREQUENCY_FREQUENCY_M8;

    spi_config.SPI_CONFIG_ORDER = (EZSPI_MSB ? SPI_CONFIG_ORDER_MsbFirst : SPI_CONFIG_ORDER_LsbFirst);

    err_code = spi_master_open(EZSPI_MASTER_INSTANCE, &spi_config);
    APP_ERROR_CHECK(err_code);

    //Register event handler for SPI master.
    spi_master_evt_handler_reg(EZSPI_MASTER_INSTANCE, ezSpiEventHandler);

}


int16_t ezSPIWrite(uint8_t val)
{
	uint8_t txBuf = val;
	uint8_t rxBuf = 0xFF;

	if(ezSPIBulkWrite(&txBuf, 1, &rxBuf, 1) < 0) {
		return -1;
	}

	return rxBuf;
}


int16_t ezSPIBulkWrite(uint8_t *txBuf, uint16_t txLen, uint8_t *rxBuf, uint16_t rxLen) {
	if(ezSPIBusy) {
		return -1;
	}

	ezSPIBusy = true;

	uint32_t err_code = spi_master_send_recv(EZSPI_MASTER_INSTANCE, txBuf, txLen, rxBuf, rxLen);
	if(err_code != NRF_SUCCESS) {
		return -1;
	}

	while(ezSPIBusy) {
		nrf_delay_us(50);
	}

	return 0;
}


void ezSpiEventHandler(spi_master_evt_t spi_master_evt)
{
    switch (spi_master_evt.evt_type)
    {
        case SPI_MASTER_EVT_TRANSFER_COMPLETED:
        	ezSPIBusy = false;
            break;

        default:
            //No implementation needed.
            break;
    }
}
