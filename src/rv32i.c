#include <stdint.h>
#include <stdio.h>
#include "memory.h"
#include "hart.h"
#include "proxy.h"

int
main (int argc, char const **argv)
{
  int32_t exit_code;
  int fetch_ret;
  int proxy_action;

  if (argc != 2 && argc != 3)
    {
      printf ("Usage: %s image.bin [pc]\n"
              "  image.bin - path to flat memory image\n"
              "  pc        - optional start PC (default: 0x80000000)\n",
              argv[0]);
      return -1;
    }

  if (mem_init (argv[1]) < 0)
    {
      printf ("failed to read memory\n");
      return -1;
    }

  reg_pc[0] = MEMBASE;
  if (argc == 3 && sscanf (argv[2], "%x", reg_pc) != 1)
    {
      printf ("failed to get PC\n");
      return -1;
    }

  while (1)
    {
      if (!ADDR_IS_VALID (reg_pc[0]))
        {
          printf ("stop: PC out of bounds (0x%08x)\n", reg_pc[0]);
          break;
        }

      fetch_ret = fetch (memory + ADDR_TO_IDX (reg_pc[0]));
      if (fetch_ret != FETCH_OK)
        {
          switch (fetch_ret)
            {
              case FETCH_TRAP_ECALL:
                proxy_action = proxy_ecall (&exit_code);
                if (proxy_action == PROXY_CONTINUE)
                  continue;
                printf ("stop: proxy exit code=%d at PC=0x%08x\n", exit_code,
                        reg_pc[0]);
                break;

              case FETCH_TRAP_EBREAK:
                printf ("stop: trap ebreak at PC=0x%08x\n", reg_pc[0]);
                break;

              case FETCH_FAULT:
                printf ("stop: fault at PC=0x%08x\n", reg_pc[0]);
                break;

              case FETCH_INVALID:
              default:
                printf ("stop: invalid instruction at PC=0x%08x\n", reg_pc[0]);
                break;
            }
          break;
        }
    };

  printf ("\n");
  mem_print (32);
  printf ("\n");
  reg_print ();

  if (mem_save ("memsave.bin") < 0)
    {
      printf ("failed to write memory\n");
      return -1;
    }

  if (reg_save ("regsave.bin") < 0)
    {
      printf ("failed to write registers\n");
      return -1;
    }

  return 0;
}
