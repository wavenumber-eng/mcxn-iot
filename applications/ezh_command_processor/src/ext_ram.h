#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <zephyr/drivers/spi.h>

#ifndef CONFIG_PSRAM_SIZE_BYTES
  #define CONFIG_PSRAM_SIZE_BYTES              0x200000
#endif

typedef enum {
    PSRAM__WRITE     = 0x02,      //datasheet says max 144MHz w/ 8 Clock cycle latency
    PSRAM__READ      = 0x03,       //datasheet says max 33MHz on this command
    PSRAM__FAST_READ = 0x0B,  //datasheet says max 144MHz w/ 8 Clock wait
    PSRAM__RDID      = 0x9f,
} psram_cmd_t;

class ExtRAM {
  public:
    ExtRAM();
    void Init();
    void RDID();
    //Read only works when clock speed <=33MHz

    int32_t read(uint32_t address, uint8_t *data, uint32_t len);
    int32_t fast_read(uint32_t address, uint8_t *data, uint32_t len);
    int32_t write(uint32_t address, uint8_t *data, uint32_t len);    
    
    int32_t ezh_write(uint32_t address, uint32_t *data, uint32_t len);
    int32_t ezh_rdid();

    bool init_complete;
    const uint32_t size = CONFIG_PSRAM_SIZE_BYTES;

  private:
    bool m_first;
    struct spi_dt_spec psram_spi_spec;
};
