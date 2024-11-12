
#include <zephyr/irq.h>
#include <zephyr/logging/log.h>

#include "fsl_common.h"
#include "fsl_clock.h"
#include "ezh_init.h"
#include <ezh_app.h>
#include "bunny_build.h"
#include "fsl_device_registers.h"





__attribute((section("SRAMX_EZH"))) uint32_t ezh_ram[512];



// EZH APPLICATIONS

#define CONFIG_BOARD_LPCXPRESSO55S69_LPC55S69_CPU0

#if defined(CONFIG_BOARD_GIBBON_D_LPC55S69_CPU0) | defined(CONFIG_BOARD_LPCXPRESSO55S69_LPC55S69_CPU0)
__attribute((section("SRAMX_EZH"))) uint32_t ezh_app0[256];
__attribute((section("SRAMX_EZH"))) uint32_t ezh_app1[256];


#elif defined (CONFIG_BOARD_FRDM_MCXN947_MCXN947_CPU0)
__attribute((section("SRAM1"))) uint32_t my_ezh_program1[128]; // Todo relocate into fast SRAMX - no contention 
__attribute((section("SRAM1"))) uint32_t my_ezh_program2[128]; // Todo relocate into fast SRAMX - no contention 
__attribute((section("SRAM1"))) uint32_t my_ezh_program3[512]; // Todo relocate into fast SRAMX - no contention 
#endif

void ezh_app__toggle1(void);
void ezh_app__toggle2(void);
void ezh_app__spi_wr(void);
void ezh_app__spi_rd(void);

#define EZH_TEST_GPIO_1 18
#define EZH_TEST_GPIO_2 25

#if defined(CONFIG_BOARD_GIBBON_D_LPC55S69_CPU0) | defined(CONFIG_BOARD_LPCXPRESSO55S69_LPC55S69_CPU0)

#define EZH__Reserved46_IRQn (IRQn_Type)30

