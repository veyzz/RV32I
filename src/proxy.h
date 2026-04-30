#ifndef __PROXY_H__
#define __PROXY_H__

#include <stdint.h>

enum
{
  PROXY_CONTINUE,
  PROXY_EXIT
};

int proxy_ecall (int32_t *exit_code);

#endif /* __PROXY_H__ */
