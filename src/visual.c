#include <stdio.h>
#include <stdint.h>
#include "memory.h"
#include "visual.h"

int mem_print(uint32_t const *mem, size_t size)
{
  uint8_t *p = (uint8_t *)mem;
  size_t p_size = sizeof(mem) * size;
  size_t i, j;

  printf("[ MEMORY ]\n");
  for (i = 0, j = 0; i < p_size; i++, j++)
  {
    if (j == 16)
    {
      printf("\n");
      j = 0;
    }
    printf("%.2x ", p[i]);
  }
  printf("\n");

  return 0;
}

int reg_print()
{
  uint8_t *p;
  size_t reg;

  printf("[ REGISTERS ]\n");
  for (reg = REG_X0; reg < REG_GP_XLEN; reg++)
  {
    printf("REG_X%d:%c ", (int)reg, (reg < 10) ? ' ' : '\0');
    p = (uint8_t *)(reg_gp + reg);

    for (int i = 0; i < sizeof(*reg_gp); i++)
    {
      printf("%.2x ", p[i]);
    }
    printf("\n");
  }

  return 0;
}

