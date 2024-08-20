#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

const u_int8_t ZERO_FLAG_BYTE_POSITION  = 7;
const u_int8_t SUBTRACT_FLAG_BYTE_POSITION = 6;
const u_int8_t HALF_CARRY_FLAG_BYTE_POSITION = 5;
const u_int8_t CARRY_FLAG_BYTE_POSITION = 4;


typedef struct {
    u_int8_t a;
    u_int8_t b;
    u_int8_t c;
    u_int8_t d;
    u_int8_t e;
    u_int8_t f;
    u_int8_t h;
    u_int8_t l;


} Registers;

typedef struct {
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
} FlagsRegister;

// Registar manipulation
u_int16_t get_bc(const Registers *r){
    return (u_int16_t)r -> b << 8 | r -> c; 
}

void set_bc(Registers *r, u_int16_t value){ 
    r -> b = (value >> 8) & 0xFF;
    r -> c = value & 0xFF;
} 


uint8_t FlagsRegister_to_uint8(FlagsRegister flag) {
    return ((flag.zero       ? 1 : 0) << ZERO_FLAG_BYTE_POSITION) |
           ((flag.subtract   ? 1 : 0) << SUBTRACT_FLAG_BYTE_POSITION) |
           ((flag.half_carry ? 1 : 0) << HALF_CARRY_FLAG_BYTE_POSITION) |
           ((flag.carry      ? 1 : 0) << CARRY_FLAG_BYTE_POSITION);
}

FlagsRegister uint8_to_FlagsRegister(uint8_t byte) {
    FlagsRegister flag;
    flag.zero       = (byte >> ZERO_FLAG_BYTE_POSITION) & 0x01;
    flag.subtract   = (byte >> SUBTRACT_FLAG_BYTE_POSITION) & 0x01;
    flag.half_carry = (byte >> HALF_CARRY_FLAG_BYTE_POSITION) & 0x01;
    flag.carry      = (byte >> CARRY_FLAG_BYTE_POSITION) & 0x01;

    return flag;
}

typedef enum {
  A, 
  B, 
  C, 
  D, 
  E, 
  H, 
  L
} ArithmeticTarget;

typedef enum {
    ADD
} InstructionType;

typedef struct {
    InstructionType type;
    ArithmeticTarget target;
} Instruction;


void execute(Registers *r, Instruction instr){
    switch (instr.type) {
        case ADD:
            switch (instr.target) {
                case C:
                    uint8_t* overflow;
                    int value = r->c;
                    int newValue = add(r, value, overflow);
                    r->a = newValue;
                    break;
                default:
                    printf("Target not supported yet\n");
                    break;
            }
            break;
        // Add cases for other instruction types as needed
        default:
            printf("Instruction not supported yet\n");
            break;
    }
}

uint8_t add(Registers *reg, uint8_t value, uint8_t *did_overflow) {
    uint16_t result = (uint16_t)reg->a + (uint16_t)value; // Promote to uint16_t to detect overflow
    *did_overflow = (result > 255); // Check if the result exceeds the max value of uint8_t

    reg->a = (uint8_t)result; // Store only the lower 8 bits back into the register

    // TODO: Set flags based on the operation result, e.g., zero flag, carry flag, etc.
    return reg->a; // Return the new value of 'a'
}

int main(){
    return 0;
}