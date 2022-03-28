#ifndef __MEMORY_H__
#define __MEMORY_H__

#define MEMSIZE (1<<12) /* 4K */

#define REG_ZERO REG_X0 /* Hard-wired zero */
#define REG_RA REG_X1 /* Return address  */
#define REG_SP REG_X2 /* Stack pointer  */
#define REG_GP REG_X3 /* Global pointer */
#define REG_TP REG_X4 /* Thread pointer */
#define REG_T0 REG_X5 /* Temporary/alternate link register */
#define REG_T1 REG_X6 /* Temporary register */
#define REG_T2 REG_X7 /* Temporary register */
#define REG_S0 REG_X8 /* Frame pointer */
#define REG_S1 REG_X9 /* Saved register */
#define REG_A0 REG_X10 /* Function arguments/return values */
#define REG_A1 REG_X11 /* Function arguments */

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
  REG_GP_XLEN
};

enum
{
  REG_PC,
  REG_PC_XLEN
};

/* Memory Globals */
#ifndef MAIN_FILE
#define IS_EXTERN extern
#else /* MAIN_FILE */
#define IS_EXTERN
#endif /* MAIN_FILE */
IS_EXTERN uint32_t memory[MEMSIZE];
IS_EXTERN uint32_t reg_gp[REG_GP_XLEN];
IS_EXTERN uint32_t reg_pc[REG_PC_XLEN];
#undef IS_EXTERN

#endif /* __MEMORY_H__ */

