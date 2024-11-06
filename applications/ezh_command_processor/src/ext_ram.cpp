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


ExtRAM::ExtRAM() : m_first(true)  {} 

void ExtRAM::Init()
 {
    int err; 
    psram_spi_spec = SPI_DT_SPEC_GET(DT_NODELABEL(psram_spi), SPI_WORD_SET(8) | SPI_MODE_GET(0), 0);

    if (!(err = spi_is_ready_dt(&psram_spi_spec))) 
    {
        LOG_ERR("Error: SPI device for the PSRAM is not ready, err: %d", err);
        return;
    }

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
        int err; 

        /*
            1  byte command, 3 bytes dummy address and the data
        */

        uint8_t tx_cmd_buffer[4] ={PSRAM__READ,
                                  (uint8_t)((address>>16)&0xff),
                                  (uint8_t)((address>>8)&0xff),
                                  (uint8_t)((address)&0xff)
                                  };


        uint8_t rx_cmd_dummy_buffer[4] ={0,0,0,0}; // needed to deal with the reponse during command phase
        
        struct spi_buf tx_spi_buf[2]=   {
                                            {.buf = (void *)&tx_cmd_buffer, .len = sizeof(tx_cmd_buffer)},
                                            {.buf = data, .len = len} //use the read buffer as dummy tx
                                        };


        struct spi_buf_set tx_spi_buf_set 	= {.buffers = &tx_spi_buf[0], .count = 2};

        struct spi_buf rx_spi_bufs[2] = {
                                            {.buf = rx_cmd_dummy_buffer, .len = sizeof(rx_cmd_dummy_buffer)},
                                            {.buf = data, .len = len}
                                        };

        struct spi_buf_set rx_spi_buf_set	= {.buffers = &rx_spi_bufs[0], .count = 2};

        err = spi_transceive_dt(&psram_spi_spec, &tx_spi_buf_set, &rx_spi_buf_set);

        if (err < 0) 
        {
            LOG_ERR("spi_transceive_dt() failed in read, err: %d", err);
        }

        return err;

}


int32_t ExtRAM::fast_read(uint32_t address, uint8_t *data, uint32_t len){
        int err; 

        /*
            1  byte command, 3 bytes address, 1 byte wait,  and the data
        */

        uint8_t tx_cmd_buffer[5] ={PSRAM__FAST_READ,
                                  (uint8_t)((address>>16)&0xff),
                                  (uint8_t)((address>>8)&0xff),
                                  (uint8_t)((address)&0xff),
                                  0x00,
                                  };




        uint8_t rx_cmd_dummy_buffer[5] ={0,0,0,0,0}; 
        
        struct spi_buf tx_spi_buf[2]=   {
                                            {.buf = (void *)&tx_cmd_buffer, .len = sizeof(tx_cmd_buffer)},
                                            {.buf = data, .len = len} //use the read buffer as dummy tx
                                        };


        struct spi_buf_set tx_spi_buf_set 	= {.buffers = &tx_spi_buf[0], .count = 2};

        struct spi_buf rx_spi_bufs[2] = {
                                            {.buf = rx_cmd_dummy_buffer, .len = sizeof(rx_cmd_dummy_buffer)},
                                            {.buf = data, .len = len}
                                        };

        struct spi_buf_set rx_spi_buf_set	= {.buffers = &rx_spi_bufs[0], .count = 2};

        err = spi_transceive_dt(&psram_spi_spec, &tx_spi_buf_set, &rx_spi_buf_set);

        if (err < 0) 
        {
            LOG_ERR("spi_transceive_dt() failed in read, err: %d", err);
        }

        return err;

}

uint8_t  *spi_8bit_fifo_wr = (uint8_t *)(SPI8_BASE + 0xE20);
uint16_t *spi_fifo_ctrl   =  (uint16_t *)(SPI8_BASE + 0xE22);


int32_t ExtRAM::write(uint32_t address, uint8_t *data, uint32_t len)
{
        int err = 0; 

        /*
            1  byte command, 3 bytes dummy address and the data

            ToDo:  THe zephyr SPI buffer chaining approach for has significant delay between 
            transactions.   

        */
/*
        SPI8->FIFOCFG |= 3<<16; //*Flush the Tx & Rx buffers

        SPI8->FIFOCFG |= 1; // Enable the fifo

        *spi_fifo_ctrl = (0x1) |
                         (1<<(SPI_FIFOWR_RXIGNORE_SHIFT-16)) | 
                         ((7)<<(SPI_FIFOWR_LEN_SHIFT-16));
     
    
        *spi_8bit_fifo_wr = PSRAM__WRITE;      while((SPI8->FIFOSTAT & (1<<5)) == 0){}
        *spi_8bit_fifo_wr =  (uint8_t)((address>>16)&0xff);      while((SPI8->FIFOSTAT & (1<<5)) == 0){}
        *spi_8bit_fifo_wr  =  (uint8_t)((address>>8)&0xff);      while((SPI8->FIFOSTAT & (1<<5)) == 0){}
        *spi_8bit_fifo_wr  =  (uint8_t)((address)&0xff);      while((SPI8->FIFOSTAT & (1<<5)) == 0){}
*/

/*
        for(int i=0;i<len-1;i++)
        {

               while((SPI8->FIFOSTAT & (1<<5)) == 0){}
            *spi_8bit_fifo_wr = data[i];

        }


               while((SPI8->FIFOSTAT & (1<<5)) == 0){}
      *spi_fifo_ctrl =  (0x1) | (1<<(SPI_FIFOWR_EOT_SHIFT-16));
      *spi_8bit_fifo_wr = data[(len-1)];
      */

     
     
        uint8_t tx_cmd_buffer[4] ={PSRAM__WRITE,
                                  (uint8_t)((address>>16)&0xff),
                                  (uint8_t)((address>>8)&0xff),
                                  (uint8_t)((address)&0xff)
        };


    
    
        struct spi_buf tx_spi_buf[2]=   {
                                            {.buf = (void *)&tx_cmd_buffer, .len = sizeof(tx_cmd_buffer)},
                                            {.buf = data, .len = len} 
                                        };
        

        struct spi_buf_set tx_spi_buf_set 	= {.buffers = &tx_spi_buf[0], .count = 2};
     

     uint8_t rx_cmd_dummy_buffer[4] ={0,0,0,0}; // needed to deal with the reponse during command phase.
        

        //todo - improve this...  switch to te patch spi driver that can do a tx blast

        struct spi_buf rx_spi_bufs[2] = {
                                            {.buf = rx_cmd_dummy_buffer, .len = sizeof(rx_cmd_dummy_buffer)},
                                            {.buf = NULL, .len = 0}//use the write buffer as dummy rx
                                        };

        struct spi_buf_set rx_spi_buf_set	= {.buffers = &rx_spi_bufs[0], .count = 2};

   

        err = spi_transceive_dt(&psram_spi_spec, &tx_spi_buf_set, &rx_spi_buf_set);

        if (err < 0) 
        {
            LOG_ERR("spi_transceive_dt() failed in write, err: %d", err);
        }

        return err;

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