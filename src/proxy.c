#include <stdint.h>
#include <stdio.h>
#include "memory.h"
#include "proxy.h"

int
proxy_ecall (int32_t *exit_code)
{
  uint32_t const sysno = reg_gp[REG_X17];

  switch (sysno)
    {
      case 64: /* write */
        {
          uint32_t const fd = reg_gp[REG_X10];
          uint32_t const addr = reg_gp[REG_X11];
          uint32_t const len = reg_gp[REG_X12];
          FILE *stream;
          uint32_t i;
          int fault = 0;
          size_t nw;

          if (fd == 1U)
            stream = stdout;
          else if (fd == 2U)
            stream = stderr;
          else
            {
              reg_gp[REG_X10] = (uint32_t)-9; /* -EBADF */
              reg_pc[0] += 4U;
              return PROXY_CONTINUE;
            }

          for (i = 0; i < len; i++)
            {
              if (!ADDR_IS_VALID (addr + i))
                {
                  fault = 1;
                  break;
                }
            }
          if (fault)
            {
              reg_gp[REG_X10] = (uint32_t)-14; /* -EFAULT */
              reg_pc[0] += 4U;
              return PROXY_CONTINUE;
            }

          nw = fwrite (memory + ADDR_TO_IDX (addr), 1, len, stream);
          fflush (stream);
          reg_gp[REG_X10] = (uint32_t)nw;
          reg_pc[0] += 4U;
          return PROXY_CONTINUE;
        }

      case 93: /* exit */
        *exit_code = (int32_t)reg_gp[REG_X10];
        return PROXY_EXIT;

      default:
        reg_gp[REG_X10] = (uint32_t)-38; /* -ENOSYS */
        reg_pc[0] += 4U;
        return PROXY_CONTINUE;
    }
}
