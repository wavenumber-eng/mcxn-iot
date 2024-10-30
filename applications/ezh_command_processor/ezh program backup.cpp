
#include <zephyr/irq.h>
#include <zephyr/logging/log.h>

#include "fsl_common.h"
#include "fsl_clock.h"
#include "ezh_init.h"
#include <ezh_app.h>
#include "bunny_build.h"
#include "fsl_device_registers.h"

uint32_t ezh_stack[16];
uint32_t ezh_debug_params[5];
EZHPWM_Para ezh_parameters;

EZH_CMD_PROCESSOR_PARAMS cmd_processor_params;

uint32_t test_val = 0;

// EZH APPLICATIONS
__attribute((section("SRAM1"))) uint32_t my_ezh_program1[128]; // Todo relocate into fast SRAMX - no contention 
__attribute((section("SRAM1"))) uint32_t my_ezh_program2[128]; // Todo relocate into fast SRAMX - no contention 
__attribute((section("SRAM1"))) uint32_t my_ezh_program3[2048]; // Todo relocate into fast SRAMX - no contention 


void ezh_app__toggle1(void);
void ezh_app__toggle2(void);
void ezh_app__spi_wr(void);


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


LOG_MODULE_REGISTER(EZH_MGR);

void ezh__start_app()
{

#if defined(CONFIG_BOARD_LPCXPRESSO55S69_LPC55S69_CPU0)
    MRT0->CHANNEL[0].STAT = 0;

    EZH_SetExternalFlag(0);

    irq_disable(EZH__Reserved46_IRQn); // EZH irq NUMBER 30
    IRQ_DIRECT_CONNECT(EZH__Reserved46_IRQn, 0, Reserved46_IRQHandler__EZH, 0) // IRQ_ZERO_LATENCY doesn't build yet

    IOCON->PIO[0][24] = PINFUNC_EZH | 2 << 4 | 1 << 8;
    IOCON->PIO[0][25] = PINFUNC_EZH | 2 << 4 | 1 << 8;

    CLOCK_EnableClock(kCLOCK_Ezhb); // enable EZH clock

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

    PORT1->PCR[7]  = (7<<8) | (1<<12); //EZH_PIO3, PIO1_7

    CLOCK_EnableClock(kCLOCK_Smartdma); // enable EZH clock

    EZH_SetExternalFlag(0);

    irq_enable(SMARTDMA_IRQn);
#endif

//
//    LOG_INF("\n\nBUILDING PROGRAM 1");
//    bunny_build(&my_ezh_program1[0],
//                sizeof(my_ezh_program1),
//                ezh_app__toggle1);
//
//    LOG_INF("\n\nBUILDING PROGRAM 2");
//    bunny_build(&my_ezh_program2[0],
//                sizeof(my_ezh_program2),
//                ezh_app__toggle2);

    LOG_INF("\n\nBUILDING PROGRAM 3");
    bunny_build(&my_ezh_program3[0],
                sizeof(my_ezh_program3),
                ezh_app__spi_wr);
}



void ezh__execute_command(uint8_t cmd)
{
    uint32_t * selected_program;

    switch (cmd)
    {
    case TOGGLE1_APP:
        selected_program = my_ezh_program1; // start EZH
        break;

    case TOGGLE2_APP:
        selected_program = my_ezh_program2; // start EZH
        break;

    case SPI_WRITE_APP:
        selected_program = my_ezh_program3; // start EZH
        ezh_debug_params[0] = 0x00223344;
        break;

    default:
        break;
    }

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
    ezh_parameters.p_buffer = (uint32_t *)ezh_debug_params;
    EZH_init_and_boot(selected_program, &ezh_parameters);
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
    //E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_1);
    E_BSET_IMM(GPD, GPD, EZH_TEST_GPIO_2);
    //E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_2);


    E_HEART_RYTHM_IMM((150000000 / 10));
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();

E_PER_WRITE(R0, EZH2ARM);

E_LABEL("END");
    E_LOAD_IMM(CFS, 0);
    E_LOAD_SIMM(R0, 0xDB, 24);
    E_LOAD_SIMM(R1, 0x6D, 16);
    E_LOAD_SIMM(R2, 0xB6, 8);
    E_XOR(R0, R0, R1);
    E_XOR(CFM, R0, R2);
    E_HOLD();
    E_GOTO("END");
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
    //E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_1);
    E_BSET_IMM(GPD, GPD, EZH_TEST_GPIO_2);
    //E_BSET_IMM(GPO, GPO, EZH_TEST_GPIO_2);

    E_HEART_RYTHM_IMM((150000000 / 10));

    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();

    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();

E_PER_WRITE(R0, EZH2ARM);

E_LABEL("END");
    E_LOAD_IMM(CFS, 0);
    E_LOAD_SIMM(R0, 0xDB, 24);
    E_LOAD_SIMM(R1, 0x6D, 16);
    E_LOAD_SIMM(R2, 0xB6, 8);
    E_XOR(R0, R0, R1);
    E_XOR(CFM, R0, R2);
    E_HOLD();
    E_GOTO("END");
}


