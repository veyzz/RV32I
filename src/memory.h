#ifndef __MEMORY_H__
#define __MEMORY_H__

#define MEMSIZE (1U << 12) /* 4K */
#define MEMBASE 0x80000000U
#define MEMMASK ((uint32_t)(MEMSIZE - 1U))

#define ADDR_IS_VALID(addr)                                             \
  ((uint32_t)(addr) >= MEMBASE && (uint32_t)(addr) < MEMBASE + MEMSIZE)
#define ADDR_TO_IDX(addr) ((uint32_t)(addr) - MEMBASE)
#define IDX_TO_ADDR(idx) ((uint32_t)(idx) + MEMBASE)

enum
{
  REG_X0,
  REG_X1,
  REG_X2,
  REG_X3,
  REG_X4,
  REG_X5,
  REG_X6,
  REG_X7,
  REG_X8,
  REG_X9,
  REG_X10,
  REG_X11,
  REG_X12,
  REG_X13,
  REG_X14,
  REG_X15,
  REG_X16,
  REG_X17,
  REG_X18,
  REG_X19,
  REG_X20,
  REG_X21,
  REG_X22,
  REG_X23,
  REG_X24,
  REG_X25,
  REG_X26,
  REG_X27,
  REG_X28,
  REG_X29,
  REG_X30,
  REG_X31,
  REG_GP_COUNT
};

enum
{
  REG_PC,
  REG_PC_COUNT
};

/* Memory Globals */
extern uint8_t memory[MEMSIZE];
extern uint32_t reg_gp[REG_GP_COUNT];
extern uint32_t reg_pc[REG_PC_COUNT];

int mem_init (char const *mem_path);
int mem_save (char const *mem_path);
int reg_save (char const *reg_path);
int mem_print (size_t size);
int reg_print (void);

#endif /* __MEMORY_H__ */
