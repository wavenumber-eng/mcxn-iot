#define CONFIG_NET_L2_ETHERNET 1
#define CONFIG_SERIAL 1
#define CONFIG_UART_INTERRUPT_DRIVEN 1
#define CONFIG_MAIN_STACK_SIZE 1024
#define CONFIG_NUM_IRQS 155
#define CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC 150000000
#define CONFIG_FLASH_SIZE 2048
#define CONFIG_FLASH_BASE_ADDRESS 0x10000000
#define CONFIG_MP_MAX_NUM_CPUS 1
#define CONFIG_PLATFORM_SPECIFIC_INIT 1
#define CONFIG_SYS_CLOCK_TICKS_PER_SEC 10000
#define CONFIG_ROM_START_OFFSET 0x0
#define CONFIG_PINCTRL 1
#define CONFIG_BUILD_OUTPUT_BIN 1
#define CONFIG_XIP 1
#define CONFIG_IDLE_STACK_SIZE 320
#define CONFIG_HAS_FLASH_LOAD_OFFSET 1
#define CONFIG_CPU_HAS_ARM_MPU 1
#define CONFIG_TICKLESS_KERNEL 1
#define CONFIG_SYSTEM_WORKQUEUE_STACK_SIZE 1024
#define CONFIG_CORTEX_M_SYSTICK 1
#define CONFIG_CLOCK_CONTROL_INIT_PRIORITY 30
#define CONFIG_PHY_INIT_PRIORITY 70
#define CONFIG_FLASH_LOAD_OFFSET 0x0
#define CONFIG_HW_STACK_PROTECTION 1
#define CONFIG_NET_UDP_CHECKSUM 1
#define CONFIG_HEAP_MEM_POOL_SIZE 0
#define CONFIG_SERIAL_INIT_PRIORITY 55
#define CONFIG_FLASH_FILL_BUFFER_SIZE 128
#define CONFIG_GPIO 1
#define CONFIG_KERNEL_ENTRY "__start"
#define CONFIG_LOG 1
#define CONFIG_DCACHE_LINE_SIZE 32
#define CONFIG_GEN_IRQ_VECTOR_TABLE 1
#define CONFIG_SOC "mcxn947"
#define CONFIG_ARCH_SW_ISR_TABLE_ALIGN 4
#define CONFIG_LOG_DOMAIN_NAME ""
#define CONFIG_CLOCK_CONTROL 1
#define CONFIG_UART_USE_RUNTIME_CONFIGURE 1
#define CONFIG_ENTROPY_INIT_PRIORITY 50
#define CONFIG_SOC_SERIES "mcxnx4x"
#define CONFIG_SOC_FAMILY "nxp_mcx"
#define CONFIG_COMMON_LIBC_MALLOC_ARENA_SIZE -1
#define CONFIG_GEN_ISR_TABLES 1
#define CONFIG_GEN_SW_ISR_TABLE 1
#define CONFIG_GEN_IRQ_START_VECTOR 0
#define CONFIG_SRAM_OFFSET 0x0
#define CONFIG_CONSOLE 1
#define CONFIG_ARCH_IRQ_VECTOR_TABLE_ALIGN 4
#define CONFIG_ISR_STACK_SIZE 2048
#define CONFIG_ICACHE_LINE_SIZE 32
#define CONFIG_PRIVILEGED_STACK_SIZE 1024
#define CONFIG_DT_HAS_ARM_ARMV8M_MPU_ENABLED 1
#define CONFIG_DT_HAS_ARM_ARMV8M_SYSTICK_ENABLED 1
#define CONFIG_DT_HAS_ARM_CORTEX_M33F_ENABLED 1
#define CONFIG_DT_HAS_ARM_V8M_NVIC_ENABLED 1
#define CONFIG_DT_HAS_ETHERNET_PHY_ENABLED 1
#define CONFIG_DT_HAS_FIXED_PARTITIONS_ENABLED 1
#define CONFIG_DT_HAS_GPIO_KEYS_ENABLED 1
#define CONFIG_DT_HAS_GPIO_LEDS_ENABLED 1
#define CONFIG_DT_HAS_MMIO_SRAM_ENABLED 1
#define CONFIG_DT_HAS_NXP_EHCI_ENABLED 1
#define CONFIG_DT_HAS_NXP_ENET_QOS_ENABLED 1
#define CONFIG_DT_HAS_NXP_ENET_QOS_MAC_ENABLED 1
#define CONFIG_DT_HAS_NXP_ENET_QOS_MDIO_ENABLED 1
#define CONFIG_DT_HAS_NXP_FLEXCAN_ENABLED 1
#define CONFIG_DT_HAS_NXP_FLEXIO_ENABLED 1
#define CONFIG_DT_HAS_NXP_FLEXPWM_ENABLED 1
#define CONFIG_DT_HAS_NXP_IAP_MSF1_ENABLED 1
#define CONFIG_DT_HAS_NXP_IMX_FLEXSPI_ENABLED 1
#define CONFIG_DT_HAS_NXP_IMX_FLEXSPI_NOR_ENABLED 1
#define CONFIG_DT_HAS_NXP_IMX_LPI2C_ENABLED 1
#define CONFIG_DT_HAS_NXP_IMX_LPSPI_ENABLED 1
#define CONFIG_DT_HAS_NXP_IMX_PWM_ENABLED 1
#define CONFIG_DT_HAS_NXP_IMX_USDHC_ENABLED 1
#define CONFIG_DT_HAS_NXP_KINETIS_GPIO_ENABLED 1
#define CONFIG_DT_HAS_NXP_KINETIS_LPUART_ENABLED 1
#define CONFIG_DT_HAS_NXP_KINETIS_PINCTRL_ENABLED 1
#define CONFIG_DT_HAS_NXP_KINETIS_PINMUX_ENABLED 1
#define CONFIG_DT_HAS_NXP_LP_FLEXCOMM_ENABLED 1
#define CONFIG_DT_HAS_NXP_LPC_CTIMER_ENABLED 1
#define CONFIG_DT_HAS_NXP_LPC_LPADC_ENABLED 1
#define CONFIG_DT_HAS_NXP_LPC_SYSCON_ENABLED 1
#define CONFIG_DT_HAS_NXP_LPC_WWDT_ENABLED 1
#define CONFIG_DT_HAS_NXP_LPCMP_ENABLED 1
#define CONFIG_DT_HAS_NXP_LPDAC_ENABLED 1
#define CONFIG_DT_HAS_NXP_LPTMR_ENABLED 1
#define CONFIG_DT_HAS_NXP_MCUX_EDMA_V4_ENABLED 1
#define CONFIG_DT_HAS_NXP_VREF_ENABLED 1
#define CONFIG_DT_HAS_SOC_NV_FLASH_ENABLED 1
#define CONFIG_DT_HAS_ZEPHYR_MEMORY_REGION_ENABLED 1
#define CONFIG_DT_HAS_ZEPHYR_SDMMC_DISK_ENABLED 1
#define CONFIG_ZEPHYR_ACPICA_MODULE 1
#define CONFIG_ZEPHYR_CMSIS_MODULE 1
#define CONFIG_HAS_CMSIS_CORE 1
#define CONFIG_HAS_CMSIS_CORE_M 1
#define CONFIG_ZEPHYR_CMSIS_DSP_MODULE 1
#define CONFIG_ZEPHYR_CMSIS_NN_MODULE 1
#define CONFIG_ZEPHYR_FATFS_MODULE 1
#define CONFIG_ZEPHYR_ADI_MODULE 1
#define CONFIG_ZEPHYR_ALTERA_MODULE 1
#define CONFIG_ZEPHYR_HAL_AMBIQ_MODULE 1
#define CONFIG_ZEPHYR_ATMEL_MODULE 1
#define CONFIG_ZEPHYR_HAL_ESPRESSIF_MODULE 1
#define CONFIG_ZEPHYR_HAL_ETHOS_U_MODULE 1
#define CONFIG_ZEPHYR_HAL_GIGADEVICE_MODULE 1
#define CONFIG_ZEPHYR_HAL_INFINEON_MODULE 1
#define CONFIG_ZEPHYR_HAL_INTEL_MODULE 1
#define CONFIG_ZEPHYR_MICROCHIP_MODULE 1
#define CONFIG_ZEPHYR_HAL_NORDIC_MODULE 1
#define CONFIG_ZEPHYR_NUVOTON_MODULE 1
#define CONFIG_ZEPHYR_HAL_NXP_MODULE 1
#define CONFIG_ZEPHYR_OPENISA_MODULE 1
#define CONFIG_ZEPHYR_QUICKLOGIC_MODULE 1
#define CONFIG_ZEPHYR_HAL_RENESAS_MODULE 1
#define CONFIG_ZEPHYR_HAL_RPI_PICO_MODULE 1
#define CONFIG_ZEPHYR_HAL_SILABS_MODULE 1
#define CONFIG_ZEPHYR_HAL_ST_MODULE 1
#define CONFIG_ZEPHYR_STM32_MODULE 1
#define CONFIG_ZEPHYR_HAL_TELINK_MODULE 1
#define CONFIG_ZEPHYR_TI_MODULE 1
#define CONFIG_ZEPHYR_HAL_WURTHELEKTRONIK_MODULE 1
#define CONFIG_ZEPHYR_XTENSA_MODULE 1
#define CONFIG_ZEPHYR_HOSTAP_MODULE 1
#define CONFIG_ZEPHYR_LIBMETAL_MODULE 1
#define CONFIG_ZEPHYR_LIBLC3_MODULE 1
#define CONFIG_ZEPHYR_LITTLEFS_MODULE 1
#define CONFIG_ZEPHYR_LORAMAC_NODE_MODULE 1
#define CONFIG_ZEPHYR_LVGL_MODULE 1
#define CONFIG_ZEPHYR_MBEDTLS_MODULE 1
#define CONFIG_ZEPHYR_MCUBOOT_MODULE 1
#define CONFIG_ZEPHYR_MIPI_SYS_T_MODULE 1
#define CONFIG_ZEPHYR_NRF_HW_MODELS_MODULE 1
#define CONFIG_ZEPHYR_OPEN_AMP_MODULE 1
#define CONFIG_ZEPHYR_OPENTHREAD_MODULE 1
#define CONFIG_ZEPHYR_PERCEPIO_MODULE 1
#define CONFIG_ZEPHYR_PICOLIBC_MODULE 1
#define CONFIG_ZEPHYR_SEGGER_MODULE 1
#define CONFIG_HAS_SEGGER_RTT 1
#define CONFIG_ZEPHYR_TINYCRYPT_MODULE 1
#define CONFIG_ZEPHYR_TRUSTED_FIRMWARE_M_MODULE 1
#define CONFIG_ZEPHYR_TRUSTED_FIRMWARE_A_MODULE 1
#define CONFIG_ZEPHYR_UOSCORE_UEDHOC_MODULE 1
#define CONFIG_ZEPHYR_ZCBOR_MODULE 1
#define CONFIG_HAS_MCUX 1
#define CONFIG_MCUX_CORE_SUFFIX "_cm33_core0"
#define CONFIG_HAS_MCUX_CACHE 1
#define CONFIG_HAS_MCUX_FLEXCOMM 1
#define CONFIG_BOARD "frdm_mcxn947"
#define CONFIG_BOARD_REVISION ""
#define CONFIG_BOARD_TARGET "frdm_mcxn947/mcxn947/cpu0"
#define CONFIG_BOARD_FRDM_MCXN947 1
#define CONFIG_BOARD_FRDM_MCXN947_MCXN947_CPU0 1
#define CONFIG_BOARD_QUALIFIERS "mcxn947/cpu0"
#define CONFIG_BOARD_INIT_PRIORITY 1
#define CONFIG_SOC_PART_NUMBER "MCXN947VDF"
#define CONFIG_SOC_FAMILY_NXP_MCX 1
#define CONFIG_SOC_SERIES_MCXNX4X 1
#define CONFIG_SOC_MCXN947 1
#define CONFIG_SOC_MCXN947_CPU0 1
#define CONFIG_SOC_PART_NUMBER_MCXN947VDF 1
#define CONFIG_MFD 1
#define CONFIG_GPIO_INIT_PRIORITY 40
#define CONFIG_SOC_LOG_LEVEL_DEFAULT 1
#define CONFIG_SOC_LOG_LEVEL 3
#define CONFIG_ARCH "arm"
#define CONFIG_NET_TX_STACK_SIZE 1200
#define CONFIG_NET_RX_STACK_SIZE 1500
#define CONFIG_ARCH_HAS_SINGLE_THREAD_SUPPORT 1
#define CONFIG_CPU_CORTEX 1
#define CONFIG_KOBJECT_TEXT_AREA 256
#define CONFIG_ARM_MPU 1
#define CONFIG_ARM_MPU_REGION_MIN_ALIGN_AND_SIZE 32
#define CONFIG_CPU_CORTEX_M 1
#define CONFIG_ISA_THUMB2 1
#define CONFIG_ASSEMBLER_ISA_THUMB2 1
#define CONFIG_COMPILER_ISA_THUMB2 1
#define CONFIG_STACK_ALIGN_DOUBLE_WORD 1
#define CONFIG_FAULT_DUMP 2
#define CONFIG_BUILTIN_STACK_GUARD 1
#define CONFIG_ARM_STACK_PROTECTION 1
#define CONFIG_ARM_SECURE_FIRMWARE 1
#define CONFIG_FP16 1
#define CONFIG_FP16_IEEE 1
#define CONFIG_CPU_CORTEX_M33 1
#define CONFIG_CPU_CORTEX_M_HAS_SYSTICK 1
#define CONFIG_CPU_CORTEX_M_HAS_DWT 1
#define CONFIG_CPU_CORTEX_M_HAS_BASEPRI 1
#define CONFIG_CPU_CORTEX_M_HAS_VTOR 1
#define CONFIG_CPU_CORTEX_M_HAS_SPLIM 1
#define CONFIG_CPU_CORTEX_M_HAS_PROGRAMMABLE_FAULT_PRIOS 1
#define CONFIG_CPU_CORTEX_M_HAS_CMSE 1
#define CONFIG_ARMV7_M_ARMV8_M_MAINLINE 1
#define CONFIG_ARMV8_M_MAINLINE 1
#define CONFIG_ARMV8_M_SE 1
#define CONFIG_ARMV7_M_ARMV8_M_FP 1
#define CONFIG_ARMV8_M_DSP 1
#define CONFIG_NULL_POINTER_EXCEPTION_DETECTION_NONE 1
#define CONFIG_ARM_TRUSTZONE_M 1
#define CONFIG_CUSTOM_SECTION_MIN_ALIGN_SIZE 32
#define CONFIG_CPU_HAS_ARM_SAU 1
#define CONFIG_ARM 1
#define CONFIG_ARCH_IS_SET 1
#define CONFIG_ARCH_LOG_LEVEL_DEFAULT 1
#define CONFIG_ARCH_LOG_LEVEL 3
#define CONFIG_LITTLE_ENDIAN 1
#define CONFIG_SRAM_SIZE 320
#define CONFIG_SRAM_BASE_ADDRESS 0x30000000
#define CONFIG_TRUSTED_EXECUTION_SECURE 1
#define CONFIG_KOBJECT_DATA_AREA_RESERVE_EXTRA_PERCENT 100
#define CONFIG_KOBJECT_RODATA_AREA_EXTRA_BYTES 16
#define CONFIG_GEN_PRIV_STACKS 1
#define CONFIG_ISR_TABLES_LOCAL_DECLARATION_SUPPORTED 1
#define CONFIG_IRQ_VECTOR_TABLE_JUMP_BY_ADDRESS 1
#define CONFIG_EXCEPTION_DEBUG 1
#define CONFIG_ARCH_HAS_TIMING_FUNCTIONS 1
#define CONFIG_ARCH_HAS_TRUSTED_EXECUTION 1
#define CONFIG_ARCH_HAS_STACK_PROTECTION 1
#define CONFIG_ARCH_HAS_USERSPACE 1
#define CONFIG_ARCH_HAS_EXECUTABLE_PAGE_BIT 1
#define CONFIG_ARCH_HAS_RAMFUNC_SUPPORT 1
#define CONFIG_ARCH_HAS_NESTED_EXCEPTION_DETECTION 1
#define CONFIG_ARCH_SUPPORTS_COREDUMP 1
#define CONFIG_ARCH_SUPPORTS_ARCH_HW_INIT 1
#define CONFIG_ARCH_SUPPORTS_ROM_START 1
#define CONFIG_ARCH_HAS_EXTRA_EXCEPTION_INFO 1
#define CONFIG_ARCH_HAS_THREAD_LOCAL_STORAGE 1
#define CONFIG_ARCH_HAS_SUSPEND_TO_RAM 1
#define CONFIG_ARCH_HAS_THREAD_ABORT 1
#define CONFIG_ARCH_HAS_CODE_DATA_RELOCATION 1
#define CONFIG_CPU_HAS_TEE 1
#define CONFIG_CPU_HAS_FPU 1
#define CONFIG_CPU_HAS_MPU 1
#define CONFIG_MPU 1
#define CONFIG_MPU_LOG_LEVEL_DEFAULT 1
#define CONFIG_MPU_LOG_LEVEL 3
#define CONFIG_MPU_REQUIRES_NON_OVERLAPPING_REGIONS 1
#define CONFIG_MPU_GAP_FILLING 1
#define CONFIG_SRAM_REGION_PERMISSIONS 1
#define CONFIG_TOOLCHAIN_HAS_BUILTIN_FFS 1
#define CONFIG_KERNEL_LOG_LEVEL_DEFAULT 1
#define CONFIG_KERNEL_LOG_LEVEL 3
#define CONFIG_MULTITHREADING 1
#define CONFIG_NUM_COOP_PRIORITIES 16
#define CONFIG_NUM_PREEMPT_PRIORITIES 15
#define CONFIG_MAIN_THREAD_PRIORITY 0
#define CONFIG_COOP_ENABLED 1
#define CONFIG_PREEMPT_ENABLED 1
#define CONFIG_PRIORITY_CEILING -127
#define CONFIG_NUM_METAIRQ_PRIORITIES 0
#define CONFIG_THREAD_STACK_INFO 1
#define CONFIG_SCHED_DUMB 1
#define CONFIG_WAITQ_DUMB 1
#define CONFIG_LIBC_ERRNO 1
#define CONFIG_ERRNO 1
#define CONFIG_CURRENT_THREAD_USE_TLS 1
#define CONFIG_INIT_STACKS 1
#define CONFIG_BOOT_BANNER 1
#define CONFIG_BOOT_BANNER_STRING "Booting Zephyr OS build"
#define CONFIG_BOOT_DELAY 0
#define CONFIG_THREAD_MONITOR 1
#define CONFIG_THREAD_NAME 1
#define CONFIG_THREAD_MAX_NAME_LEN 32
#define CONFIG_SYSTEM_WORKQUEUE_PRIORITY -1
#define CONFIG_BARRIER_OPERATIONS_ARCH 1
#define CONFIG_ATOMIC_OPERATIONS_BUILTIN 1
#define CONFIG_TIMESLICING 1
#define CONFIG_TIMESLICE_SIZE 0
#define CONFIG_TIMESLICE_PRIORITY 0
#define CONFIG_POLL 1
#define CONFIG_NUM_MBOX_ASYNC_MSGS 10
#define CONFIG_KERNEL_MEM_POOL 1
#define CONFIG_ARCH_HAS_CUSTOM_SWAP_TO_MAIN 1
#define CONFIG_SWAP_NONATOMIC 1
#define CONFIG_SYS_CLOCK_EXISTS 1
#define CONFIG_TIMEOUT_64BIT 1
#define CONFIG_SYS_CLOCK_MAX_TIMEOUT_DAYS 365
#define CONFIG_STACK_POINTER_RANDOM 0
#define CONFIG_ARCH_MEM_DOMAIN_SUPPORTS_ISOLATED_STACKS 1
#define CONFIG_MEM_DOMAIN_ISOLATED_STACKS 1
#define CONFIG_MP_NUM_CPUS 1
#define CONFIG_TOOLCHAIN_SUPPORTS_THREAD_LOCAL_STORAGE 1
#define CONFIG_THREAD_LOCAL_STORAGE 1
#define CONFIG_TOOLCHAIN_SUPPORTS_STATIC_INIT_GNU 1
#define CONFIG_KERNEL_INIT_PRIORITY_OBJECTS 30
#define CONFIG_KERNEL_INIT_PRIORITY_LIBC 35
#define CONFIG_KERNEL_INIT_PRIORITY_DEFAULT 40
#define CONFIG_KERNEL_INIT_PRIORITY_DEVICE 50
#define CONFIG_APPLICATION_INIT_PRIORITY 90
#define CONFIG_CLOCK_CONTROL_LOG_LEVEL_DEFAULT 1
#define CONFIG_CLOCK_CONTROL_LOG_LEVEL 3
#define CONFIG_CLOCK_CONTROL_MCUX_SYSCON 1
#define CONFIG_CONSOLE_INPUT_MAX_LINE_LEN 128
#define CONFIG_CONSOLE_HAS_DRIVER 1
#define CONFIG_CONSOLE_INIT_PRIORITY 60
#define CONFIG_UART_CONSOLE 1
#define CONFIG_UART_CONSOLE_LOG_LEVEL_DEFAULT 1
#define CONFIG_UART_CONSOLE_LOG_LEVEL 3
#define CONFIG_ENTROPY_GENERATOR 1
#define CONFIG_ENTROPY_LOG_LEVEL_DEFAULT 1
#define CONFIG_ENTROPY_LOG_LEVEL 3
#define CONFIG_ETH_DRIVER 1
#define CONFIG_ETHERNET_LOG_LEVEL_DEFAULT 1
#define CONFIG_ETHERNET_LOG_LEVEL 3
#define CONFIG_ETH_NXP_ENET_QOS 1
#define CONFIG_ETH_NXP_ENET_QOS_MAC 1
#define CONFIG_ETH_NXP_ENET_QOS_TX_BUFFER_DESCRIPTORS 4
#define CONFIG_ETH_NXP_ENET_QOS_RX_BUFFER_DESCRIPTORS 4
#define CONFIG_ETH_NXP_ENET_QOS_DMA_RESET_WAIT_TIME 10
#define CONFIG_ETH_NXP_ENET_QOS_RX_THREAD_STACK_SIZE 1024
#define CONFIG_ETH_NXP_ENET_QOS_RX_THREAD_PRIORITY 3
#define CONFIG_ETH_PHY_DRIVER 1
#define CONFIG_PHY_LOG_LEVEL_DEFAULT 1
#define CONFIG_PHY_LOG_LEVEL 3
#define CONFIG_PHY_GENERIC_MII 1
#define CONFIG_PHY_AUTONEG_TIMEOUT_MS 4000
#define CONFIG_PHY_MONITOR_PERIOD 500
#define CONFIG_ETH_INIT_PRIORITY 80
#define CONFIG_GPIO_LOG_LEVEL_DEFAULT 1
#define CONFIG_GPIO_LOG_LEVEL 3
#define CONFIG_GPIO_MCUX 1
#define CONFIG_INTC_INIT_PRIORITY 40
#define CONFIG_INTC_LOG_LEVEL_DEFAULT 1
#define CONFIG_INTC_LOG_LEVEL 3
#define CONFIG_MDIO 1
#define CONFIG_MDIO_NXP_ENET_QOS 1
#define CONFIG_MDIO_NXP_ENET_QOS_RECHECK_COUNT 3
#define CONFIG_MDIO_NXP_ENET_QOS_RECHECK_TIME 100
#define CONFIG_MDIO_INIT_PRIORITY 60
#define CONFIG_MDIO_LOG_LEVEL_DEFAULT 1
#define CONFIG_MDIO_LOG_LEVEL 3
#define CONFIG_MFD_LOG_LEVEL_DEFAULT 1
#define CONFIG_MFD_LOG_LEVEL 3
#define CONFIG_MFD_INIT_PRIORITY 80
#define CONFIG_NXP_LP_FLEXCOMM 1
#define CONFIG_PINCTRL_LOG_LEVEL_DEFAULT 1
#define CONFIG_PINCTRL_LOG_LEVEL 3
#define CONFIG_PINCTRL_NXP_KINETIS 1
#define CONFIG_SERIAL_HAS_DRIVER 1
#define CONFIG_SERIAL_SUPPORT_ASYNC 1
#define CONFIG_SERIAL_SUPPORT_INTERRUPT 1
#define CONFIG_UART_LOG_LEVEL_DEFAULT 1
#define CONFIG_UART_LOG_LEVEL 3
#define CONFIG_UART_MCUX_LPUART 1
#define CONFIG_UART_MCUX_LPUART_ISR_SUPPORT 1
#define CONFIG_TIMER_HAS_64BIT_CYCLE_COUNTER 1
#define CONFIG_SYSTEM_CLOCK_INIT_PRIORITY 0
#define CONFIG_TICKLESS_CAPABLE 1
#define CONFIG_SYSTEM_TIMER_HAS_DISABLE_SUPPORT 1
#define CONFIG_CORTEX_M_SYSTICK_INSTALL_ISR 1
#define CONFIG_CORTEX_M_SYSTICK_64BIT_CYCLE_COUNTER 1
#define CONFIG_NRF_USBD_COMMON_LOG_LEVEL_DEFAULT 1
#define CONFIG_NRF_USBD_COMMON_LOG_LEVEL 3
#define CONFIG_USBC_LOG_LEVEL_DEFAULT 1
#define CONFIG_USBC_LOG_LEVEL 3
#define CONFIG_NET_MGMT_EVENT_STACK_SIZE 800
#define CONFIG_REQUIRES_FLOAT_PRINTF 1
#define CONFIG_FULL_LIBC_SUPPORTED 1
#define CONFIG_MINIMAL_LIBC_SUPPORTED 1
#define CONFIG_NEWLIB_LIBC_SUPPORTED 1
#define CONFIG_PICOLIBC_SUPPORTED 1
#define CONFIG_PICOLIBC 1
#define CONFIG_HAS_NEWLIB_LIBC_NANO 1
#define CONFIG_COMMON_LIBC_ABORT 1
#define CONFIG_COMMON_LIBC_MALLOC 1
#define CONFIG_COMMON_LIBC_CALLOC 1
#define CONFIG_COMMON_LIBC_REALLOCARRAY 1
#define CONFIG_PICOLIBC_USE_TOOLCHAIN 1
#define CONFIG_PICOLIBC_IO_FLOAT 1
#define CONFIG_STDOUT_CONSOLE 1
#define CONFIG_NEED_LIBC_MEM_PARTITION 1
#define CONFIG_CRC 1
#define CONFIG_SYS_HEAP_ALLOC_LOOPS 3
#define CONFIG_SYS_HEAP_AUTO 1
#define CONFIG_FDTABLE 1
#define CONFIG_ZVFS_OPEN_MAX 4
#define CONFIG_MPSC_PBUF 1
#define CONFIG_CBPRINTF_COMPLETE 1
#define CONFIG_CBPRINTF_FULL_INTEGRAL 1
#define CONFIG_CBPRINTF_PACKAGE_LOG_LEVEL_DEFAULT 1
#define CONFIG_CBPRINTF_PACKAGE_LOG_LEVEL 3
#define CONFIG_CBPRINTF_CONVERT_CHECK_PTR 1
#define CONFIG_ZVFS 1
#define CONFIG_ZVFS_EVENTFD 1
#define CONFIG_ZVFS_EVENTFD_MAX 1
#define CONFIG_POSIX_AEP_CHOICE_NONE 1
#define CONFIG_POSIX_C_LIB_EXT 1
#define CONFIG_POSIX_OPEN_MAX 4
#define CONFIG_POSIX_PAGE_SIZE 0x40
#define CONFIG_EVENTFD 1
#define CONFIG_EVENTFD_MAX 1
#define CONFIG_MAX_PTHREAD_COUNT 0
#define CONFIG_MAX_PTHREAD_KEY_COUNT 0
#define CONFIG_MAX_TIMER_COUNT 0
#define CONFIG_MSG_COUNT_MAX 0
#define CONFIG_POSIX_LIMITS_RTSIG_MAX 0
#define CONFIG_POSIX_MAX_FDS 4
#define CONFIG_POSIX_MAX_OPEN_FILES 4
#define CONFIG_TIMER_DELAYTIMER_MAX 0
#define CONFIG_SEM_NAMELEN_MAX 0
#define CONFIG_SEM_VALUE_MAX 0
#define CONFIG_LIBGCC_RTLIB 1
#define CONFIG_RING_BUFFER 1
#define CONFIG_PRINTK 1
#define CONFIG_EARLY_CONSOLE 1
#define CONFIG_ASSERT_VERBOSE 1
#define CONFIG_LLEXT_EDK_NAME "llext-edk"
#define CONFIG_LOG_CORE_INIT_PRIORITY 0
#define CONFIG_LOG_MODE_DEFERRED 1
#define CONFIG_LOG_RUNTIME_FILTERING 1
#define CONFIG_LOG_DEFAULT_LEVEL 3
#define CONFIG_LOG_OVERRIDE_LEVEL 0
#define CONFIG_LOG_MAX_LEVEL 4
#define CONFIG_LOG_PRINTK 1
#define CONFIG_LOG_MODE_OVERFLOW 1
#define CONFIG_LOG_PROCESS_TRIGGER_THRESHOLD 10
#define CONFIG_LOG_PROCESS_THREAD 1
#define CONFIG_LOG_PROCESS_THREAD_STARTUP_DELAY_MS 0
#define CONFIG_LOG_PROCESS_THREAD_SLEEP_MS 1000
#define CONFIG_LOG_PROCESS_THREAD_STACK_SIZE 768
#define CONFIG_LOG_BUFFER_SIZE 1024
#define CONFIG_LOG_TRACE_SHORT_TIMESTAMP 1
#define CONFIG_LOG_FUNC_NAME_PREFIX_DBG 1
#define CONFIG_LOG_TAG_MAX_LEN 0
#define CONFIG_LOG_USE_VLA 1
#define CONFIG_LOG_SIMPLE_MSG_OPTIMIZE 1
#define CONFIG_LOG_FAILURE_REPORT_PERIOD 1000
#define CONFIG_LOG_OUTPUT 1
#define CONFIG_MEM_ATTR 1
#define CONFIG_NET_BUF 1
#define CONFIG_NET_BUF_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_BUF_LOG_LEVEL 3
#define CONFIG_NET_BUF_ALIGNMENT 0
#define CONFIG_NETWORKING 1
#define CONFIG_NET_L2_ETHERNET_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_L2_ETHERNET_LOG_LEVEL 3
#define CONFIG_NET_ARP 1
#define CONFIG_NET_ARP_TABLE_SIZE 2
#define CONFIG_NET_ARP_GRATUITOUS 1
#define CONFIG_NET_ARP_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_ARP_LOG_LEVEL 3
#define CONFIG_NET_IP 1
#define CONFIG_NET_NATIVE 1
#define CONFIG_NET_NATIVE_IP 1
#define CONFIG_NET_NATIVE_IPV4 1
#define CONFIG_NET_NATIVE_UDP 1
#define CONFIG_NET_INIT_PRIO 90
#define CONFIG_NET_IP_DSCP_ECN 1
#define CONFIG_NET_IPV4 1
#define CONFIG_NET_INITIAL_TTL 64
#define CONFIG_NET_INITIAL_MCAST_TTL 1
#define CONFIG_NET_IF_MAX_IPV4_COUNT 1
#define CONFIG_NET_IF_UNICAST_IPV4_ADDR_COUNT 1
#define CONFIG_NET_IF_MCAST_IPV4_ADDR_COUNT 2
#define CONFIG_NET_IF_MCAST_IPV4_SOURCE_COUNT 1
#define CONFIG_NET_IPV4_IGMP 1
#define CONFIG_NET_IPV4_HDR_OPTIONS 1
#define CONFIG_NET_IPV4_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_IPV4_LOG_LEVEL 3
#define CONFIG_NET_ICMPV4_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_ICMPV4_LOG_LEVEL 3
#define CONFIG_NET_IPV4_ACD_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_IPV4_ACD_LOG_LEVEL 3
#define CONFIG_NET_SHELL 1
#define CONFIG_NET_SHELL_DYN_CMD_COMPLETION 1
#define CONFIG_NET_TC_TX_COUNT 0
#define CONFIG_NET_TC_RX_COUNT 1
#define CONFIG_NET_TC_THREAD_COOPERATIVE 1
#define CONFIG_NET_TC_NUM_PRIORITIES 16
#define CONFIG_NET_TC_MAPPING_STRICT 1
#define CONFIG_NET_TX_DEFAULT_PRIORITY 1
#define CONFIG_NET_RX_DEFAULT_PRIORITY 0
#define CONFIG_NET_IP_ADDR_CHECK 1
#define CONFIG_NET_MAX_ROUTERS 1
#define CONFIG_NET_UDP 1
#define CONFIG_NET_UDP_MISSING_CHECKSUM 1
#define CONFIG_NET_UDP_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_UDP_LOG_LEVEL 3
#define CONFIG_NET_MAX_CONN 4
#define CONFIG_NET_MAX_CONTEXTS 6
#define CONFIG_NET_CONTEXT_SYNC_RECV 1
#define CONFIG_NET_CONTEXT_CHECK 1
#define CONFIG_NET_CONTEXT_DSCP_ECN 1
#define CONFIG_NET_CONTEXT_REUSEADDR 1
#define CONFIG_NET_CONTEXT_REUSEPORT 1
#define CONFIG_NET_PKT_RX_COUNT 14
#define CONFIG_NET_PKT_TX_COUNT 14
#define CONFIG_NET_BUF_RX_COUNT 36
#define CONFIG_NET_BUF_TX_COUNT 36
#define CONFIG_NET_BUF_FIXED_DATA_SIZE 1
#define CONFIG_NET_BUF_DATA_SIZE 128
#define CONFIG_NET_PKT_BUF_USER_DATA_SIZE 4
#define CONFIG_NET_DEFAULT_IF_FIRST 1
#define CONFIG_NET_INTERFACE_NAME 1
#define CONFIG_NET_INTERFACE_NAME_LEN 8
#define CONFIG_NET_MGMT 1
#define CONFIG_NET_MGMT_EVENT 1
#define CONFIG_NET_MGMT_EVENT_THREAD 1
#define CONFIG_NET_MGMT_EVENT_QUEUE 1
#define CONFIG_NET_MGMT_EVENT_QUEUE_SIZE 5
#define CONFIG_NET_MGMT_EVENT_QUEUE_TIMEOUT 10
#define CONFIG_NET_MGMT_EVENT_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_MGMT_EVENT_LOG_LEVEL 3
#define CONFIG_NET_LOG 1
#define CONFIG_NET_PKT_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_PKT_LOG_LEVEL 3
#define CONFIG_NET_DEBUG_NET_PKT_EXTERNALS 0
#define CONFIG_NET_CORE_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_CORE_LOG_LEVEL 3
#define CONFIG_NET_IF_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_IF_LOG_LEVEL 3
#define CONFIG_NET_TC_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_TC_LOG_LEVEL 3
#define CONFIG_NET_UTILS_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_UTILS_LOG_LEVEL 3
#define CONFIG_NET_CONTEXT_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_CONTEXT_LOG_LEVEL 3
#define CONFIG_NET_CONN_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_CONN_LOG_LEVEL 3
#define CONFIG_NET_ROUTE_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_ROUTE_LOG_LEVEL 3
#define CONFIG_DNS_RESOLVER 1
#define CONFIG_DNS_RESOLVER_AUTO_INIT 1
#define CONFIG_DNS_RESOLVER_ADDITIONAL_QUERIES 1
#define CONFIG_DNS_RESOLVER_AI_MAX_ENTRIES 2
#define CONFIG_DNS_RESOLVER_MAX_SERVERS 1
#define CONFIG_DNS_RESOLVER_MAX_QUERY_LEN 255
#define CONFIG_DNS_NUM_CONCUR_QUERIES 1
#define CONFIG_DNS_RESOLVER_LOG_LEVEL_DEFAULT 1
#define CONFIG_DNS_RESOLVER_LOG_LEVEL 3
#define CONFIG_DNS_SOCKET_DISPATCHER 1
#define CONFIG_DNS_RESOLVER_ADDITIONAL_BUF_CTR 1
#define CONFIG_DNS_SOCKET_DISPATCHER_LOG_LEVEL_DEFAULT 1
#define CONFIG_DNS_SOCKET_DISPATCHER_LOG_LEVEL 3
#define CONFIG_NET_HTTP_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_HTTP_LOG_LEVEL 3
#define CONFIG_NET_HTTP_SERVER_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_HTTP_SERVER_LOG_LEVEL 3
#define CONFIG_NET_CONFIG_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_CONFIG_LOG_LEVEL 3
#define CONFIG_NET_SOCKETS 1
#define CONFIG_NET_SOCKETS_PRIORITY_DEFAULT 50
#define CONFIG_NET_SOCKETS_POLL_MAX 3
#define CONFIG_NET_SOCKETS_CONNECT_TIMEOUT 3000
#define CONFIG_NET_SOCKETS_DNS_TIMEOUT 2000
#define CONFIG_NET_SOCKETS_DNS_BACKOFF_INTERVAL 5000
#define CONFIG_NET_SOCKET_MAX_SEND_WAIT 10000
#define CONFIG_NET_SOCKETS_SERVICE 1
#define CONFIG_NET_SOCKETS_SERVICE_THREAD_PRIO 15
#define CONFIG_NET_SOCKETS_SERVICE_STACK_SIZE 1200
#define CONFIG_NET_SOCKETS_TLS_PRIORITY 45
#define CONFIG_NET_SOCKETS_TLS_SET_MAX_FRAGMENT_LENGTH 1
#define CONFIG_NET_SOCKETS_OFFLOAD_PRIORITY 40
#define CONFIG_NET_SOCKETS_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_SOCKETS_LOG_LEVEL 3
#define CONFIG_NET_DHCPV4 1
#define CONFIG_NET_DHCPV4_LOG_LEVEL_DEFAULT 1
#define CONFIG_NET_DHCPV4_LOG_LEVEL 3
#define CONFIG_NET_DHCPV4_INITIAL_DELAY_MAX 10
#define CONFIG_NET_DHCPV4_OPTION_CALLBACKS 1
#define CONFIG_NET_DHCPV4_MAX_REQUESTED_OPTIONS 10
#define CONFIG_NET_DHCPV4_ACCEPT_UNICAST 1
#define CONFIG_NET_DHCPV6_DUID_MAX_LEN 22
#define CONFIG_TEST_RANDOM_GENERATOR 1
#define CONFIG_TIMER_RANDOM_INITIAL_STATE 123456789
#define CONFIG_TIMER_RANDOM_GENERATOR 1
#define CONFIG_SHELL 1
#define CONFIG_SHELL_LOG_LEVEL_DEFAULT 1
#define CONFIG_SHELL_LOG_LEVEL 3
#define CONFIG_SHELL_BACKENDS 1
#define CONFIG_SHELL_BACKEND_SERIAL 1
#define CONFIG_SHELL_BACKEND_SERIAL_INIT_PRIORITY 90
#define CONFIG_SHELL_PROMPT_UART "uart:~$ "
#define CONFIG_SHELL_BACKEND_SERIAL_INTERRUPT_DRIVEN 1
#define CONFIG_SHELL_BACKEND_SERIAL_API_INTERRUPT_DRIVEN 1
#define CONFIG_SHELL_BACKEND_SERIAL_TX_RING_BUFFER_SIZE 8
#define CONFIG_SHELL_BACKEND_SERIAL_RX_RING_BUFFER_SIZE 64
#define CONFIG_SHELL_BACKEND_SERIAL_LOG_MESSAGE_QUEUE_TIMEOUT 100
#define CONFIG_SHELL_BACKEND_SERIAL_LOG_MESSAGE_QUEUE_SIZE 512
#define CONFIG_SHELL_BACKEND_SERIAL_LOG_LEVEL_DEFAULT 1
#define CONFIG_SHELL_BACKEND_SERIAL_LOG_LEVEL 5
#define CONFIG_SHELL_STACK_SIZE 2048
#define CONFIG_SHELL_BACKSPACE_MODE_DELETE 1
#define CONFIG_SHELL_PROMPT_CHANGE 1
#define CONFIG_SHELL_PROMPT_BUFF_SIZE 20
#define CONFIG_SHELL_CMD_BUFF_SIZE 256
#define CONFIG_SHELL_PRINTF_BUFF_SIZE 30
#define CONFIG_SHELL_DEFAULT_TERMINAL_WIDTH 80
#define CONFIG_SHELL_DEFAULT_TERMINAL_HEIGHT 24
#define CONFIG_SHELL_ARGC_MAX 20
#define CONFIG_SHELL_TAB 1
#define CONFIG_SHELL_TAB_AUTOCOMPLETION 1
#define CONFIG_SHELL_ASCII_FILTER 1
#define CONFIG_SHELL_WILDCARD 1
#define CONFIG_SHELL_MSG_CMD_NOT_FOUND 1
#define CONFIG_SHELL_MSG_SPECIFY_SUBCOMMAND 1
#define CONFIG_SHELL_ECHO_STATUS 1
#define CONFIG_SHELL_VT100_COMMANDS 1
#define CONFIG_SHELL_VT100_COLORS 1
#define CONFIG_SHELL_METAKEYS 1
#define CONFIG_SHELL_HELP 1
#define CONFIG_SHELL_HELP_OPT_PARSE 1
#define CONFIG_SHELL_HELP_ON_WRONG_ARGUMENT_COUNT 1
#define CONFIG_SHELL_HISTORY 1
#define CONFIG_SHELL_HISTORY_BUFFER 512
#define CONFIG_SHELL_STATS 1
#define CONFIG_SHELL_CMDS 1
#define CONFIG_SHELL_CMDS_RESIZE 1
#define CONFIG_SHELL_CMD_ROOT ""
#define CONFIG_SHELL_LOG_BACKEND 1
#define CONFIG_SHELL_LOG_FORMAT_TIMESTAMP 1
#define CONFIG_SHELL_AUTOSTART 1
#define CONFIG_SHELL_CMDS_RETURN_VALUE 1
#define CONFIG_KERNEL_SHELL 1
#define CONFIG_DEVICE_SHELL 1
#define CONFIG_DEVMEM_SHELL 1
#define CONFIG_TOOLCHAIN_ZEPHYR_0_16 1
#define CONFIG_TOOLCHAIN_ZEPHYR_SUPPORTS_THREAD_LOCAL_STORAGE 1
#define CONFIG_LINKER_ORPHAN_SECTION_WARN 1
#define CONFIG_FLASH_LOAD_SIZE 0x0
#define CONFIG_ROM_END_OFFSET 0x0
#define CONFIG_LD_LINKER_SCRIPT_SUPPORTED 1
#define CONFIG_LD_LINKER_TEMPLATE 1
#define CONFIG_LINKER_SORT_BY_ALIGNMENT 1
#define CONFIG_LINKER_GENERIC_SECTIONS_PRESENT_AT_BOOT 1
#define CONFIG_LINKER_LAST_SECTION_ID 1
#define CONFIG_LINKER_LAST_SECTION_ID_PATTERN 0xE015E015
#define CONFIG_LINKER_USE_RELAX 1
#define CONFIG_LINKER_ITERABLE_SUBALIGN 4
#define CONFIG_LINKER_DEVNULL_SUPPORT 1
#define CONFIG_STD_C99 1
#define CONFIG_TOOLCHAIN_SUPPORTS_GNU_EXTENSIONS 1
#define CONFIG_SIZE_OPTIMIZATIONS 1
#define CONFIG_COMPILER_TRACK_MACRO_EXPANSION 1
#define CONFIG_COMPILER_COLOR_DIAGNOSTICS 1
#define CONFIG_FORTIFY_SOURCE_COMPILE_TIME 1
#define CONFIG_COMPILER_OPT ""
#define CONFIG_RUNTIME_ERROR_CHECKS 1
#define CONFIG_KERNEL_BIN_NAME "zephyr"
#define CONFIG_OUTPUT_STAT 1
#define CONFIG_OUTPUT_PRINT_MEMORY_USAGE 1
#define CONFIG_BUILD_OUTPUT_STRIP_PATHS 1
#define CONFIG_CHECK_INIT_PRIORITIES 1
#define CONFIG_WARN_DEPRECATED 1
#define CONFIG_EXPERIMENTAL 1
#define CONFIG_ENFORCE_ZEPHYR_STDINT 1
#define CONFIG_LEGACY_GENERATED_INCLUDE_PATH 1
