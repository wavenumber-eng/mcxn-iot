#if defined(CONFIG_BOARD_GIBBON_D_LPC55S69_CPU0)
#include <zephyr/init.h>
#include <zephyr/devicetree.h>
#include <fsl_common.h>
#include <fsl_power.h>
#include <fsl_iocon.h>
#include <fsl_clock.h>
#include <fsl_sysctl.h>
#include <soc.h>

/* System clock frequency */
extern uint32_t SystemCoreClock;

const pll_setup_t pll1Setup = {
    .pllctrl = SYSCON_PLL1CTRL_CLKEN_MASK | SYSCON_PLL1CTRL_SELI(53U) | SYSCON_PLL1CTRL_SELP(31U),
    .pllndec = SYSCON_PLL1NDEC_NDIV(8U),
    .pllpdec = SYSCON_PLL1PDEC_PDIV(1U),
    .pllmdec = SYSCON_PLL1MDEC_MDIV(150U),
    .pllRate = 150000000U,
    .flags = PLL_SETUPFLAG_WAITLOCK};

static int board_clocks(void) {
    SystemCoreClock = 96000000U;
    CLOCK_AttachClk(kFRO12M_to_MAIN_CLK);

    /* Ensure CLK_IN is on  */
    SYSCON->CLOCK_CTRL |= SYSCON_CLOCK_CTRL_CLKIN_ENA_MASK;
    ANACTRL->XO32M_CTRL |= ANACTRL_XO32M_CTRL_ENABLE_SYSTEM_CLK_OUT_MASK;

    /* Configure XTAL32M - Should be in the range of 12MHz to 32MHz */
    uint32_t ExternalClockFrequency = 16000000U;
    CLOCK_SetupExtClocking(ExternalClockFrequency);
    /* Enable FRO HF(SystemCoreClock) output (Default expected value 96MHz) */
    CLOCK_SetupFROClocking(SystemCoreClock);
    /* Switch MAIN_CLK to FRO_HF */
    CLOCK_AttachClk(kFRO_HF_to_MAIN_CLK);

    SystemCoreClock = 150000000U;

#if !defined(CONFIG_TRUSTED_EXECUTION_NONSECURE)
    /* Set Voltage for one of the fastest clock outputs: System clock output */
    POWER_SetVoltageForFreq(SystemCoreClock);
    /*!< Set FLASH wait states for core */
    CLOCK_SetFLASHAccessCyclesForFreq(SystemCoreClock);
#endif /* !CONFIG_TRUSTED_EXECUTION_NONSECURE */

    /* Switch PLL1 clock source selector to XTAL32M */
    CLOCK_AttachClk(kEXT_CLK_to_PLL1);
    /* Ensure PLL1 is on */
    POWER_DisablePD(kPDRUNCFG_PD_PLL1);
    /* Configure PLL to the desired values */
    CLOCK_SetPLL1Freq(&pll1Setup);
    /* Switch MAIN_CLK to FRO_HF */
    CLOCK_AttachClk(kPLL1_to_MAIN_CLK);
    return 0;
}

static int init_flexcomm_clocks(void) {
    /* attach 12 MHz clock to FLEXCOMM5 */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM5);
    /* reset FLEXCOMM for I2C */
    RESET_PeripheralReset(kFC5_RST_SHIFT_RSTn);
#if DT_NODE_HAS_COMPAT_STATUS(DT_NODELABEL(flexcomm1), nxp_lpc_spi, okay)
#if FSL_CLOCK_DRIVER_VERSION >= MAKE_VERSION(2, 3, 4)
    CLOCK_SetClkDiv(kCLOCK_DivFlexFrg1, 0U, false);         /*!< Set DIV to value 0xFF and MULT to value 0U in related FLEXFRGCTRL register */
#else
    CLOCK_SetClkDiv(kCLOCK_DivFlexFrg1, 256U, false);         /*!< Set DIV to value 0xFF and MULT to value 0U in related FLEXFRGCTRL register */
