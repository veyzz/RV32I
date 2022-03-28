#ifndef __HART_H__
#define __HART_H__

#define GET_BIT_FIELD(num, lsb, width) \
        (((num) >> (lsb)) & ((1 << (width)) - 1))
#define SET_BIT_FIELD(num, value, lsb, width) \
        ((num) |= ((value) & ((1 << (width)) - 1)) << (lsb))

#define GET_OPCODE(instr)         GET_BIT_FIELD((instr), 0, 7)
#define SET_OPCODE(instr, value)  SET_BIT_FIELD((instr), (value), 0, 7)

#define GET_RD(instr)             GET_BIT_FIELD((instr), 7, 5)
#define SET_RD(instr, value)      SET_BIT_FIELD((instr), (value), 7, 5)

#define GET_FUNCT3(instr)         GET_BIT_FIELD((instr), 12, 3)
#define SET_FUNCT3(instr, value)  SET_BIT_FIELD((instr), (value), 12, 3)

#define GET_RS1(instr)            GET_BIT_FIELD((instr), 15, 5)
#define SET_RS1(instr, value)     SET_BIT_FIELD((instr), (value), 15, 5)

#define GET_RS2(instr)            GET_BIT_FIELD((instr), 20, 5)
#define SET_RS2(instr, value)     SET_BIT_FIELD((instr), (value), 20, 5)

#define GET_FUNCT7(instr)         GET_BIT_FIELD((instr), 25, 7)
#define SET_FUNCT7(instr, value)  SET_BIT_FIELD((instr), (value), 25, 7)

int fetch(uint32_t instr);

#endif /* __HART_H__ */

