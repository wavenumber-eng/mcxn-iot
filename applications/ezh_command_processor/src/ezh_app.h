#include "stdint.h"

#pragma once

#ifndef _EZH_APP_H
#define _EZH_APP_H

#ifdef __cplusplus
extern "C" {
#endif

#define SPI_RD_MAX_LENGTH   128

typedef struct
{
    uint32_t cmd_and_addr;          // (cmd(8bits) << 24) | add(24bits)
    uint32_t data_buffer_length;
    uint32_t * data_buffer;
} EZH_spi_wr_params_t;

typedef struct
{
    uint32_t cmd_and_addr;          // (cmd(8bits) << 24) | add(24bits)
    uint32_t wait_cycles;
    uint32_t rx_buffer_length;
    uint32_t * rx_buffer_ptr;

} EZH_spi_rd_params_t;


typedef struct _EZHPWM_Para
{
    void  *coprocessor_stack;
    uint32_t *p_buffer;
} EZHPWM_Para;

typedef enum
{
    TOGGLE1_APP,
    TOGGLE2_APP,
    SPI_WRITE_APP,
    SPI_READ_APP,

    EZH_APP_QTY,
} ezh_applications_e;


void ezh_app(void);
void ezh__start_app();
void ezh__execute_command(uint8_t cmd, EZHPWM_Para * ezh_parameters);

#ifdef __cplusplus
}
#endif

#endif

