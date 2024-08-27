#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "CPU.h"

void test_add();


void test_add() {
   
    Registers* reg = (Registers*)malloc(sizeof(Registers));

    reg->a = 10;
    reg->f = 0;
    reg->c = 5;

    InstructionType addInstr = ADD;
    ArithmeticTarget cReg = C;

    Instruction instruction = {.type = addInstr, .target = cReg};

    uint8_t* did_overflow = (uint8_t*)malloc(sizeof(u_int8_t));
    *did_overflow = 0;
    execute(reg, instruction);
    printf("F register %d", reg->f);
    assert(reg->a == 15);
    assert(reg->f == 0);

    reg->a = 250;
    
    uint8_t result = add(reg, 10, did_overflow);
    assert(result == 4);
    FlagsRegister flags = uint8_to_FlagsRegister(reg->f);
    assert(flags.carry == 1);
    assert(*did_overflow == 1);

    reg->a = 255;
    result = add(reg, 1, did_overflow);
    flags = uint8_to_FlagsRegister(reg->f);
    assert(result == 0);
    assert(flags.zero == 1);
    assert(flags.half_carry == 1);
    assert(*did_overflow == 1);

    reg->a = 0x0F;
    printf("Value of a in test %d\n", reg->a);
    result = add(reg, 0x01, did_overflow);
    flags = uint8_to_FlagsRegister(reg->f);
    assert(reg->a == 16);
    assert(flags.half_carry == 1);
}

void run_all_tests() {
    printf("Testing add \n");
    test_add();
}

void run_one_test(){
    test_add();
}


int main() {
    run_all_tests();
    printf("All instruction tests passed successfully.\n");
    return 0;
}
