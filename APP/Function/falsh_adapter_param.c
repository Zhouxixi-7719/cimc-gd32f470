#include "SPI_FLASH.h" 

#define PARAM_SPI_ADDR   0x000000U

/* 擦除参数所在扇区 */
void flash_erase_param_sector(void)
{
    spi_flash_sector_erase(PARAM_SPI_ADDR);
}

/* 整块写入 */
void flash_write_param(const uint8_t *data, uint32_t len)
{
    spi_flash_buffer_write((uint8_t *)data, PARAM_SPI_ADDR, len);
}

/* 整块读出 */
void flash_read_param(uint8_t *data, uint32_t len)
{
    spi_flash_buffer_read(data, PARAM_SPI_ADDR, (uint16_t)len);
}


