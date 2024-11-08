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

static int gibbon_handler(const struct shell *shell,
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
	shell_fprintf(shell, SHELL_VT100_COLOR_CYAN, "                          i am gibbon\r\n");

	return 0;
}

static int psram_rdid_handler(const struct shell *shell,
							  size_t argc,
							  char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	uint16_t RDID_Code = ext_ram.RDID();

	shell_print(shell,"RDID: 0x%04x\r",RDID_Code);

	return 0;
}

#define TEST_BUFFER_SIZE        128
#define PSRAM_SIZE              0x200000

uint8_t test_write_buffer[TEST_BUFFER_SIZE];
uint8_t test_read_buffer[TEST_BUFFER_SIZE];

static int psram_test_handler(const struct shell *shell,
							  size_t argc,
							  char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	bool failed = false;

    for(uint32_t base_addr = 0; base_addr<PSRAM_SIZE; base_addr+=TEST_BUFFER_SIZE)
    {
    
        for(int i=0; i<TEST_BUFFER_SIZE; i++)
        {
            test_write_buffer[i] = rand();
        }

        shell_print(shell,"Testing %d bytes at psram base address 0x%08x   \r",TEST_BUFFER_SIZE,base_addr);

        ext_ram.write(base_addr,&test_write_buffer[0],TEST_BUFFER_SIZE);

        //ext_ram.read(0,&test_read_buffer[0],TEST_BUFFER_SIZE);
        ext_ram.fast_read(base_addr,&test_read_buffer[0],TEST_BUFFER_SIZE);

        if(memcmp(test_write_buffer , test_read_buffer , TEST_BUFFER_SIZE)!=0)
        {

            shell_print(shell,"Memory test fail at base address 0x%08x",base_addr);

            shell_print(shell,"Data write buffer : ");

           shell_hexdump(shell,test_write_buffer,TEST_BUFFER_SIZE);

            shell_print(shell,"Data read buffer : ");

            shell_hexdump(shell,test_read_buffer,TEST_BUFFER_SIZE);
            
            failed = true;

            return 0;
        }


    }


    if(failed == false)
    {
        shell_print(shell,"\r\n Memory test passed");
    }
    
	return 0;
}


#define TEST_ARRAY_SIZE 128
uint8_t spi_test_array[TEST_ARRAY_SIZE];
uint8_t test_array[64 * 4];

SHELL_CMD_REGISTER(gibbon, NULL, "i am gibbon", gibbon_handler);
SHELL_CMD_REGISTER(psram_rdid, NULL, "psram_rdid", psram_rdid_handler);
SHELL_CMD_REGISTER(psram_test, NULL, "psram_test", psram_test_handler);

LOG_MODULE_REGISTER(main);



int main(void)
{

	 ext_ram.Init();
	
	while (1)
	{
		//	ext_ram.read(0xFF, &spi_test_array[0], TEST_ARRAY_SIZE);
		//	ext_ram.write(0xFF, &spi_test_array[0], TEST_ARRAY_SIZE);
		

		k_sleep(K_MSEC(100));
	}

	return 0;
}

