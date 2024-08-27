#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t a, b, c, d, e, f, h, l;
} Registers;

typedef struct {
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
} FlagsRegister;

typedef enum {
    ADD
} InstructionType;

typedef enum {
  A, 
  B, 
  C, 
  D, 
  E, 
  H, 
  L
} ArithmeticTarget;

typedef struct {
    InstructionType type;
    ArithmeticTarget target;
} Instruction;



uint8_t add(Registers *reg, uint8_t value, uint8_t *did_overflow);
uint16_t get_bc(const Registers *r);
void set_bc(Registers *r, uint16_t value);
uint8_t FlagsRegister_to_uint8(FlagsRegister flag);
FlagsRegister uint8_to_FlagsRegister(uint8_t byte);
void execute(Registers *r, Instruction instr);

#endif