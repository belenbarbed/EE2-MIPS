/*
 * test_mips_tests.h
 *
 *  Created on: 25 Oct 2016
 *      Author: bb2115
 */

#ifndef SRC_BB2115_TEST_MIPS_TESTS_H_
#define SRC_BB2115_TEST_MIPS_TESTS_H_

#include "mips.h"

void setupR(mips_cpu_h cpu, mips_mem_h mem, uint32_t instr,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest, uint32_t &got);

void setupI(mips_cpu_h cpu, mips_mem_h mem, uint32_t instr,
		uint32_t reg1, uint32_t n1,
		uint32_t regdest, uint32_t &got);

void setupB(mips_cpu_h cpu, mips_mem_h mem, uint32_t instr,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t &gotpc, uint32_t &gotpcn);

void setupJ(mips_cpu_h cpu, mips_mem_h mem, uint32_t instr,
		uint32_t &gotpc, uint32_t &gotpcn);

void testadd(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t reg2, int32_t n2,
		uint32_t regdest);
void testaddi(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint16_t imm,
		uint32_t regdest);
void testaddiu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint16_t imm,
		uint32_t regdest);
void testaddu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t reg2, int32_t n2,
		uint32_t regdest);
void testand(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest);
void testandi(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint16_t imm,
		uint32_t regdest);
void testbeq(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t off);
void testbgez(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off);
void testbgezal(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off);
void testbgtz(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off);
void testblez(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off);
void testbltz(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off);
void testbltzal(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off);
void testbne(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t off);
void testj(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t address);
void testjal(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t address);
void testjalr(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t address_reg, uint32_t address,
		uint32_t dst_reg);
void testjr(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t address_reg, uint32_t address);
void testlb(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst);
void testlbu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst);
void testlh(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst);
void testlhu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst);
void testlui(mips_mem_h mem, mips_cpu_h cpu,
		uint16_t imm,
		uint32_t regdest);
void testlw(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst);
void testor(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest);
void testori(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint16_t imm,
		uint32_t regdest);
void testsb(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint32_t src_reg, uint32_t src,
		uint16_t off);
void testsh(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint32_t src_reg, uint32_t src,
		uint16_t off);
void testsll(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t sa,
		uint32_t regdest);
void testsllv(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t sareg, uint32_t sa,
		uint32_t regdest);
void testslt(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t reg2, int32_t n2,
		uint32_t regdest);
void testslti(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint16_t imm,
		uint32_t regdest);
void testsltiu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint16_t imm,
		uint32_t regdest);
void testsltu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest);
void testsra(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t sa,
		uint32_t regdest);
void testsrav(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t sareg, uint32_t sa,
		uint32_t regdest);
void testsrl(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t sa,
		uint32_t regdest);
void testsrlv(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t sareg, uint32_t sa,
		uint32_t regdest);
void testsub(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t reg2, int32_t n2,
		uint32_t regdest);
void testsubu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest);
void testsw(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint32_t src_reg, uint32_t src,
		uint16_t off);
void testxor(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest);



#endif /* SRC_BB2115_TEST_MIPS_TESTS_H_ */
