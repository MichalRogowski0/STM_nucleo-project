#include "logger.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static UART_HandleTypeDef *g_uart = NULL;

static const char *logger_level_prefix(log_type level) {

  switch(level) {
    case LOG_TYPE_DEBUG: return "[DBG]";
    case LOG_TYPE_ERROR: return "[ERR]";
    case LOG_TYPE_INFO: return "[INF]";
    case LOG_TYPE_WARN: return "[WRN]";
    default: return "[UNK]";
  }
}

void logger_init(UART_HandleTypeDef *huart)
{
  g_uart = huart;
}

void logger_log(log_type log, const char *format, ...)
{
  if ((g_uart == NULL) || (format == NULL)) {
    return;
  }

  const char *prefix = logger_level_prefix(log);
  
  char buffer[128];
  int prefix_len = snprintf(buffer, sizeof(buffer), "%s", prefix);
  va_list args;
  va_start(args, format);
  int len = vsnprintf(buffer + prefix_len , sizeof(buffer) - prefix_len, format, args);
  va_end(args);

  if (len <= 0){
    return;
  }

  HAL_UART_Transmit(g_uart, (uint8_t *)buffer, (uint16_t)strlen(buffer), 100);
}
