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
  ssize_t nw;
  size_t reg_gp_size = REG_GP_COUNT * sizeof (reg_gp[0]);

  fd = open (reg_path, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  if (fd == -1)
    {
      perror ("error occured");
      return -1;
    }

  nw = write (fd, reg_gp, reg_gp_size);

  close (fd);

  if (nw < 0)
    {
      perror ("error occured");
      return -1;
    }
  if ((size_t)nw != reg_gp_size)
    {
      printf ("reg: written only part of memory\n");
    }

  return (int)nw;
}

int
mem_print (size_t size)
{
  size_t i;

  printf ("[ MEMORY ]");
  for (i = 0; i < size; i++)
    {
      if (i % 16 == 0)
        {
          printf ("\n");
        }
      printf ("%.2x ", memory[i]);
    }
  printf ("\n");

  return 0;
}

int
reg_print (void)
{
  uint8_t *p;
  size_t reg;
  size_t i;

  printf ("[ REGISTERS ]\n");
  for (reg = REG_X0; reg < REG_GP_COUNT; reg++)
    {
      printf ("REG_X%d:%c ", (int)reg, (reg < 10) ? ' ' : '\0');
      p = (uint8_t *)(reg_gp + reg);

      for (i = 0; i < sizeof (*reg_gp); i++)
        {
          printf ("%.2x ", p[i]);
        }
      printf ("| %d\n", reg_gp[reg]);
    }

  printf ("-----\n");

  printf ("REG_PC:  ");
  p = (uint8_t *)(reg_pc);
  for (i = 0; i < sizeof (reg_pc[0]); i++)
    {
      printf ("%.2x ", p[i]);
    }
  printf ("| %d\n", reg_pc[0]);

  return 0;
}
