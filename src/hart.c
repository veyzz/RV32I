#include <stdint.h>
#include <string.h>
#include "memory.h"
#include "hart.h"

int
fetch (uint8_t *ip)
{
  uint32_t instr;
  memcpy (&instr, ip, sizeof (instr));

  reg_gp[REG_X0] = 0;

  uint32_t const pc_cur = reg_pc[0];
  uint32_t pc_next = pc_cur + sizeof (uint32_t);

  switch (GET_OPCODE (instr))
    {
      case RV_OP_OP:

        switch (GET_FUNCT3 (instr))
          {
            case RV_F3_ADD_SUB:

              switch (GET_FUNCT7 (instr))
                {

                  case RV_F7_ADD_SRL:
                    reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                             + reg_gp[GET_RS2 (instr)];
                    break;

                  case RV_F7_SUB_SRA:
                    reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                             - reg_gp[GET_RS2 (instr)];
                    break;

                  default:
                    return FETCH_INVALID;
                }
              break;

            case RV_F3_XOR:
              reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                       ^ reg_gp[GET_RS2 (instr)];
              break;

            case RV_F3_OR:
              reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                       | reg_gp[GET_RS2 (instr)];
              break;

            case RV_F3_AND:
              reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                       & reg_gp[GET_RS2 (instr)];
              break;

            case RV_F3_SLL:
              reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                       << (reg_gp[GET_RS2 (instr)] & 0x1F);
              break;

            case RV_F3_SRL_SRA:

              switch (GET_FUNCT7 (instr))
                {

                  case RV_F7_ADD_SRL:
                    reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                             >> (reg_gp[GET_RS2 (instr)]
                                                 & 0x1F);
                    break;

                  case RV_F7_SUB_SRA:
                    reg_gp[GET_RD (instr)]
                        = (uint32_t)((int32_t)reg_gp[GET_RS1 (instr)]
                                     >> (int32_t)(reg_gp[GET_RS2 (instr)]
                                                  & 0x1F));
                    break;

                  default:
                    return FETCH_INVALID;
                }
              break;

            case RV_F3_SLT:
              reg_gp[GET_RD (instr)] = ((int32_t)reg_gp[GET_RS1 (instr)]
                                        < (int32_t)reg_gp[GET_RS2 (instr)])
                                           ? 1
                                           : 0;
              break;

            case RV_F3_SLTU:
              reg_gp[GET_RD (instr)] = (reg_gp[GET_RS1 (instr)]
                                        < reg_gp[GET_RS2 (instr)])
                                           ? 1
                                           : 0;
              break;

            default:
              return FETCH_INVALID;
          }
        break;

      case RV_OP_IMM:

        switch (GET_FUNCT3 (instr))
          {
            case RV_F3_ADD_SUB:
              reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                       + GET_IMM_I (instr);
              break;

            case RV_F3_XOR:
              reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                       ^ GET_IMM_I (instr);
              break;

            case RV_F3_OR:
              reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                       | GET_IMM_I (instr);
              break;

            case RV_F3_AND:
              reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                       & GET_IMM_I (instr);
              break;

            case RV_F3_SLL:

              switch (GET_BIT_FIELD (GET_IMM_I (instr), 5, 11))
                {

                  case RV_F7_ADD_SRL:
                    reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                             << GET_BIT_FIELD (GET_IMM_I (
                                                                   instr),
                                                               0, 4);
                    break;

                  default:
                    return FETCH_INVALID;
                }
              break;

            case RV_F3_SRL_SRA:

              switch (GET_BIT_FIELD (GET_IMM_I (instr), 5, 11))
                {

                  case RV_F7_ADD_SRL:
                    reg_gp[GET_RD (instr)] = reg_gp[GET_RS1 (instr)]
                                             >> GET_BIT_FIELD (GET_IMM_I (
                                                                   instr),
                                                               0, 4);
                    break;

                  case RV_F7_SUB_SRA:
                    reg_gp[GET_RD (instr)]
                        = (uint32_t)((int32_t)reg_gp[GET_RS1 (instr)]
                                     >> (int32_t)GET_BIT_FIELD (
                                         GET_IMM_I (instr), 0, 4));
                    break;

                  default:
                    return FETCH_INVALID;
                }
              break;

            case RV_F3_SLT:
              reg_gp[GET_RD (instr)] = ((int32_t)reg_gp[GET_RS1 (instr)]
                                        < (int32_t)GET_IMM_I (instr))
                                           ? 1
                                           : 0;
              break;

            case RV_F3_SLTU:
              reg_gp[GET_RD (instr)] = (reg_gp[GET_RS1 (instr)]
                                        < GET_IMM_I (instr))
                                           ? 1
                                           : 0;
              break;

            default:
              return FETCH_INVALID;
          }
        break;

      case RV_OP_LOAD:

        {
          uint32_t addr = reg_gp[GET_RS1 (instr)] + GET_IMM_I (instr);
          switch (GET_FUNCT3 (instr))
            {
              case RV_F3_MEM_B:
                if (!ADDR_IS_VALID (addr))
                  return FETCH_FAULT;
                reg_gp[GET_RD (instr)] = *(int8_t *)(memory
                                                     + ADDR_TO_IDX (addr));
                break;

              case RV_F3_MEM_H:
                if (!ADDR_IS_VALID (addr) || !ADDR_IS_VALID (addr + 1))
                  return FETCH_FAULT;
                {
                  int16_t val;
                  memcpy (&val, memory + ADDR_TO_IDX (addr), sizeof (val));
                  reg_gp[GET_RD (instr)] = (uint32_t)val;
                }
                break;

              case RV_F3_MEM_W:
                if (!ADDR_IS_VALID (addr) || !ADDR_IS_VALID (addr + 3))
                  return FETCH_FAULT;
                {
                  uint32_t val;
                  memcpy (&val, memory + ADDR_TO_IDX (addr), sizeof (val));
                  reg_gp[GET_RD (instr)] = val;
                }
                break;

              case RV_F3_MEM_BU:
                if (!ADDR_IS_VALID (addr))
                  return FETCH_FAULT;
                reg_gp[GET_RD (instr)] = *(uint8_t *)(memory
                                                      + ADDR_TO_IDX (addr));
                break;

              case RV_F3_MEM_HU:
                if (!ADDR_IS_VALID (addr) || !ADDR_IS_VALID (addr + 1))
                  return FETCH_FAULT;
                {
                  uint16_t val;
                  memcpy (&val, memory + ADDR_TO_IDX (addr), sizeof (val));
                  reg_gp[GET_RD (instr)] = (uint32_t)val;
                }
                break;

              default:
                return FETCH_INVALID;
            }
          break;
        }

      case RV_OP_STORE:

        {
          uint32_t addr = reg_gp[GET_RS1 (instr)] + GET_IMM_S (instr);
          switch (GET_FUNCT3 (instr))
            {
              case RV_F3_MEM_B:
                if (!ADDR_IS_VALID (addr))
                  return FETCH_FAULT;
                memcpy (memory + ADDR_TO_IDX (addr), reg_gp + GET_RS2 (instr),
                        sizeof (uint8_t));
                break;

              case RV_F3_MEM_H:
                if (!ADDR_IS_VALID (addr) || !ADDR_IS_VALID (addr + 1))
                  return FETCH_FAULT;
                memcpy (memory + ADDR_TO_IDX (addr), reg_gp + GET_RS2 (instr),
                        sizeof (uint16_t));
                break;

              case RV_F3_MEM_W:
                if (!ADDR_IS_VALID (addr) || !ADDR_IS_VALID (addr + 3))
                  return FETCH_FAULT;
                memcpy (memory + ADDR_TO_IDX (addr), reg_gp + GET_RS2 (instr),
                        sizeof (uint32_t));
                break;

              default:
                return FETCH_INVALID;
            }
          break;
        }

      case RV_OP_BRANCH:

        switch (GET_FUNCT3 (instr))
          {
            case RV_F3_BR_BEQ:
              if (reg_gp[GET_RS1 (instr)] == reg_gp[GET_RS2 (instr)])
                {
                  pc_next = pc_cur + GET_IMM_B (instr);
                  if ((pc_next & 0x3U) != 0)
                    return FETCH_FAULT;
                }
              break;

            case RV_F3_BR_BNE:
              if (reg_gp[GET_RS1 (instr)] != reg_gp[GET_RS2 (instr)])
                {
                  pc_next = pc_cur + GET_IMM_B (instr);
                  if ((pc_next & 0x3U) != 0)
                    return FETCH_FAULT;
                }
              break;

            case RV_F3_BR_BLT:
              if ((int32_t)reg_gp[GET_RS1 (instr)]
                  < (int32_t)reg_gp[GET_RS2 (instr)])
                {
                  pc_next = pc_cur + GET_IMM_B (instr);
                  if ((pc_next & 0x3U) != 0)
                    return FETCH_FAULT;
                }
              break;

            case RV_F3_BR_BGE:
              if ((int32_t)reg_gp[GET_RS1 (instr)]
                  >= (int32_t)reg_gp[GET_RS2 (instr)])
                {
                  pc_next = pc_cur + GET_IMM_B (instr);
                  if ((pc_next & 0x3U) != 0)
                    return FETCH_FAULT;
                }
              break;

            case RV_F3_BR_BLTU:
              if (reg_gp[GET_RS1 (instr)] < reg_gp[GET_RS2 (instr)])
                {
                  pc_next = pc_cur + GET_IMM_B (instr);
                  if ((pc_next & 0x3U) != 0)
                    return FETCH_FAULT;
                }
              break;

            case RV_F3_BR_BGEU:
              if (reg_gp[GET_RS1 (instr)] >= reg_gp[GET_RS2 (instr)])
                {
                  pc_next = pc_cur + GET_IMM_B (instr);
                  if ((pc_next & 0x3U) != 0)
                    return FETCH_FAULT;
                }
              break;

            default:
              return FETCH_INVALID;
          }
        break;

      case RV_OP_JAL:

        reg_gp[GET_RD (instr)] = pc_cur + sizeof (uint32_t);
        pc_next = pc_cur + GET_IMM_J (instr);
        if ((pc_next & 0x3U) != 0)
          return FETCH_FAULT;
        break;

      case RV_OP_JALR:

        switch (GET_FUNCT3 (instr))
          {
            case RV_F3_JALR:
              reg_gp[GET_RD (instr)] = pc_cur + sizeof (uint32_t);
              pc_next = (reg_gp[GET_RS1 (instr)] + GET_IMM_I (instr)) & ~1U;
              if ((pc_next & 0x3U) != 0)
                return FETCH_FAULT;
              break;

            default:
              return FETCH_INVALID;
          }
        break;

      case RV_OP_LUI:

        reg_gp[GET_RD (instr)] = GET_IMM_U (instr);
        break;

      case RV_OP_AUIPC:

        reg_gp[GET_RD (instr)] = pc_cur + GET_IMM_U (instr);
        break;

      case RV_OP_SYSTEM:

        switch (GET_FUNCT3 (instr))
          {
            case RV_F3_PRIV:

              switch (GET_FUNCT12 (instr))
                {
                  case RV_F12_ECALL:
                    return FETCH_TRAP_ECALL;

                  case RV_F12_EBREAK:
                    return FETCH_TRAP_EBREAK;

                  default:
                    return FETCH_INVALID;
                }
              break;

            default:
              return FETCH_INVALID;
          }
        break;

      case RV_OP_MISC_MEM:

        switch (GET_FUNCT3 (instr))
          {
            case RV_F3_FENCE:
              /* NOP */
              break;

            default:
              return FETCH_INVALID;
          }
        break;

      default:
        return FETCH_INVALID;
    }

  reg_pc[0] = pc_next;

  return FETCH_OK;
}
