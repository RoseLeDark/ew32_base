#pragma once


#include <ew32_base/ew32_config.h>

#if EW32_PLATFORM == EW32_PLATFORM_ESP

#include <soc/soc_caps.h>

#define EW32_HAL_I2C_HARDWARE_NUM           SOC_I2C_NUM
#define EW32_HAL_I2S_HARDWARE_NUM           SOC_I2S_NUM
#define EW32_HAL_SPI_HARDWARE_NUM           SOC_SPI_PERIPH_NUM
#define EW32_HAL_SPIDMA_CHANNEL_NUM         SOC_SPI_DMA_CHAN_NUM
#define EW32_HAL_UART_HARDWARE_NUM          SOC_UART_NUM

#endif