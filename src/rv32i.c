#define MAIN_FILE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "memory.h"
#include "hart.h"
#include "visual.h"

int mem_init(char const *mem_path, uint32_t *mem)
{
	int fd;
	struct stat filestat;
	void *data = NULL;

	fd = open(mem_path, O_RDWR | O_SYNC);

  if (fd == -1 || fstat(fd, &filestat) == -1)
  {
		perror("error occured");
    return -1;
  }

	data = mmap(NULL, filestat.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED)
	{
		perror("mmap failed");
		return -1;
	}

  memcpy(mem, data, filestat.st_size);

  munmap(data, filestat.st_size);

  return 0;
}

int main(int argc, char const **argv)
{
  mem_init(argv[1], memory);
  mem_init(argv[2], reg_gp);
  if (1 != sscanf(argv[3], "%x", reg_pc))
    return -1;

  mem_print(memory, 8);
  reg_print();

  while (1)
  {
    if (fetch(memory[reg_pc[0]]))
      break;
  };

  mem_print(memory, 8);
  reg_print();

  return 0;
}

