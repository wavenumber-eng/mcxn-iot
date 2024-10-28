#include "stdint.h"

#pragma once

#ifndef _EZH_APP_H
#define _EZH_APP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint32_t command;
    uint32_t * data_buffer;
    uint32_t data_buffer_length;
    uint32_t target_address;

} EZH_CMD_PROCESSOR_PARAMS;

typedef struct _EZHPWM_Para
{
    void  *coprocessor_stack;
    uint32_t *p_buffer;
} EZHPWM_Para;

extern EZHPWM_Para ezh_parameters;

void ezh_app(void);

void ezh__start_app();

void ezh__send_cmd(uint32_t cmd);

void ezh__execute_command(uint8_t cmd);

#ifdef __cplusplus
}
#endif

#endif

