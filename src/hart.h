#ifndef __HART_H__
#define __HART_H__

#define BIT_MASK(lsb, msb) (((1U << ((msb) - (lsb) + 1U)) - 1U) << (lsb))

#define GET_BIT_FIELD(num, lsb, msb)           \
  (((num) & BIT_MASK ((lsb), (msb))) >> (lsb))

#define GET_OPCODE(instr) GET_BIT_FIELD ((instr), 0, 6)

#define GET_RD(instr) GET_BIT_FIELD ((instr), 7, 11)
#define GET_RS1(instr) GET_BIT_FIELD ((instr), 15, 19)
#define GET_RS2(instr) GET_BIT_FIELD ((instr), 20, 24)

#define GET_FUNCT3(instr) GET_BIT_FIELD ((instr), 12, 14)
#define GET_FUNCT7(instr) GET_BIT_FIELD ((instr), 25, 31)
#define GET_FUNCT12(instr) GET_BIT_FIELD ((instr), 20, 31)

#define GET_UIMM_I(instr) GET_BIT_FIELD ((instr), 20, 31)
#define GET_UIMM_S(instr)                                                   \
  (GET_BIT_FIELD ((instr), 7, 11) | (GET_BIT_FIELD ((instr), 25, 31) << 5))
#define GET_UIMM_B(instr)                                                   \
  ((GET_BIT_FIELD ((instr), 8, 11) | (GET_BIT_FIELD ((instr), 25, 30) << 4) \
    | (GET_BIT_FIELD ((instr), 7, 7) << 10)                                 \
    | (GET_BIT_FIELD ((instr), 31, 31) << 11))                              \
   << 1)
#define GET_UIMM_U(instr) (GET_BIT_FIELD ((instr), 12, 31) << 12)
#define GET_UIMM_J(instr)                                                     \
  ((GET_BIT_FIELD ((instr), 21, 30) | (GET_BIT_FIELD ((instr), 20, 20) << 10) \
    | (GET_BIT_FIELD ((instr), 12, 19) << 18)                                 \
    | (GET_BIT_FIELD ((instr), 31, 31) << 19))                                \
   << 1)

#define GET_IMM_I(instr)                            \
  (GET_BIT_FIELD ((instr), 31, 31)                  \
       ? GET_UIMM_I ((instr)) | BIT_MASK (11, 31)   \
       : GET_UIMM_I ((instr)) & ~BIT_MASK (11, 31))
#define GET_IMM_S(instr)                            \
  (GET_BIT_FIELD ((instr), 31, 31)                  \
       ? GET_UIMM_S ((instr)) | BIT_MASK (11, 31)   \
       : GET_UIMM_S ((instr)) & ~BIT_MASK (11, 31))
#define GET_IMM_B(instr)                            \
  (GET_BIT_FIELD ((instr), 31, 31)                  \
       ? GET_UIMM_B ((instr)) | BIT_MASK (12, 31)   \
       : GET_UIMM_B ((instr)) & ~BIT_MASK (12, 31))
#define GET_IMM_U(instr) GET_UIMM_U ((instr))
#define GET_IMM_J(instr)                            \
  (GET_BIT_FIELD ((instr), 31, 31)                  \
       ? GET_UIMM_J ((instr)) | BIT_MASK (20, 31)   \
       : GET_UIMM_J ((instr)) & ~BIT_MASK (20, 31))

#define RV_OP_OP 0x33 /* 0b0110011 */
#define RV_OP_IMM 0x13 /* 0b0010011 */
#define RV_OP_LOAD 0x03 /* 0b0000011 */
#define RV_OP_STORE 0x23 /* 0b0100011 */
#define RV_OP_BRANCH 0x63 /* 0b1100011 */
#define RV_OP_JAL 0x6f /* 0b1101111 */
#define RV_OP_JALR 0x67 /* 0b1100111 */
#define RV_OP_LUI 0x37 /* 0b0110111 */
#define RV_OP_AUIPC 0x17 /* 0b0010111 */
#define RV_OP_SYSTEM 0x73 /* 0b1110011 */
#define RV_OP_MISC_MEM 0x0f /* 0b0001111 */

#define RV_F3_ADD_SUB 0x0 /* 0b000 */
#define RV_F3_SLL 0x1 /* 0b001 */
#define RV_F3_SLT 0x2 /* 0b010 */
#define RV_F3_SLTU 0x3 /* 0b011 */
#define RV_F3_XOR 0x4 /* 0b100 */
#define RV_F3_SRL_SRA 0x5 /* 0b101 */
#define RV_F3_OR 0x6 /* 0b110 */
#define RV_F3_AND 0x7 /* 0b111 */
#define RV_F3_MEM_B 0x0 /* 0b000 */
#define RV_F3_MEM_H 0x1 /* 0b001 */
#define RV_F3_MEM_W 0x2 /* 0b010 */
#define RV_F3_MEM_BU 0x4 /* 0b100 */
#define RV_F3_MEM_HU 0x5 /* 0b101 */
#define RV_F3_BR_BEQ 0x0 /* 0b000 */
#define RV_F3_BR_BNE 0x1 /* 0b001 */
#define RV_F3_BR_BLT 0x4 /* 0b100 */
#define RV_F3_BR_BGE 0x5 /* 0b101 */
#define RV_F3_BR_BLTU 0x6 /* 0b110 */
#define RV_F3_BR_BGEU 0x7 /* 0b111 */
#define RV_F3_JALR 0x0 /* 0b000 */
#define RV_F3_PRIV 0x0 /* 0b000 */
#define RV_F3_FENCE 0x0 /* 0b000 */

#define RV_F7_ADD_SRL 0x00 /* 0b0000000 */
#define RV_F7_SUB_SRA 0x20 /* 0b0100000 */

#define RV_F12_ECALL 0x000 /* 0b000000000000 */
#define RV_F12_EBREAK 0x001 /* 0b000000000001 */

enum
{
  FETCH_OK,
  FETCH_INVALID,
  FETCH_FAULT,
  FETCH_TRAP_ECALL,
  FETCH_TRAP_EBREAK,
};

int fetch (uint8_t *ip);

#endif /* __HART_H__ */
