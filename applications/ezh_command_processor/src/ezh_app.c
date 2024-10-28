
#include <zephyr/irq.h>
#include <zephyr/logging/log.h>

#include "fsl_common.h"
#include "fsl_clock.h"
#include "ezh_init.h"
#include <ezh_app.h>
#include "bunny_build.h"
#include "fsl_device_registers.h"

uint32_t ezh_stack[16];
EZHPWM_Para ezh_parameters;
EZH_CMD_PROCESSOR_PARAMS cmd_processor_params;
uint32_t ezh_debug_params[5];

uint32_t test_val = 0;

// EZH APPLICATIONS
__attribute((section("SRAM1"))) uint32_t my_ezh_program1[128]; // Todo relocate into fast SRAMX - no contention 
__attribute((section("SRAM1"))) uint32_t my_ezh_program2[128]; // Todo relocate into fast SRAMX - no contention 
void ezh_app__toggle1(void);
void ezh_app__toggle2(void);
void ezh_app__command_processor(void);

// Magic / undocumented IRQ vector for the EZH to ARM

#define EZH_TEST_GPIO_1 24
#define EZH_TEST_GPIO_2 25

#if defined(CONFIG_BOARD_LPCXPRESSO55S69_LPC55S69_CPU0)

#define EZH__Reserved46_IRQn (IRQn_Type)30
ISR_DIRECT_DECLARE(Reserved46_IRQHandler__EZH)
{
    EZH_SetExternalFlag(1);

    test_val = LPC_EZH_ARCH_B0->EZHB_EZH2ARM;
    EZH_stop();

    EZH_SetExternalFlag(0);

    return 0;
}

#elif defined (CONFIG_BOARD_FRDM_MCXN947_MCXN947_CPU0)
ISR_DIRECT_DECLARE(EZH_INTERRUPT_ISR)
{
    EZH_SetExternalFlag(1);

    test_val = LPC_EZH_ARCH_B0->EZHB_EZH2ARM;
    EZH_stop();

    EZH_SetExternalFlag(0);

    return 0;
}
#endif

uint32_t params [1];

LOG_MODULE_REGISTER(EZH_MGR);

void ezh__start_app()
{

#if defined(CONFIG_BOARD_LPCXPRESSO55S69_LPC55S69_CPU0)
    MRT0->CHANNEL[0].STAT = 0;

    EZH_SetExternalFlag(0);

    irq_disable(EZH__Reserved46_IRQn); // EZH irq NUMBER 30

    IRQ_DIRECT_CONNECT(EZH__Reserved46_IRQn, 0, Reserved46_IRQHandler__EZH, 0) // IRQ_ZERO_LATENCY doesn't build yet

    // Magic mux setting to use port 0.3 directly in EZH
    IOCON->PIO[0][3] = PINFUNC_EZH | 2 << 4 | 1 << 8;

    // P0_24
    // P0_25
    IOCON->PIO[0][24] = PINFUNC_EZH | 2 << 4 | 1 << 8;
    IOCON->PIO[0][25] = PINFUNC_EZH | 2 << 4 | 1 << 8;

    CLOCK_EnableClock(kCLOCK_Ezhb); // enable EZH clock

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
    ezh_parameters.p_buffer = (uint32_t *)ezh_debug_params;

    EZH_Init(&ezh_parameters); // EZH initialisation

    LOG_INF("\n\nBUILDING PROGRAM 1");
    bunny_build(&my_ezh_program1[0],
                sizeof(my_ezh_program1),
                ezh_app__toggle1);

    LOG_INF("\n\nBUILDING PROGRAM 2");
    bunny_build(&my_ezh_program2[0],
                sizeof(my_ezh_program2),
                ezh_app__toggle2);


    irq_enable(EZH__Reserved46_IRQn); // EZH irq number 30


#elif defined (CONFIG_BOARD_FRDM_MCXN947_MCXN947_CPU0)
    CLOCK_EnableClock(kCLOCK_Gpio1);
    CLOCK_EnableClock(kCLOCK_Port1);

    irq_disable(SMARTDMA_IRQn); 
    IRQ_DIRECT_CONNECT(SMARTDMA_IRQn, 0, EZH_INTERRUPT_ISR, 0) // IRQ_ZERO_LATENCY doesn't build yet

    //figure out what these do... From the old camera project.
    SYSCON->LPCAC_CTRL &= ~1;                                  // rocky: enable LPCAC ICache
    SYSCON->NVM_CTRL &= SYSCON->NVM_CTRL & ~(1 << 2 | 1 << 4); // enable flash Data cache     /* init I3C0*/
    SYSCON->AHBMATPRIO |= (0x3<<4)|(0x3<<6); // Give priority to SmartDMA

    PORT1->PCR[7]  = (7<<8) |(1<<12); //EZH_PIO3, PIO1_7

    CLOCK_EnableClock(kCLOCK_Smartdma); // enable EZH clock

    EZH_SetExternalFlag(0);

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
    ezh_parameters.p_buffer = (uint32_t *)params;

    ezh_parameters.p_buffer[0] = 1;

    EZH_Init(&ezh_parameters); // EZH initialisation


    LOG_INF("\n\nBUILDING PROGRAM 1");
    bunny_build(&my_ezh_program1[0],
                sizeof(my_ezh_program1),
                ezh_app__toggle1);

    LOG_INF("\n\nBUILDING PROGRAM 2");
    bunny_build(&my_ezh_program2[0],
                sizeof(my_ezh_program2),
                ezh_app__toggle2);

    irq_enable(SMARTDMA_IRQn);

#endif
}



