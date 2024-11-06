#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include "fsl_clock.h"
#include "fsl_device_registers.h"
#include "ezh_app.h"
#include "ext_ram.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_spi.h"
#include "fsl_iocon.h"
#include <fsl_sysctl.h>



static ExtRAM ext_ram; // create RAM instaance

static int monkey_handler(const struct shell *shell,
						  size_t argc,
						  char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "\r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "                 ██████████████████████████            \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "               ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██          \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "               ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██        \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "             ██▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░██        \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "         ██████▒▒░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░██      \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "       ██░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██████  \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "       ██░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██░░░░██\r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "       ██░░░░░░▒▒░░░░░░░░░░██░░░░░░░░██░░░░░░░░██░░░░██\r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "         ████░░▒▒░░░░░░░░░░██░░░░░░░░██░░░░░░░░██████  \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "             ██▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██      \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "     ████      ██▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░██        \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "   ██    ██      ██▒▒░░░░░░░░░░░░░░░░░░░░░░██          \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "   ██  ██      ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██        \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "   ██          ██▒▒▒▒▒▒▒▒░░░░░░░░░░░░▒▒▒▒▒▒▒▒██        \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "     ████    ██▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒██      \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "         ██████▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒██      \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "             ██▒▒▒▒██▒▒░░░░░░░░░░░░░░░░▒▒██▒▒▒▒██      \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "               ██████▒▒▒▒░░░░░░░░░░░░▒▒▒▒██████        \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "                   ██▒▒▒▒▒▒████████▒▒▒▒▒▒██            \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "                   ██░░░░██        ██░░░░██            \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "                   ██████            ██████            \r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "\r\n");
	shell_fprintf(shell, SHELL_VT100_COLOR_CYAN, "                          I'm Super\r\n");

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

	ext_ram.write(0, &test_write_buffer[0], sizeof(test_write_buffer));
	return 0;
}


void SPI8__init();

SHELL_CMD_REGISTER(monkey, NULL, "I'm super.", monkey_handler);
SHELL_CMD_REGISTER(psram_rdid, NULL, "psram_rdid", psram_rdid_handler);
SHELL_CMD_REGISTER(psram_test, NULL, "psram_test", psram_test_handler);

LOG_MODULE_REGISTER(main);

static struct gpio_dt_spec io_dir_pin = GPIO_DT_SPEC_GET(DT_ALIAS(io_dir_pin), gpios);

#define TEST_ARRAY_SIZE 128
uint8_t spi_test_array[TEST_ARRAY_SIZE];
uint8_t test_array[64 * 4];

int main(void)
{
	LOG_DBG("init psram ....");
	//  ext_ram.Init();
	LOG_DBG("...done");
	
	ezh__start_app();
	SPI8__init();
	LOG_DBG("SPI8 configured");

	
	for (uint32_t i = 0; i < TEST_ARRAY_SIZE; i++)
	{
		spi_test_array[i] = i;
	}

	while (1)
	{
		//ext_ram.ezh_fast_read(0, (uint32_t * )&test_array[0], sizeof(test_array));
		ext_ram.ezh_write(0x00112233, (uint32_t *)spi_test_array, TEST_ARRAY_SIZE);
		k_sleep(K_MSEC(15));
	}

	return 0;
}



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
}