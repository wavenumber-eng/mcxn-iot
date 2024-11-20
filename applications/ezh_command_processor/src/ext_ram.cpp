#include "ext_ram.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/spi.h>

#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_iocon.h"

#include "ezh_app.h"
#include "fsl_spi.h"

LOG_MODULE_REGISTER(psram, LOG_LEVEL_DBG);

// This variables must be global
uint32_t ezh_stack[64];
uint32_t ezh_debug_params[10];
EZHPWM_Para ezh_parameters;
ezh_spi_params_t ezh_spi_params;


#define IOCON_PIO_DIGITAL_EN 0x0100u  /*!<@brief Enables digital function */
#define IOCON_PIO_FUNC1 0x01u         /*!<@brief Selects pin function 1 */
#define IOCON_PIO_FUNC5 0x05u         /*!<@brief Selects pin function 5 */
#define IOCON_PIO_FUNC6 0x06u         /*!<@brief Selects pin function 6 */
#define IOCON_PIO_FUNC9 0x09u         /*!<@brief Selects pin function 9 */
#define IOCON_PIO_INV_DI 0x00u        /*!<@brief Input function is not inverted */
#define IOCON_PIO_MODE_INACT 0x00u    /*!<@brief No addition pin function */
#define IOCON_PIO_MODE_PULLUP 0x20u   /*!<@brief Selects pull-up function */
#define IOCON_PIO_OPENDRAIN_DI 0x00u  /*!<@brief Open drain is disabled */
#define IOCON_PIO_SLEW_STANDARD 0x00u /*!<@brief Standard mode, output slew rate control is enabled */


const uint32_t port1_pin1_config = (/* Pin is configured as HS_SPI_SSEL1 */
                                        IOCON_PIO_FUNC5 |
                                        /* Selects pull-up function */
                                        IOCON_PIO_MODE_PULLUP |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);


void SPI8__init()
{
    IOCON_PinMuxSet(IOCON, 1U, 1U, port1_pin1_config);

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
}

ExtRAM::ExtRAM() : m_first(true)  {} 

void ExtRAM::Init()
 {
	ezh__build_apps();
	SPI8__init();
    init_complete = true;
}

uint16_t ExtRAM::rdid()
{
    /*
        Note... The current Tx/Rx pipelie is deep.  Need a minimum of 5 bytes total.
    */

    uint64_t RDID_Code;
    
    ezh_spi_params.cmd_and_addr =  (PSRAM__RDID << 24);  
    ezh_spi_params.wait_cycles =  0; // zero dummy cycles
    
    ezh_spi_params.buffer_length = sizeof(RDID_Code); // length in bytes
    ezh_spi_params.buffer_ptr = (uint32_t *)(&RDID_Code);

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
    ezh_parameters.p_buffer = (uint32_t *)(&ezh_spi_params);

    ezh__execute_command(SPI_READ_APP, &ezh_parameters);

    while(ezh__command_complete() == false)
    {

    }

     return RDID_Code;
}




int32_t ExtRAM::fast_read(uint32_t address, uint8_t *data, uint32_t len)
{
     
    ezh_spi_params.cmd_and_addr =  (PSRAM__FAST_READ << 24) | (address & 0xffffff);       
    ezh_spi_params.wait_cycles =  1; // zero dummy cycles
    
    ezh_spi_params.buffer_length = len; // length in bytes
    ezh_spi_params.buffer_ptr = (uint32_t *)(data);

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
    ezh_parameters.p_buffer = (uint32_t *)(&ezh_spi_params);

    ezh__execute_command(SPI_READ_APP, &ezh_parameters);
    
    while(ezh__command_complete() == false)
    {

    }

     return 0;

}

int32_t ExtRAM::read(uint32_t address, uint8_t *data, uint32_t len)
{


    fast_read(address,data, len);

     return 0;
      
}

int32_t ExtRAM::write(uint32_t address, uint8_t *data, uint32_t len)
{
    
    ezh_spi_params.cmd_and_addr =  (((uint8_t)PSRAM__WRITE) << 24) | (address & 0xffffff);      
    ezh_spi_params.wait_cycles =  0; // zero dummy cycles
        
    ezh_spi_params.buffer_length = len; // length in bytes
    ezh_spi_params.buffer_ptr = (uint32_t *)(data);

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
    ezh_parameters.p_buffer = (uint32_t *)(&ezh_spi_params);
 
    ezh__execute_command(SPI_WRITE_APP, &ezh_parameters);

    while(ezh__command_complete() == false)
    {

    }

    return 0;
}