#endif
    CLOCK_SetClkDiv(kCLOCK_DivFrohfClk, 0U, true);	/*!< Reset FROHFDIV divider counter and halt it */
    CLOCK_SetClkDiv(kCLOCK_DivFrohfClk, 4U, false); /*!< Set FROHFDIV divider to value 4 */
    /* attach 24 MHz clock to FLEXCOMM1 */
    CLOCK_AttachClk(kFRO_HF_DIV_to_FLEXCOMM1);
    /* reset FLEXCOMM for SPI */
    RESET_PeripheralReset(kFC1_RST_SHIFT_RSTn);
#endif // DT_NODE_HAS_COMPAT_STATUS(DT_NODELABEL(flexcomm1), nxp_lpc_spi, okay)

     SYSCTL_Init(SYSCTL);
#if (DT_NODE_HAS_COMPAT_STATUS(DT_NODELABEL(flexcomm0), te_lpc_i2s, okay))
    /* attach PLL0 clock to FLEXCOMM0 */
    CLOCK_AttachClk(kPLL0_DIV_to_FLEXCOMM0);
    /* attach FLEXCOMM0 to ShareSet0 */
    SYSCTL_SetShareSet(SYSCTL, kSYSCTL_Flexcomm0, kSYSCTL_FlexcommSignalSCK, kSYSCTL_ShareSet0);
    SYSCTL_SetShareSet(SYSCTL, kSYSCTL_Flexcomm0, kSYSCTL_FlexcommSignalWS, kSYSCTL_ShareSet0);
    /* share data in to share set 0. */
    SYSCTL_SetShareSignalSrc(SYSCTL, kSYSCTL_ShareSet0, kSYSCTL_SharedCtrlSignalDataIn, kSYSCTL_Flexcomm0);
    RESET_PeripheralReset(kFC0_RST_SHIFT_RSTn);
#endif

#if (DT_NODE_HAS_COMPAT_STATUS(DT_NODELABEL(flexcomm4), te_lpc_i2s, okay))
    /* attach PLL0 clock to FLEXCOMM4 */
    CLOCK_AttachClk(kPLL0_DIV_to_FLEXCOMM4);
    /* attach FLEXCOMM4 to ShareSet0 */
    SYSCTL_SetShareSet(SYSCTL, kSYSCTL_Flexcomm4, kSYSCTL_FlexcommSignalSCK, kSYSCTL_ShareSet0);
    SYSCTL_SetShareSet(SYSCTL, kSYSCTL_Flexcomm4, kSYSCTL_FlexcommSignalWS, kSYSCTL_ShareSet0);
    SYSCTL_SetShareSet(SYSCTL, kSYSCTL_Flexcomm4, kSYSCTL_FlexcommSignalDataIn, kSYSCTL_ShareSet0);
    RESET_PeripheralReset(kFC4_RST_SHIFT_RSTn);
#endif


#if (DT_NODE_HAS_COMPAT_STATUS(DT_NODELABEL(flexcomm7), te_lpc_i2s, okay))
    /* attach PLL0 clock to FLEXCOMM7 */
    CLOCK_AttachClk(kPLL0_DIV_to_FLEXCOMM7);
    /* attach FLEXCOMM7 to ShareSet0 */
    SYSCTL_SetShareSignalSrc(SYSCTL, kSYSCTL_ShareSet0, kSYSCTL_SharedCtrlSignalSCK, kSYSCTL_Flexcomm7);
    SYSCTL_SetShareSignalSrc(SYSCTL, kSYSCTL_ShareSet0, kSYSCTL_SharedCtrlSignalWS, kSYSCTL_Flexcomm7);
    RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn);
#endif

#if (DT_NODE_HAS_COMPAT_STATUS(DT_NODELABEL(hs_lspi), nxp_lpc_spi, okay))

    CLOCK_AttachClk(kMAIN_CLK_to_HSLSPI);
  
#endif

    return 0;
}

SYS_INIT(board_clocks, APPLICATION, 0);
SYS_INIT(init_flexcomm_clocks, PRE_KERNEL_1, 0);
#endif // defined(CONFIG_BOARD_GIBBON_D_LPC55S69_CPU0)
