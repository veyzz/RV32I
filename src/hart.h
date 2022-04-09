#ifndef __HART_H__
#define __HART_H__

#define BIT_MASK(lsb, msb) \
        (((1U << ((msb) - (lsb) + 1U)) - 1U) << (lsb))

#define GET_BIT_FIELD(num, lsb, msb) \
        (((num) & BIT_MASK((lsb), (msb))) >> (lsb))

#define GET_OPCODE(instr) \
        GET_BIT_FIELD((instr), 0, 6)

#define GET_RD(instr) \
        GET_BIT_FIELD((instr), 7, 11)
#define GET_RS1(instr) \
        GET_BIT_FIELD((instr), 15, 19)
#define GET_RS2(instr) \
        GET_BIT_FIELD((instr), 20, 24)

#define GET_FUNCT3(instr) \
        GET_BIT_FIELD((instr), 12, 14)
#define GET_FUNCT7(instr) \
        GET_BIT_FIELD((instr), 25, 31)

#define GET_UIMM_I(instr) \
        GET_BIT_FIELD((instr), 20, 31)
#define GET_UIMM_S(instr) \
        (GET_BIT_FIELD((instr), 7, 11) | \
        (GET_BIT_FIELD((instr), 25, 31) << 5))
#define GET_UIMM_B(instr) \
        ((GET_BIT_FIELD((instr), 8, 11) | \
        (GET_BIT_FIELD((instr), 25, 30) << 4) | \
        (GET_BIT_FIELD((instr), 7, 7) << 10) | \
        (GET_BIT_FIELD((instr), 31, 31) << 11)) << 1)
#define GET_UIMM_U(instr) \
        (GET_BIT_FIELD((instr), 12, 31) << 12)
#define GET_UIMM_J(instr) \
        ((GET_BIT_FIELD((instr), 21, 30) | \
        (GET_BIT_FIELD((instr), 20, 20) << 10) | \
        (GET_BIT_FIELD((instr), 12, 19) << 18) | \
        (GET_BIT_FIELD((instr), 31, 31) << 19)) << 1)

#define GET_IMM_I(instr) \
        (GET_BIT_FIELD((instr), 31, 31)          ? \
        GET_UIMM_I((instr)) | BIT_MASK(11, 31)  : \
        GET_UIMM_I((instr)) & ~BIT_MASK(11, 31))
#define GET_IMM_S(instr) \
        (GET_BIT_FIELD((instr), 31, 31)          ? \
        GET_UIMM_S((instr)) | BIT_MASK(11, 31)  : \
        GET_UIMM_S((instr)) & ~BIT_MASK(11, 31))
#define GET_IMM_B(instr) \
        (GET_BIT_FIELD((instr), 31, 31)          ? \
        GET_UIMM_B((instr)) | BIT_MASK(12, 31)  : \
        GET_UIMM_B((instr)) & ~BIT_MASK(12, 31))
#define GET_IMM_U(instr) \
        GET_UIMM_U((instr))
#define GET_IMM_J(instr) \
        (GET_BIT_FIELD((instr), 31, 31)          ? \
        GET_UIMM_J((instr)) | BIT_MASK(20, 31)  : \
        GET_UIMM_J((instr)) & ~BIT_MASK(20, 31))

int fetch(uint8_t *ip);

#endif /* __HART_H__ */

