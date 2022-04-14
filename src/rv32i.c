#define MAIN_FILE

#include <stdint.h>
#include <stdio.h>
#include "memory.h"
#include "hart.h"

int main(int argc, char const **argv)
{
  if (argc != 4)
  {
    printf("Usage: %s mem.bin reg.bin 0x0\n"
           "  mem.bin - path to hex dump of memory,\n"
           "  reg.bin - path to hex dump of registers\n"
           "  0x0     - PC (instruction pointer)\n",
           argv[0]);
    return -1;
  }

  if (0 > mem_init(argv[1]))
  {
    printf("failed to read memory\n");
    return -1;
  }

  if (0 > reg_init(argv[2]))
  {
    printf("failed to read registers\n");
    return -1;
  }

  if (1 != sscanf(argv[3], "%x", reg_pc))
  {
    printf("failed to get PC\n");
    return -1;
  }

  mem_print(8);
  reg_print();

  while (1)
  {
    if (fetch(memory + reg_pc[0]))
      break;
  };

  mem_print(8);
  reg_print();

  if (0 > mem_save("memsave.bin"))
  {
    printf("failed to write memory\n");
    return -1;
  }

  if (0 > reg_save("regsave.bin"))
  {
    printf("failed to write registers\n");
    return -1;
  }

  return 0;
}

