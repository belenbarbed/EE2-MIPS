/*
 * structdef.h
 *
 *  Created on: 21 Oct 2016
 *      Author: bb2115
 */

#ifndef MIPS_CPU_STRUCTDEF_H_
#define MIPS_CPU_STRUCTDEF_H_


struct mips_cpu_impl {
    uint32_t pc;
    uint32_t pcNext;

    uint32_t regs[32];
    uint32_t HI;
    uint32_t LO;

    mips_mem_h mem;

    unsigned logLevel;
    FILE *logDst;

};

#endif /* MIPS_CPU_STRUCTDEF_H_ */
