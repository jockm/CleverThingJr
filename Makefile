TARGET_CHIP := NRF51822_QFAA_CA
BOARD := BOARD_NRF6310

# application source
C_SOURCE_FILES += main.c
C_SOURCE_FILES += CleverData.c
C_SOURCE_FILES += CleverCommands.c
C_SOURCE_FILES += ble_ancs_c.c
C_SOURCE_FILES += ezI2C.c
C_SOURCE_FILES += ezSPI.c
C_SOURCE_FILES += ds1307.c
C_SOURCE_FILES += ILI9163C.c
C_SOURCE_FILES += mmc.c
C_SOURCE_FILES += pff.c
C_SOURCE_FILES += tinyscript.c
C_SOURCE_FILES += pig.c
C_SOURCE_FILES += defaultScript.c


# nRF51 SDK source
C_SOURCE_FILES += ble_srv_common.c

C_SOURCE_FILES += ble_advdata.c
C_SOURCE_FILES += ble_sensorsim.c
C_SOURCE_FILES += softdevice_handler.c
C_SOURCE_FILES += ble_debug_assert_handler.c
C_SOURCE_FILES += ble_error_log.c
C_SOURCE_FILES += ble_conn_params.c
C_SOURCE_FILES += pstorage.c
C_SOURCE_FILES += crc16.c
C_SOURCE_FILES += app_timer.c
C_SOURCE_FILES += app_scheduler.c
C_SOURCE_FILES += app_button.c
C_SOURCE_FILES += app_gpiote.c
C_SOURCE_FILES += device_manager_peripheral.c
C_SOURCE_FILES += simple_uart.c
C_SOURCE_FILES += spi_master.c
C_SOURCE_FILES += nrf_delay.c

#should we make this hw?
C_SOURCE_FILES += twi_sw_master.c



SDK_PATH = /usr/local/nrf51_sdk_v6_0_0_43681/nrf51822/

OUTPUT_FILENAME := CleverThingJr

DEVICE_VARIANT := xxaa

USE_SOFTDEVICE := S110

CFLAGS := -DDEBUG_NRF_USER -DBLE_STACK_SUPPORT_REQD -DSPI_MASTER_0_ENABLE 

# we do not use heap in this app
ASMFLAGS := -D__HEAP_SIZE=0

# keep every function in separate section. This will allow linker to dump unused functions
CFLAGS += -ffunction-sections

# let linker to dump unused sections
LDFLAGS := -Wl,--gc-sections --specs=nano.specs

INCLUDEPATHS += -I"."
INCLUDEPATHS += -I"./libpff"

INCLUDEPATHS += -I"$(SDK_PATH)Include/s110"
INCLUDEPATHS += -I"$(SDK_PATH)Include/ble"
INCLUDEPATHS += -I"$(SDK_PATH)Include/ble/ble_services"
INCLUDEPATHS += -I"$(SDK_PATH)Include/ble/device_manager"
INCLUDEPATHS += -I"$(SDK_PATH)Include/app_common"
INCLUDEPATHS += -I"$(SDK_PATH)Include/sd_common"
INCLUDEPATHS += -I"$(SDK_PATH)Include/sdk"

C_SOURCE_PATHS += ./libpff

C_SOURCE_PATHS += $(SDK_PATH)Source/ble
C_SOURCE_PATHS +=  $(SDK_PATH)Source/ble/device_manager
C_SOURCE_PATHS += $(SDK_PATH)Source/app_common
C_SOURCE_PATHS += $(SDK_PATH)Source/sd_common


flash-mac:
	$(NRFJPROG) wipe
	$(NRFJPROG) program --softdevice $(SOFTDEVICE) --code $(PROJECT).hex

flash-win:
	nrfjprog -e --programs $(SOFTDEVICE)
	nrfjprog --program $(PROJECT).hex -r
	
include $(SDK_PATH)Source/templates/gcc/Makefile.common
