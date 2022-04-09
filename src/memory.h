#ifndef __MEMORY_H__
#define __MEMORY_H__

#define XLEN 32
#if 0 /* max memsize */
#define MEMSIZE (1UL << XLEN)
#else
#define MEMSIZE (1 << 12) /* 4K */
#endif

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
#ifndef MAIN_FILE
#define IS_EXTERN extern
#else /* MAIN_FILE */
#define IS_EXTERN
#endif /* MAIN_FILE */
IS_EXTERN uint8_t  memory[MEMSIZE];
IS_EXTERN uint32_t reg_gp[REG_GP_COUNT];
IS_EXTERN uint32_t reg_pc[REG_PC_COUNT];
#undef IS_EXTERN

int mem_init(char const *mem_path);
int reg_init(char const *reg_path);

int mem_print(size_t size);
int reg_print();

#endif /* __MEMORY_H__ */