void ezh__execute_command(uint8_t cmd)
{
    uint32_t * selected_program;

    switch (cmd)
    {
    case 1:
        EZH_boot(my_ezh_program1); // start EZH
        break;

    case 2:
        EZH_boot(my_ezh_program2); // start EZH
        break;
    default:
        break;
    }
}


void ezh_app__toggle1(void)
{
    E_NOP;
    E_NOP;

    E_PER_READ(R6, ARM2EZH);                // Read the base address of the parameters into R6
    E_LSR(R6, R6, 2);                       // make sure parameter structure 32-bit aligned
    E_LSL(R6, R6, 2);                       //

    E_LDR(SP, R6, 0);                       // load stack pointer from the 1st 32-bit word of the parameter struct
    E_LDR(R7, R6, 1);                       // R7 -> load the base address of debug parameter array into R7

    E_BSET_IMM(GPD, GPD, EZH_TEST_GPIO_1);
    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_1);
    E_BSET_IMM(GPD, GPD, EZH_TEST_GPIO_2);
    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_2);


    E_HEART_RYTHM_IMM((150000000 / 10));
    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();

    E_BCLR_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BCLR_IMM(GPO, GPO, EZH_TEST_GPIO_2); 

    
E_LABEL("END");
    E_PER_WRITE(R0, EZH2ARM);               //notify the arm that the command is complete
    E_HOLD();
}

void ezh_app__toggle2(void)
{
    E_NOP;
    E_NOP;

    E_PER_READ(R6, ARM2EZH);                // Read the base address of the parameters into R6
    E_LSR(R6, R6, 2);                       // make sure parameter structure 32-bit aligned
    E_LSL(R6, R6, 2); 

    E_LDR(SP, R6, 0);                       // load stack pointer from the 1st 32-bit word of the parameter struct
    E_LDR(R7, R6, 1);                       // R7 -> load the base address of debug parameter array into R7

    E_BSET_IMM(GPD, GPD, EZH_TEST_GPIO_1);
    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_1);
    E_BSET_IMM(GPD, GPD, EZH_TEST_GPIO_2);
    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_2);

    E_HEART_RYTHM_IMM((150000000 / 10));

    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_1); // Set test GPIO
    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_2); // Set test GPIO
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();

    E_BCLR_IMM(GPO, GPO, EZH_TEST_GPIO_1); // Clear test GPIO
    E_BCLR_IMM(GPO, GPO, EZH_TEST_GPIO_2); // Clear test GPIO
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();

    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_1); // Set test GPIO
    E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_2); // Set test GPIO
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();

    E_BCLR_IMM(GPO, GPO, EZH_TEST_GPIO_1); // Clear test GPIO
    E_BCLR_IMM(GPO, GPO, EZH_TEST_GPIO_2); // Clear test GPIO
    
E_LABEL("END");
    E_PER_WRITE(R0, EZH2ARM);           // Notify the arm that the command is complete
    E_HOLD();
}