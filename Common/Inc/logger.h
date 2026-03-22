#pragma once

#include "main.h"

typedef enum log_type
{
    LOG_TYPE_ERROR,
    LOG_TYPE_WARN,
    LOG_TYPE_DEBUG,
    LOG_TYPE_INFO
} log_type;

void logger_init(UART_HandleTypeDef *huart);
void logger_log(log_type log, const char *format, ...);
