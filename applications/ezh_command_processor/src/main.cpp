#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include "fsl_clock.h"
#include "fsl_device_registers.h"
#include "ezh_app.h"
#include "ext_ram.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_spi.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_spi.h"
#include "fsl_iocon.h"
#define IO_DIR_1_PIN    1


 /* @brief Enables digital function */
#define IOCON_PIO_DIGITAL_EN 0x0100u
/*!
 * @brief Selects pin function 1 */
#define IOCON_PIO_FUNC1 0x01u
/*!
 * @brief Input function is not inverted */
#define IOCON_PIO_INV_DI 0x00u
/*!
 * @brief No addition pin function */
#define IOCON_PIO_MODE_INACT 0x00u
/*!
 * @brief Open drain is disabled */
#define IOCON_PIO_OPENDRAIN_DI 0x00u
/*!
 * @brief Standard mode, output slew rate control is enabled */
#define IOCON_PIO_SLEW_STANDARD 0x00u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO0_20_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO0_26_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_1_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO1_1_FUNC_ALT0 0x00u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_2_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 6. */
#define PIO1_2_FUNC_ALT6 0x06u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_3_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 6. */
#define PIO1_3_FUNC_ALT6 0x06u

/*! @name PIO0_29 (coord H8), PIO0_29
  @{ */
