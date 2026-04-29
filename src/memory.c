#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "memory.h"

uint8_t memory[MEMSIZE];
uint32_t reg_gp[REG_GP_COUNT];
uint32_t reg_pc[REG_PC_COUNT];

int
mem_init (char const *mem_path)
{
  int fd;
  struct stat filestat;
  void *data = NULL;

  fd = open (mem_path, O_RDONLY | O_SYNC);

  if (fd == -1 || fstat (fd, &filestat) == -1)
    {
      perror ("error occured");
      return -1;
    }

  data = mmap (NULL, filestat.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (data == MAP_FAILED)
    {
      perror ("mmap failed");
      return -1;
    }

  memcpy (memory, data, filestat.st_size);

  munmap (data, filestat.st_size);

  close (fd);

  return filestat.st_size;
}

int
mem_save (char const *mem_path)
{
  int fd;
  ssize_t nw;

  fd = open (mem_path, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  if (fd == -1)
    {
      perror ("error occured");
      return -1;
    }

  nw = write (fd, memory, MEMSIZE);

  close (fd);

  if (nw < 0)
    {
      perror ("error occured");
      return -1;
    }
  if ((size_t)nw != MEMSIZE)
    {
      printf ("mem: written only part of memory\n");
    }

  return (int)nw;
}

int
reg_save (char const *reg_path)
{
  int fd;
  ssize_t nw_gp;
  ssize_t nw_pc;
  size_t reg_gp_size = REG_GP_COUNT * sizeof (reg_gp[0]);
  size_t reg_pc_size = sizeof (reg_pc[0]);

  fd = open (reg_path, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  if (fd == -1)
    {
      perror ("error occured");
      return -1;
    }

  nw_gp = write (fd, reg_gp, reg_gp_size);
  nw_pc = write (fd, reg_pc, reg_pc_size);

  close (fd);

  if (nw_gp < 0 || nw_pc < 0)
    {
      perror ("error occured");
      return -1;
    }
  if ((size_t)nw_gp != reg_gp_size || (size_t)nw_pc != reg_pc_size)
    {
      printf ("reg: written only part of register dump\n");
    }

  return (int)(nw_gp + nw_pc);
}

int
mem_print (size_t size)
{
  size_t row, col;

  printf ("[ MEMORY ]\n");
  for (row = 0; row < size; row += 8)
    {
      printf ("0x%08x: ", IDX_TO_ADDR (row));

      for (col = 0; col < 8; col++)
        {
          size_t idx = row + col;
          if (idx >= size)
            break;
          printf ("%02X ", memory[idx]);
        }
      printf ("\n");
    }

  return 0;
}

int
reg_print (void)
{
  size_t reg;
  uint8_t *p;

  printf ("[ REGISTERS ]\n");
  printf (" # |     DUMP    |     INT     |     HEX\n");
  for (reg = REG_X0; reg < REG_GP_COUNT; reg++)
    {
      p = (uint8_t *)(reg_gp + reg);
      printf ("%-2zu | %02X %02X %02X %02X | %11d | 0x%08x\n", reg, p[0], p[1],
              p[2], p[3], (int32_t)reg_gp[reg], reg_gp[reg]);
    }

  p = (uint8_t *)(reg_pc);
  printf ("PC | %02X %02X %02X %02X | %11d | 0x%08x\n", p[0], p[1], p[2], p[3],
          (int32_t)reg_pc[0], reg_pc[0]);

  return 0;
}