static volatile bool last_ezh_op_complete = true;
uint32_t ezh_app_offset[8];
uint32_t test_val;
ISR_DIRECT_DECLARE(Reserved46_IRQHandler__EZH)
{
    EZH_SetExternalFlag(1);

    last_ezh_op_complete=true;

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

void ezh__build_apps()
{

#if defined(CONFIG_BOARD_GIBBON_D_LPC55S69_CPU0) | defined(CONFIG_BOARD_LPCXPRESSO55S69_LPC55S69_CPU0)


    EZH_SetExternalFlag(0);

    irq_disable(EZH__Reserved46_IRQn); // EZH irq NUMBER 30
    IRQ_DIRECT_CONNECT(EZH__Reserved46_IRQn, 0, Reserved46_IRQHandler__EZH, 0) // IRQ_ZERO_LATENCY doesn't build yet

    IOCON->PIO[0][18] = PINFUNC_EZH | 2 << 4 | 1 << 8;
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


   uint32_t last_idx=0;
   uint32_t num_ezh_apps=0;

   ezh_app_offset[SPI_WRITE_APP] = last_idx;

   last_idx += bunny_build(&ezh_ram[ezh_app_offset[SPI_WRITE_APP]],
                sizeof(ezh_app0),
                ezh_app__spi_wr);

   num_ezh_apps++;

   ezh_app_offset[SPI_READ_APP] = 256;

   last_idx += bunny_build(&ezh_ram[ ezh_app_offset[SPI_READ_APP]],
                    sizeof(ezh_app1),
                    ezh_app__spi_rd);
   num_ezh_apps++;


   BUNNY_BUILD_PRINTF("Built %d ezh apps using a total of %d bytes\r\n",num_ezh_apps,last_idx*4);


}

uint32_t * selected_program = 0;
uint32_t offset = 0;

void ezh__execute_command(uint8_t cmd, EZHPWM_Para * ezh_parameters_ptr)
{
    if(cmd<EZH_APP_QTY)
    {
        offset = ezh_app_offset[cmd];
        selected_program = &ezh_ram[offset];
       // selected_program =  &ezh_ram[ezh_app_offset[cmd]];


    //the offset array gets trashed after teh 1st call...

        if(cmd == 0)
            selected_program = &ezh_ram[0];
        else
            selected_program = &ezh_ram[256];

        last_ezh_op_complete=false;

        EZH_init_and_boot(selected_program, ezh_parameters_ptr);
    }
}

bool ezh__command_complete()
{
    return last_ezh_op_complete;
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
    E_PUSH(R5);                                 \
    E_LOAD_SIMM(rx, (uint8_t)(imm >> 24), 24);  \
    E_LOAD_SIMM(R5, (uint8_t)(imm >> 16), 16);  \
    E_OR(rx, rx, R5);                           \
    E_LOAD_SIMM(R5, (uint8_t)(imm >> 8), 8);    \
    E_OR(rx, rx, R5);                           \
    E_LOAD_IMM(R5, (uint8_t)(imm));             \
    E_OR(rx, rx, R5);                           \
    E_POP(R5);               



#if defined(CONFIG_BOARD_GIBBON_D_LPC55S69_CPU0)  | defined(CONFIG_BOARD_LPCXPRESSO55S69_LPC55S69_CPU0)
#define SPI8_FIFOWR_ADDR            (SPI8_BASE + 0xE20)  
#define SPI8_FIFORD_ADDR            (SPI8_BASE + 0xE30)  
#define SPI8_FIFOCFG_ADDR           (SPI8_BASE + 0xE00)  
#define SPI8_FIFOSTAT_ADDR          (SPI8_BASE + 0XE04)

#define SPI_FIFOWR__BASIC_CONFIG_WR    ((1 << 22) | (7 << 24))                                  //Activating all chip selects

#define SPI_FIFOWR__BASIC_CONFIG_WR_EOT  ((1 << 22) | (7 << 24) | (0xf<<16) | (1<<20))         //Note:  deactiving all chip selects

#define SPI_FIFOWR__BASIC_CONFIG_RD       ((7 << 24) | (0xf<<16))                               //Activating all chip selects
#define SPI_FIFOWR__BASIC_CONFIG_RD_EOT   (SPI_FIFOWR__BASIC_CONFIG_RD | (0xf<<16) | (1<<20))   //Note:  deactiving all chip selects

#elif defined (CONFIG_BOARD_FRDM_MCXN947_MCXN947_CPU0)
#define SPI8_FIFOWR_ADDR            (0)  
#define SPI_FIFOWR__BASIC_CONFIG_WR    (0) 

#endif


#if defined(CONFIG__SPI_SCK_FREQ) && (CONFIG__SPI_SCK_FREQ == 10000000)
#define MAGIC_RYTHM ((7 * 15) + 6)  //for 10MHz
#elif defined(CONFIG__SPI_SCK_FREQ) && (CONFIG__SPI_SCK_FREQ == 25000000)
#define MAGIC_RYTHM ((7 * 5) + 18 ) //for 25MHz
#elif defined(CONFIG__SPI_SCK_FREQ) && (CONFIG__SPI_SCK_FREQ == 33000000)
#define MAGIC_RYTHM (15) //for 33MHz
#else
#error "SPI_SCK_FREQ NOT DEFINED"
#endif



/*
    Work In Progress SPI_WR
        this function pretends to be a SPI write function, similar to the SPI read implementation
*/
void ezh_app__spi_wr(void)
{
    E_NOP;
    E_NOP;

    E_PER_READ(R6, ARM2EZH);                    // Read the base address of the parameters into R6
    E_LSR(R6, R6, 2);                           // make sure parameter structure 32-bit aligned
    E_LSL(R6, R6, 2); 
    E_LDR(SP, R6, 0);                           // load stack pointer from the 1st 32-bit word of the parameter struct
    E_LDR(R7, R6, 1);                           // R7 -> load the base address the parameters struct

    E_HEART_RYTHM_IMM(MAGIC_RYTHM);

    // Transmit CMD + ADDR
    E_ADD_IMM(R0, R7, 0);                           
    E_GOSUB("SPI_WR_32_BITS");

    E_LDR(R2, R7, 2);                           // Load buffer length
    E_LDR(R5, R7, 3);                           // R3 = RX_BUFF PTR

    // WRITE BYTES OVER SPI8
E_LABEL("WRITE_BYTES");
    E_LOAD_32IMM(R0, SPI_FIFOWR__BASIC_CONFIG_WR);      // R0 = SPI_FIFOWR__BASIC_CONFIG_WR
    E_LOAD_32IMM(R1, SPI8_FIFOWR_ADDR);                 // R1 = SPI8_FIFOWR_ADDR


E_LABEL("WRITE_BYTES_LOOP");   

    //Subtract 1 and to see if this is the last byte
    //if so, change the SPI register for the last transmission to flat EOT and disable chip selects
    E_LOAD_32IMM(R0, SPI_FIFOWR__BASIC_CONFIG_WR);
    E_SUB_IMMS(R2, R2, 1); 
    E_COND_GOTO(NZ, "NEXT_BYTE_OUT");
    E_LOAD_32IMM(R0, SPI_FIFOWR__BASIC_CONFIG_WR_EOT);

E_LABEL("NEXT_BYTE_OUT");  
    
    E_LDRB_POST(R4, R5, 1);
    E_OR(R0,R0, R4);

    E_GOSUB("SPI_WR_BYTE");
    E_PUSH(R2);
    E_ADD_IMMS(R2, R2, 0);                      //UPDATE THE ALU FLAGS 
    E_COND_GOTO(ZE, "END");
    E_GOTO("WRITE_BYTES_LOOP");


    E_GOTO("END");


/*
    SPI_WR_BYTE
        R0  -   CURRENT BYTE TO TRANSMIT    -   ARG
        R1  -   SPI8_FIFOWR_ADDR
*/
E_LABEL("SPI_WR_BYTE");
    E_PUSH(RA);
    E_STR(R1, R0, 0);
    E_WAIT_FOR_BEAT();
    E_POP(RA);
    E_GOTO_REG(RA);


/*
    SPI_WR_32_BITS
        R0  -   ADDRESS OF THE 32-BIT value to transmit
        R1  -   CURRENT BYTE TO TRANSMIT
        R2  -   SPI TRANSACTION CONFIGS + BYTE TO WRITE
        R3  -   SPI8_FIFOWR_ADDR
*/
E_LABEL("SPI_WR_32_BITS");
    E_PUSH(RA);
    E_PUSH(R1);
    E_PUSH(R2);
    E_PUSH(R3);   

    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 

    // TRANSMIT value[31:24]
    E_LOAD_32IMM(R3, SPI8_FIFOWR_ADDR);               // R3 = SPI8_FIFOWR_ADDR
    E_LOAD_32IMM(R2, SPI_FIFOWR__BASIC_CONFIG_WR);     // R2 = SPI_FIFOWR__BASIC_CONFIG_RD
    E_LDRB(R1, R0, 3);              
    E_OR(R2, R2, R1);
    E_STR(R3, R2, 0);
    E_WAIT_FOR_BEAT();

    // TRANSMIT value[33:16]
    E_LOAD_32IMM(R2, SPI_FIFOWR__BASIC_CONFIG_WR); 
    E_LDRB(R1, R0, 2); 
    E_OR(R2, R2, R1);
    E_STR(R3, R2, 0);
    E_WAIT_FOR_BEAT();

    // TRANSMIT value[15:8]
    E_LOAD_32IMM(R2, SPI_FIFOWR__BASIC_CONFIG_WR);
    E_LDRB(R1, R0, 1);
    E_OR(R2, R2, R1);
    E_STR(R3, R2, 0);
    E_WAIT_FOR_BEAT();

    // TRANSMIT value[7:0]
    E_LOAD_32IMM(R2, SPI_FIFOWR__BASIC_CONFIG_WR);
    E_LDRB(R1, R0, 0);
    E_OR(R2, R2, R1);
    E_STR(R3, R2, 0);   
    E_WAIT_FOR_BEAT();
    
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 

    E_POP(R3);
    E_POP(R2);
    E_POP(R1);
    E_POP(RA);
    E_GOTO_REG(RA);


/*
    END
        End the program and trigger an interrupt
*/
E_LABEL("END");
    E_PER_WRITE(R1, EZH2ARM);               // IRQ
    
E_LABEL("END_LOOP");   
    E_LOAD_IMM(CFS, 0);
    E_LOAD_SIMM(R0, 0xDB, 24);
    E_LOAD_SIMM(R1, 0x6D, 16);
    E_LOAD_SIMM(R2, 0xB6, 8);
    E_XOR(R0, R0, R1);
    E_XOR(CFM, R0, R2);
    E_HOLD();
    E_GOTO("END_LOOP");    
}


#define SPI_READ_JUNK_BYTE  0X00
#define START_RXLVL     2 

void ezh_app__spi_rd(void)
{
    E_NOP;
    E_NOP;

    E_PER_READ(R6, ARM2EZH);                    // Read the base address of the parameters into R6
    E_LSR(R6, R6, 2);                           // make sure parameter structure 32-bit aligned
    E_LSL(R6, R6, 2); 
    E_LDR(SP, R6, 0);                           // load stack pointer from the 1st 32-bit word of the parameter struct
    E_LDR(R7, R6, 1);                           // R7 -> load the base address the parameters struct

    E_LOAD_32IMM(R3, SPI8_FIFORD_ADDR);                 // R3 = SPI8_FIFORD_ADDR
    E_LDR(R5, R7, 3);                                   // R5 = RX_BUFF PTR


    E_BSET_IMM(GPD, GPD, EZH_TEST_GPIO_1);
    E_BSET_IMM(GPD, GPD, EZH_TEST_GPIO_2);
    E_BCLR_IMM(GPO, GPO, EZH_TEST_GPIO_1);
    E_BCLR_IMM(GPO, GPO, EZH_TEST_GPIO_2);

    E_HEART_RYTHM_IMM(MAGIC_RYTHM);

    // Transmit CMD + ADDR
    E_ADD_IMM(R0, R7, 0);                               // R0 = cmd_and_addr
    E_GOSUB("SPI_WR_32_BITS");


    // Wait do not care cycles (1 bytes - 8 cycles)
    E_LDR(R2, R7, 1);                                   // R2 = NUM OF DONT CARE BYTES
    E_ADD_IMMS(R2, R2, 0);                              // UPDATE FLAGS
    E_COND_GOTO(ZE, "READ_BYTES");
    E_LOAD_32IMM(R0, SPI_FIFOWR__BASIC_CONFIG_WR);      // R0 = SPI_FIFOWR__BASIC_CONFIG_WR
    E_LOAD_32IMM(R1, SPI8_FIFOWR_ADDR);                 // R1 = SPI8_FIFOWR_ADDR    

E_LABEL("DONT_CARE_BYTES_LOOP");
    E_COND_GOTO(ZE, "READ_BYTES");
    E_GOSUB("SPI_WR_BYTE");
    E_SUB_IMMS(R2, R2, 1); 
    E_GOSUB("DONT_CARE_BYTES_LOOP");


    // READ INCOMING BYTES AND PUT THEM IN THE PARAMS BUFFER
E_LABEL("READ_BYTES");
        
    E_LDR(R2, R7, 2);                                   // R2 = NUM OF BYTES TO READ

//    // Clear FIFOs
//    E_LOAD_32IMM(R1, SPI8_FIFOCFG_ADDR);       
//    E_LOAD_32IMM(R0,0x00030003);               
//    E_STR(R1, R0, 0);

    // Setup spi write reg
    E_LOAD_32IMM(R0, SPI_FIFOWR__BASIC_CONFIG_RD);      // R0 = SPI_FIFOWR__BASIC_CONFIG_RD
    E_OR_IMM(R0, R0, SPI_READ_JUNK_BYTE);
    E_LOAD_32IMM(R1, SPI8_FIFOWR_ADDR);                 // R1 = SPI8_FIFOWR_ADDR

    //start TX pipeline
    E_GOSUB("SPI_WR_BYTE"); 
    E_GOSUB("SPI_WR_BYTE"); 
    E_SUB_IMMS(R2, R2, 2); 


    // POLL UNTIL WE GET "START_RXLVL" INCOMING BYTES
E_LABEL("POLL_START");
    E_LOAD_32IMM(R0, SPI8_FIFOSTAT_ADDR);                 // R1 = SPI8_FIFOWR_
E_LABEL("POLL_START_LOOP");
    E_LDRB(R1, R0, 2);
    E_AND_IMM(R1, R1, 0b11111);
    E_SUB_IMMS(R1, R1, START_RXLVL);
    E_COND_GOTO(NZ, "POLL_START_LOOP");

    E_LOAD_32IMM(R0, SPI_FIFOWR__BASIC_CONFIG_RD);      // R0 = SPI_FIFOWR__BASIC_CONFIG_RD
    E_LOAD_32IMM(R1, SPI8_FIFOWR_ADDR);                 // R1 = SPI8_FIFOWR_ADDR

E_LABEL("READ_BYTES_LOOP");   

    //Subtract 1 and to see if this is the last byte
    //if so, change the SPI register for the last transmission to flat EOT and disable chip selects
    E_SUB_IMMS(R2, R2, 1); 
    E_COND_GOTO(NZ, "NEXT_BYTE_OUT");
    E_LOAD_32IMM(R0, SPI_FIFOWR__BASIC_CONFIG_RD_EOT);      // R0 = SPI_FIFOWR__BASIC_CONFIG_RD

E_LABEL("NEXT_BYTE_OUT");   

    E_GOSUB("SPI_WR_BYTE");                             //WRITE TO GENERATE THE CLOCK
    
    //READ THE FIFO, STORE IT IN THE RX_BUFFER, AND THEN INCREMENT THE PTR
    E_LDR(R4, R3, 0);
    E_STRB_POST(R5, R4, 1);

    E_ADD_IMMS(R2, R2, 0); 
    E_COND_GOTO(ZE, "CLEAN_FIFO");
    E_GOSUB("READ_BYTES_LOOP");



E_LABEL("CLEAN_FIFO");
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_LOAD_32IMM(R0, SPI8_FIFOSTAT_ADDR);                 // R1 = SPI8_FIFOWR_
E_LABEL("CLEAN_FIFO_LOOP");
    E_LDRB(R1, R0, 2);
    E_AND_IMMS(R1, R1, 0b11111);
    E_COND_GOTO(ZE, "END");

    //READ THE FIFO, STORE IT IN THE RX_BUFFER, AND THEN INCREMENT THE PTR
    E_LDR(R4, R3, 0);
    E_STRB_POST(R5, R4, 1);
    E_GOTO("CLEAN_FIFO_LOOP");

    E_GOTO("END");
E_LABEL("LAST_BYTE");


/*
    SPI_WR_BYTE
        R0  -   CURRENT BYTE TO TRANSMIT    -   ARG
        R1  -   SPI8_FIFOWR_ADDR
*/
E_LABEL("SPI_WR_BYTE");
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_PUSH(RA);
    E_STR(R1, R0, 0);
    E_WAIT_FOR_BEAT();
    E_POP(RA);
    E_GOTO_REG(RA);
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 

/*
    SPI_WR_32_BITS
        R0  -   ADDRESS OF THE 32-BIT value to transmit
        R1  -   CURRENT BYTE TO TRANSMIT
        R2  -   SPI TRANSACTION CONFIGS + BYTE TO WRITE
        R3  -   SPI8_FIFOWR_ADDR
*/
E_LABEL("SPI_WR_32_BITS");
    E_PUSH(RA);
    E_PUSH(R1);
    E_PUSH(R2);
    E_PUSH(R3);   

    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 

    // TRANSMIT value[31:24]
    E_LOAD_32IMM(R3, SPI8_FIFOWR_ADDR);               // R3 = SPI8_FIFOWR_ADDR
    E_LOAD_32IMM(R2, SPI_FIFOWR__BASIC_CONFIG_WR);     // R2 = SPI_FIFOWR__BASIC_CONFIG_RD
    E_LDRB(R1, R0, 3);              
    E_OR(R2, R2, R1);
    E_STR(R3, R2, 0);
    E_WAIT_FOR_BEAT();

    // TRANSMIT value[33:16]
    E_LOAD_32IMM(R2, SPI_FIFOWR__BASIC_CONFIG_WR); 
    E_LDRB(R1, R0, 2); 
    E_OR(R2, R2, R1);
    E_STR(R3, R2, 0);
    E_WAIT_FOR_BEAT();

    // TRANSMIT value[15:8]
    E_LOAD_32IMM(R2, SPI_FIFOWR__BASIC_CONFIG_WR);
    E_LDRB(R1, R0, 1);
    E_OR(R2, R2, R1);
    E_STR(R3, R2, 0);
    E_WAIT_FOR_BEAT();

    // TRANSMIT value[7:0]
    E_LOAD_32IMM(R2, SPI_FIFOWR__BASIC_CONFIG_WR);
    E_LDRB(R1, R0, 0);
    E_OR(R2, R2, R1);
    E_STR(R3, R2, 0);   
    E_WAIT_FOR_BEAT();
    
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 

    E_POP(R3);
    E_POP(R2);
    E_POP(R1);
    E_POP(RA);
    E_GOTO_REG(RA);


/*  
    END
*/
E_LABEL("END");
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    E_WAIT_FOR_BEAT();
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    E_WAIT_FOR_BEAT();
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_1); 
    E_BTOG_IMM(GPO, GPO, EZH_TEST_GPIO_2); 
    
    E_PER_WRITE(R1, EZH2ARM);               // IRQ  
    
E_LABEL("END_LOOP");   
    E_LOAD_IMM(CFS, 0);
    E_LOAD_SIMM(R0, 0xDB, 24);
    E_LOAD_SIMM(R1, 0x6D, 16);
    E_LOAD_SIMM(R2, 0xB6, 8);
    E_XOR(R0, R0, R1);
    E_XOR(CFM, R0, R2);
    E_HOLD();
    E_GOSUB("END_LOOP");
}
