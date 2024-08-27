#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "CPU.h"

const u_int8_t ZERO_FLAG_BYTE_POSITION  = 7;
const u_int8_t SUBTRACT_FLAG_BYTE_POSITION = 6;
const u_int8_t HALF_CARRY_FLAG_BYTE_POSITION = 5;
const u_int8_t CARRY_FLAG_BYTE_POSITION = 4;


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







void execute(Registers *r, Instruction instr){
    switch (instr.type) {
        case ADD:
            switch (instr.target) {
                case C: {
                    uint8_t *overflow = (uint8_t*)malloc(sizeof(u_int8_t));
                    *overflow = 0;
                    int value = r->c;
                    int newValue = add(r, value, overflow);
                    r->a = newValue;
                    break;
                default:
                    printf("Target not supported yet\n");
                    break;
            }
            }
            break;
        // Add cases for other instruction types as needed
        default:
            printf("Instruction not supported yet\n");
            break;
    }
}

uint8_t add(Registers *reg, uint8_t value, uint8_t *did_overflow) {

    //Variables Defined for setting half carry flag      
    uint8_t lower_nibble_a = reg->a & 0xF;
    uint8_t lower_nibble_value = value & 0xF;

    uint16_t result = (uint16_t)reg->a + (uint16_t)value; 
    *did_overflow = (result > 255);

    reg->a = (uint8_t)result;
    

    FlagsRegister flags = uint8_to_FlagsRegister(reg->f);

    flags.zero = (reg->a == 0);

    flags.subtract = 0;

    flags.carry = *did_overflow;
    

    uint8_t sum_lower_nibbles = lower_nibble_a + lower_nibble_value;

    printf("reg.a (lower nibble): 0x%X\n", lower_nibble_a);
    printf("value (lower nibble): 0x%X\n", lower_nibble_value);
    printf("Sum of lower nibbles: 0x%X\n", sum_lower_nibbles);
    printf("Comparing sum of lower nibbles to 0xF: %s\n", sum_lower_nibbles > 0xF ? "true" : "false");



    flags.half_carry = ((lower_nibble_a) + (lower_nibble_value)) > 0xF;

    reg->f = FlagsRegister_to_uint8(flags);

    return reg->a; 
}

