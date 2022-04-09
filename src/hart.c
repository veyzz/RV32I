#include <stdint.h>
#include <string.h>
#include "memory.h"
#include "hart.h"

int fetch(uint8_t *ip)
{
  uint32_t instr = *(uint32_t *)ip;

  reg_gp[REG_X0] = 0;

  switch (GET_OPCODE(instr))
  {
    case 0b0110011:

      switch(GET_FUNCT3(instr))
      {
        case 0x0:

          switch(GET_FUNCT7(instr))
          {

            case 0x00:
              reg_gp[GET_RD(instr)] = \
                reg_gp[GET_RS1(instr)] + reg_gp[GET_RS2(instr)];
              break;

            case 0x20:
              reg_gp[GET_RD(instr)] = \
                reg_gp[GET_RS1(instr)] - reg_gp[GET_RS2(instr)];
              break;

            default:
              return 1;
          }
          break;

        case 0x4:
          reg_gp[GET_RD(instr)] = \
            reg_gp[GET_RS1(instr)] ^ reg_gp[GET_RS2(instr)];
          break;

        case 0x6:
          reg_gp[GET_RD(instr)] = \
            reg_gp[GET_RS1(instr)] | reg_gp[GET_RS2(instr)];
          break;

        case 0x7:
          reg_gp[GET_RD(instr)] = \
            reg_gp[GET_RS1(instr)] & reg_gp[GET_RS2(instr)];
          break;

        case 0x1:
          reg_gp[GET_RD(instr)] = \
            reg_gp[GET_RS1(instr)] << reg_gp[GET_RS2(instr)];
          break;

        case 0x5:

          switch(GET_FUNCT7(instr))
          {

            case 0x00:
              reg_gp[GET_RD(instr)] = \
                reg_gp[GET_RS1(instr)] >> reg_gp[GET_RS2(instr)];
              break;

            case 0x20:
              reg_gp[GET_RD(instr)] = \
                (uint32_t)((int32_t)reg_gp[GET_RS1(instr)] >> (int32_t)reg_gp[GET_RS2(instr)]);
              break;

            default:
              return 1;
          }
          break;

        case 0x2:
          reg_gp[GET_RD(instr)] = \
            ((int32_t)reg_gp[GET_RS1(instr)] < (int32_t)reg_gp[GET_RS2(instr)]) ? 1 : 0;
          break;

        case 0x3:
          reg_gp[GET_RD(instr)] = \
            (reg_gp[GET_RS1(instr)] < reg_gp[GET_RS2(instr)]) ? 1 : 0;
          break;

        default:
          return 1;
      }
      break;

    case 0b0010011:

      switch(GET_FUNCT3(instr))
      {
        case 0x0:
          reg_gp[GET_RD(instr)] = \
            reg_gp[GET_RS1(instr)] + GET_IMM_I(instr);
          break;

        case 0x4:
          reg_gp[GET_RD(instr)] = \
            reg_gp[GET_RS1(instr)] ^ GET_IMM_I(instr);
          break;

        case 0x6:
          reg_gp[GET_RD(instr)] = \
            reg_gp[GET_RS1(instr)] | GET_IMM_I(instr);
          break;

        case 0x7:
          reg_gp[GET_RD(instr)] = \
            reg_gp[GET_RS1(instr)] & GET_IMM_I(instr);
          break;

        case 0x1:

          switch(GET_BIT_FIELD(GET_IMM_I(instr), 5, 11))
          {

            case 0x00:
              reg_gp[GET_RD(instr)] = \
                reg_gp[GET_RS1(instr)] << GET_BIT_FIELD(GET_IMM_I(instr), 0, 4);
              break;

            default:
              return 1;
          }
          break;

        case 0x5:

          switch(GET_BIT_FIELD(GET_IMM_I(instr), 5, 11))
          {

            case 0x00:
              reg_gp[GET_RD(instr)] = \
                reg_gp[GET_RS1(instr)] >> GET_BIT_FIELD(GET_IMM_I(instr), 0, 4);
              break;

            case 0x20:
              reg_gp[GET_RD(instr)] = \
                (uint32_t)((int32_t)reg_gp[GET_RS1(instr)] >> \
                           (int32_t)GET_BIT_FIELD(GET_IMM_I(instr), 0, 4));
              break;

            default:
              return 1;
          }
          break;

        case 0x2:
          reg_gp[GET_RD(instr)] = \
            ((int32_t)reg_gp[GET_RS1(instr)] < (int32_t)GET_IMM_I(instr)) ? 1 : 0;
          break;

        case 0x3:
          reg_gp[GET_RD(instr)] = \
            (reg_gp[GET_RS1(instr)] < GET_IMM_I(instr)) ? 1 : 0;
          break;

        default:
          return 1;
      }
      break;

    default:
      return 1;
  }

  reg_pc[0] += sizeof(uint32_t);

  return 0;
}

