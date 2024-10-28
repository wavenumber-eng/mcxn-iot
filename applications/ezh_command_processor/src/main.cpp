#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include "fsl_clock.h"
#include "fsl_device_registers.h"
#include "ezh_app.h"
#include "ext_ram.h"

#define IO_DIR_1_PIN    1

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
    gpio_pin_set_dt(&io_dir_pin, 0);


    LOG_DBG("init psram ....");
    ext_ram.Init();
    LOG_DBG("...done");

    ezh__start_app();

    while (1)
    {
        ezh__execute_command(2);
        k_sleep(K_MSEC(100));

        ezh__execute_command(1);
        k_sleep(K_MSEC(100));
    }

	return 0;
}

