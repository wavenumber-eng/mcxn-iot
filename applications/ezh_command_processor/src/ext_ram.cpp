#include "ext_ram.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/spi.h>

#include "fsl_common.h"
#include "fsl_clock.h"
#include "ezh_app.h"
#include "fsl_spi.h"
LOG_MODULE_REGISTER(psram, LOG_LEVEL_DBG);

// This variables must be global
uint32_t ezh_stack[64];
uint32_t ezh_debug_params[10];
EZHPWM_Para ezh_parameters;
ezh_spi_params_t ezh_spi_params;


static struct gpio_dt_spec io_dir_pin = GPIO_DT_SPEC_GET(DT_ALIAS(io_dir_pin), gpios);



void SPI8__init()
{
	// Direction pin for chip select on MCU-Link Pro
	gpio_pin_configure_dt(&io_dir_pin, GPIO_OUTPUT);
	gpio_pin_set_dt(&io_dir_pin, 1);

	spi_master_config_t SPI_Config = {0};

	CLOCK_AttachClk(kMAIN_CLK_to_HSLSPI);

	// reset FLEXCOMM for SPI
	RESET_PeripheralReset(kHSLSPI_RST_SHIFT_RSTn);

	SPI_MasterGetDefaultConfig(&SPI_Config);

	SPI_Config.sselNum = (spi_ssel_t)0;
	SPI_Config.enableMaster = true;
	SPI_Config.phase = (spi_clock_phase_t)0;
	SPI_Config.polarity = (spi_clock_polarity_t)0;
	SPI_Config.dataWidth = kSPI_Data8Bits;
	SPI_Config.baudRate_Bps = CONFIG__SPI_SCK_FREQ;

	SPI_MasterInit(SPI8, &SPI_Config, CLOCK_GetHsLspiClkFreq());

    
	ezh__start_app();

}

ExtRAM::ExtRAM() : m_first(true)  {} 

void ExtRAM::Init()
 {

	LOG_DBG("init psram ....");

	ezh__start_app();
	SPI8__init();

	LOG_DBG("SPI8 configured");
    LOG_DBG("...done");
	
    init_complete = true;

}

void ExtRAM::RDID()
{
        int err; 

        /*
            1  byte command, 3 bytes dummy address and 2 bytes for the response
        */

        uint8_t tx_buffer[6] ={PSRAM__RDID,0,0,0,0,0};
        uint8_t rx_buffer[6] ={0,0,0,0,0,0};
        
        struct spi_buf tx_spi_buf		= {.buf = (void *)&tx_buffer, .len = sizeof(tx_buffer)};
        struct spi_buf_set tx_spi_buf_set 	= {.buffers = &tx_spi_buf, .count = 1};

        struct spi_buf rx_spi_bufs 		= {.buf = rx_buffer, .len = sizeof(rx_buffer)};
        struct spi_buf_set rx_spi_buf_set	= {.buffers = &rx_spi_bufs, .count = 1};

        err = spi_transceive_dt(&psram_spi_spec, &tx_spi_buf_set, &rx_spi_buf_set);

        if (err < 0) 
        {
            LOG_ERR("spi_transceive_dt() failed in RDID, err: %d", err);
        }
        else
        {
            LOG_INF("RDID bytes : 0x%02x 0x%02x",rx_buffer[4],rx_buffer[5]);
        }

}


int32_t ExtRAM::read(uint32_t address, uint8_t *data, uint32_t len)
{
      

     ezh_fast_read(address,(uint32_t *)data, len);


     while(ezh__command_complete() == false)
     {

     }

     return 0;
      
}


int32_t ExtRAM::fast_read(uint32_t address, uint8_t *data, uint32_t len){
     
     ezh_fast_read(address,(uint32_t *)data, len);


     while(ezh__command_complete() == false)
     {

     }

     return 0;

}

uint8_t  *spi_8bit_fifo_wr = (uint8_t *)(SPI8_BASE + 0xE20);
uint16_t *spi_fifo_ctrl   =  (uint16_t *)(SPI8_BASE + 0xE22);


int32_t ExtRAM::write(uint32_t address, uint8_t *data, uint32_t len)
{
      

    ezh_write(address,(uint32_t *)data, len);

    while(ezh__command_complete() == false)
    {

    }

    return 0;
}



int32_t ExtRAM::ezh_write(uint32_t address, uint32_t *data, uint32_t len)
{
    // To use with the older version
/*
    ezh_spi_wr_params.cmd_and_addr = (((uint8_t)PSRAM__WRITE) << 24) | (address & 0xffffff);
    ezh_spi_wr_params.data_buffer_length = len;
    ezh_spi_wr_params.data_buffer = data;

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
    ezh_parameters.p_buffer = (uint32_t *)(&ezh_spi_wr_params);
*/

//    TO USE WITH THE VERSION SIMILAR TO SPI_RD
        ezh_spi_params.cmd_and_addr =  (((uint8_t)PSRAM__WRITE) << 24) | (address & 0xffffff);      
        ezh_spi_params.wait_cycles =  0; // zero dummy cycles
        
        ezh_spi_params.rx_buffer_length = len; // length in bytes
        ezh_spi_params.rx_buffer_ptr = (uint32_t *)(&data[0]);

        ezh_parameters.coprocessor_stack = (void *)ezh_stack;
        ezh_parameters.p_buffer = (uint32_t *)(&ezh_spi_params);

  
    ezh__execute_command(SPI_WRITE_APP, &ezh_parameters);

    // Probably later we can return the number of words/bytes written
    return 0;
}

int32_t ExtRAM::ezh_fast_read(uint32_t address, uint32_t *rx_buffer, uint32_t len)
{
    ezh_spi_params.cmd_and_addr =  (PSRAM__FAST_READ << 24) | (address & 0xffffff);       
    ezh_spi_params.wait_cycles =  1; // zero dummy cycles
    
    ezh_spi_params.rx_buffer_length = len; // length in bytes
    ezh_spi_params.rx_buffer_ptr = (uint32_t *)(&rx_buffer[0]);

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
    ezh_parameters.p_buffer = (uint32_t *)(&ezh_spi_params);

    SPI8->FIFOCFG = 0x0303;
    ezh__execute_command(SPI_READ_APP, &ezh_parameters);

    return 0;
}


/*
    NOTES:
    1. Run it as the first operation after power up and before any other commands being executed. 

*/
uint8_t rx_buffer[SPI_RD_MAX_LENGTH];

int32_t ExtRAM::ezh_rdid()
{
        
    ezh_spi_params.cmd_and_addr =  (PSRAM__RDID << 24) ;       
    ezh_spi_params.wait_cycles =  0; // zero dummy cycles
    
    ezh_spi_params.rx_buffer_length = 2; // length in bytes
    ezh_spi_params.rx_buffer_ptr = (uint32_t *)(&rx_buffer[0]);

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
    ezh_parameters.p_buffer = (uint32_t *)(&ezh_spi_params);
    ezh__execute_command(SPI_READ_APP, &ezh_parameters);

    return 0;
}