/*
              ___ _____  _   ___ ___ ___             
  ___   ___  | __|_  / || | / __| _ \_ _|  ___   ___ 
 |___| |___| | _| / /| __ | \__ \  _/| |  |___| |___|
             |___/___|_||_| |___/_| |___|            

*/                                                     



// LOAD 32 BIT IMM
#define E_LOAD_32IMM(rx, imm)                   \
    E_LOAD_SIMM(rx, (uint8_t)(imm >> 24), 24);  \
    E_LOAD_SIMM(R5, (uint8_t)(imm >> 16), 16);  \
    E_OR(rx, rx, R5);                           \
    E_LOAD_SIMM(R5, (uint8_t)(imm >> 8), 8);    \
    E_OR(rx, rx, R5);                           \
    E_LOAD_IMM(R5, (uint8_t)(imm));             \         
    E_OR(rx, rx, R5);                           

#define SPI8_FIFOWR_ADDR            (SPI8_BASE + 0xE20)  
#define SPI_FIFOWR__BASIC_CONFIG    ((1 << 22) | (7 << 24))


//  R0  -   
//  R1  -    
//  R2  -   
//  R3  -   PAYLOAD LENGTH
//  R4  -   PAYLOAD PTR
//  R5  -   TEMP FOR E_LOAD_32IMM
//  R6  -   PARAM STRUCT ADDRESS
//  R7  -   DEBUG_ARRAY POINTER 
void ezh_app__spi_wr(void){

    E_NOP;
    E_NOP;

    E_PER_READ(R6, ARM2EZH);                    // Read the base address of the parameters into R6
    E_LSR(R6, R6, 2);                           // make sure parameter structure 32-bit aligned
    E_LSL(R6, R6, 2); 
    E_LDR(SP, R6, 0);                           // load stack pointer from the 1st 32-bit word of the parameter struct
    E_LDR(R7, R6, 1);                           // R7 -> load the base address of debug parameter array into R7


    E_LDR(R2, R7, 0);
    E_GOSUB("SPI_WR_32_BITS");
//    E_WAIT_FOR_BEAT();
//    E_WAIT_FOR_BEAT();
//    E_WAIT_FOR_BEAT();
//    E_WAIT_FOR_BEAT();
//    E_GOSUB("SPI_WR_32_BITS");
//    E_WAIT_FOR_BEAT();
//    E_WAIT_FOR_BEAT();
//    E_WAIT_FOR_BEAT();
//    E_WAIT_FOR_BEAT();
//    E_GOSUB("SPI_WR_32_BITS");
    E_GOTO("END");


//    E_LOAD_IMMS(R0, 0);
//    E_COND_GOTO(ZE, "END");
//
//E_LABEL("LOOP");
//
//                                        // PLACE ARGUMENT IN R0
//    E_GOSUB("SPI_WR_32_BITS");
//
//    E_COND_GOTO(ZE, "END");




/*
    SPI_WR_32_BITS
    R0  -   TRANSACTION ADDRESS (ARGUMENT)
    R1  -   SPI TRANSACTION CONFIGS + BYTE TO WRITE
    R2  -   SPI8_FIFOWR_ADDR
*/

E_LABEL("SPI_WR_32_BITS");
//    E_PUSH(RA);
//    E_PUSH(R1);
//    E_PUSH(R2);
    E_LOAD_32IMM(R2, SPI8_FIFOWR_ADDR);         // R2 = SPI8_FIFOWR_ADDR


    E_LOAD_32IMM(R1, SPI_FIFOWR__BASIC_CONFIG); 
    E_LDRB(R0, R7, 2);              
    E_OR(R1, R1, R2);
    E_STR(R0, R1, 0);

    E_LOAD_32IMM(R1, SPI_FIFOWR__BASIC_CONFIG);
    E_LDRB(R0, R7, 1);
    E_NOP;
    E_NOP;
    E_NOP;
    E_PER_WRITE(R0, EZH2ARM);

    E_OR(R1, R1, R2);
    E_STR(R0, R1, 0);



    E_LOAD_32IMM(R1, SPI_FIFOWR__BASIC_CONFIG);
    E_LDRB(R0, R7, 0);
    E_OR(R1, R1, R2);
    E_STR(R0, R1, 0);



//    E_POP(R2);
//    E_POP(R1);
//    E_POP(RA);    
    E_GOTO_REG(RA);



    E_PER_WRITE(R0, EZH2ARM);               // IRQ

E_LABEL("END");
    E_LOAD_IMM(CFS, 0);
    E_LOAD_SIMM(R0, 0xDB, 24);
    E_LOAD_SIMM(R1, 0x6D, 16);
    E_LOAD_SIMM(R2, 0xB6, 8);
    E_XOR(R0, R0, R1);
    E_XOR(CFM, R0, R2);
    E_HOLD();
    E_GOTO("END");
}



// BACKUP