#define BOARD_INITPINS_PIO0_29_PORT 0U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_PIO0_29_PIN 29U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_PIO0_29_PIN_MASK (1U << 29U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PIO0_30 (coord E5), PIO0_30
  @{ */
#define BOARD_INITPINS_PIO0_30_PORT 0U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_PIO0_30_PIN 30U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_PIO0_30_PIN_MASK (1U << 30U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PIO0_26 (coord H12), SPI_MOSI
  @{ */
#define BOARD_INITPINS_SPI_MOSI_PORT 0U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SPI_MOSI_PIN 26U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_SPI_MOSI_PIN_MASK (1U << 26U)      /*!<@brief PORT pin mask */
                                                          /* @} */

/*! @name PIO1_2 (coord G12), SPI_SCK
  @{ */
#define BOARD_INITPINS_SPI_SCLK_PORT 1U                  /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SPI_SCLK_PIN 2U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_SPI_SCLK_PIN_MASK (1U << 2U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PIO1_3 (coord G13), LCD_CMD_DATA
  @{ */
#define BOARD_INITPINS_LCD_CMD_DATA_PORT 1U                  /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_LCD_CMD_DATA_PIN 3U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_LCD_CMD_DATA_PIN_MASK (1U << 3U)      /*!<@brief PORT pin mask */
                                                             /* @} */

/*! @name PIO1_1 (coord G11), SPI_SSEL
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SPI_SSEL_GPIO GPIO                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_SPI_SSEL_GPIO_PIN_MASK (1U << 1U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_SPI_SSEL_PORT 1U                  /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SPI_SSEL_PIN 1U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_SPI_SSEL_PIN_MASK (1U << 1U)      /*!<@brief PORT pin mask */
                                                         /* @} */


static ExtRAM ext_ram; //create RAM instaance


static int monkey_handler(const struct shell *shell, 
                      size_t argc,
                      char **argv)
{
   ARG_UNUSED(argc);
   ARG_UNUSED(argv);

   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"\r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"                 ██████████████████████████            \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"               ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██          \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"               ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██        \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"             ██▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░██        \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"         ██████▒▒░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░██      \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"       ██░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██████  \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"       ██░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██░░░░██\r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"       ██░░░░░░▒▒░░░░░░░░░░██░░░░░░░░██░░░░░░░░██░░░░██\r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"         ████░░▒▒░░░░░░░░░░██░░░░░░░░██░░░░░░░░██████  \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"             ██▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██      \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"     ████      ██▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░██        \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"   ██    ██      ██▒▒░░░░░░░░░░░░░░░░░░░░░░██          \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"   ██  ██      ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██        \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"   ██          ██▒▒▒▒▒▒▒▒░░░░░░░░░░░░▒▒▒▒▒▒▒▒██        \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"     ████    ██▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒██      \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"         ██████▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒██      \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"             ██▒▒▒▒██▒▒░░░░░░░░░░░░░░░░▒▒██▒▒▒▒██      \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"               ██████▒▒▒▒░░░░░░░░░░░░▒▒▒▒██████        \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"                   ██▒▒▒▒▒▒████████▒▒▒▒▒▒██            \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"                   ██░░░░██        ██░░░░██            \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"                   ██████            ██████            \r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_YELLOW,"\r\n");
   shell_fprintf(shell,SHELL_VT100_COLOR_CYAN,"                          I'm Super\r\n");
      
   return 0;
}

static int psram_rdid_handler(const struct shell *shell, 
                      size_t argc,
                      char **argv)
{
   ARG_UNUSED(argc);
   ARG_UNUSED(argv);

   ext_ram.RDID();

   return 0;
}

static int psram_test_handler(const struct shell *shell, 
                      size_t argc,
                      char **argv)
{
   ARG_UNUSED(argc);
   ARG_UNUSED(argv);

   uint8_t test_write_buffer[32];

   ext_ram.write(0,&test_write_buffer[0], sizeof(test_write_buffer));
   return 0;
}

SHELL_CMD_REGISTER(monkey, NULL, "I'm super.", monkey_handler);
SHELL_CMD_REGISTER(psram_rdid, NULL, "psram_rdid", psram_rdid_handler);
SHELL_CMD_REGISTER(psram_test, NULL, "psram_test", psram_test_handler);

LOG_MODULE_REGISTER(main);

static struct gpio_dt_spec io_dir_pin = GPIO_DT_SPEC_GET(DT_ALIAS(io_dir_pin), gpios);

int main(void)
{

    gpio_pin_configure_dt(&io_dir_pin, GPIO_OUTPUT);
    gpio_pin_set_dt(&io_dir_pin, 1);

    LOG_DBG("init psram ....");
   // ext_ram.Init();
    LOG_DBG("...done");

    ezh__start_app();

  //  ext_ram.RDID();


   spi_master_config_t SPI_Config = {0};


    	CLOCK_AttachClk(kMAIN_CLK_to_HSLSPI);

    // reset FLEXCOMM for SPI 
    	RESET_PeripheralReset(kHSLSPI_RST_SHIFT_RSTn);

    	SPI_MasterGetDefaultConfig(&SPI_Config);

    	SPI_Config.sselNum =(spi_ssel_t) 0;
    	SPI_Config.enableMaster = true;
    	SPI_Config.phase =(spi_clock_phase_t) 0;
    	SPI_Config.polarity = (spi_clock_polarity_t) 0;
    	SPI_Config.dataWidth = kSPI_Data8Bits;
    	SPI_Config.baudRate_Bps = 10000000;

    	SPI_MasterInit(SPI8,&SPI_Config, CLOCK_GetHsLspiClkFreq());

    //	SPI8->FIFOCFG |= 3<<16; //*Flush the Tx & Rx buffers*

    //	SPI8->FIFOCFG |= 1; // Enable the fifo

    while (1)
    {   
//        ezh__execute_command(2);
//        k_sleep(K_MSEC(100));
//
//        ezh__execute_command(1);


//(SPI8->FIFOWR) = 0xAA | SPI_FIFOWR_LEN(8-1) | (1<<SPI_FIFOWR_RXIGNORE_SHIFT) ;
//(SPI8->FIFOWR) = 0xAA | SPI_FIFOWR_LEN(8-1) | (1<<SPI_FIFOWR_RXIGNORE_SHIFT) ;
//(SPI8->FIFOWR) = 0xAA | SPI_FIFOWR_LEN(8-1) | (1<<SPI_FIFOWR_RXIGNORE_SHIFT) ;
//(SPI8->FIFOWR) = 0xAA | SPI_FIFOWR_LEN(8-1) | (1<<SPI_FIFOWR_RXIGNORE_SHIFT) ;
    
     ext_ram.ezh_write(0x112233, nullptr, 0);
        k_sleep(K_MSEC(250));
    }

	return 0;
}

