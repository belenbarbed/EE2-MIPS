/*
 * test_mips_tests.cpp
 *
 *  Created on: 25 Oct 2016
 *      Author: bb2115
 */

#include "test_mips_tests.h"
#include <iostream>
#include <cmath>

using namespace std;

void setupR(mips_cpu_h cpu, mips_mem_h mem, uint32_t instr,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest, uint32_t &got){

	uint8_t buffer[4];
	buffer[0]=(instr>>24)&0xFF;
	buffer[1]=(instr>>16)&0xFF;
	buffer[2]=(instr>> 8)&0xFF;
	buffer[3]=(instr>> 0)&0xFF;

	uint32_t pc;
	mips_error tmp = mips_cpu_get_pc(cpu, &pc);

	if(tmp!=mips_Success){
		fprintf(stderr, "mips_cpu_get_pc : failed.\n");
		exit(1);
	}

	mips_error e=mips_mem_write(
		mem,	        //!< Handle to target memory
		pc,	    		//!< Byte address to start transaction at
		4,	            //!< Number of bytes to transfer
		buffer	        //!< Receives the target bytes
	);

	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_write : failed.\n");
		exit(1);
	}

	// 2 - put register values in cpu
	e = mips_cpu_set_register(cpu, reg1, n1);
	e = mips_cpu_set_register(cpu, reg2, n2);

	// 3 - step CPU
	e=mips_cpu_step(cpu);
	if(e!=mips_Success){
		fprintf(stderr, "mips_cpu_step : failed.\n");
		exit(1);
	}

	// 4 -Check the result
	e = mips_cpu_get_register(cpu, regdest, &got);

}

void setupI(mips_cpu_h cpu, mips_mem_h mem, uint32_t instr,
		uint32_t reg1, uint32_t n1,
		uint32_t regdest, uint32_t &got)
{

	uint8_t buffer[4];
	buffer[0]=(instr>>24)&0xFF;
	buffer[1]=(instr>>16)&0xFF;
	buffer[2]=(instr>> 8)&0xFF;
	buffer[3]=(instr>> 0)&0xFF;

	uint32_t pc;
	mips_error tmp = mips_cpu_get_pc(cpu, &pc);

	if(tmp!=mips_Success){
		fprintf(stderr, "mips_cpu_get_pc : failed.\n");
		exit(1);
	}

	mips_error e=mips_mem_write(
		mem,	        //!< Handle to target memory
		pc,	    		//!< Byte address to start transaction at
		4,	            //!< Number of bytes to transfer
		buffer	        //!< Receives the target bytes
	);

	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_write : failed.\n");
		exit(1);
	}

	// 2 - put register values in cpu
	e=mips_cpu_set_register(cpu, reg1, n1);

	// 3 - step CPU
	e=mips_cpu_step(cpu);
	if(e!=mips_Success){
		fprintf(stderr, "mips_cpu_step : failed.\n");
		exit(1);
	}

	// 4 -Check the result
	e=mips_cpu_get_register(cpu, regdest, &got);

}

void setupB(mips_cpu_h cpu, mips_mem_h mem, uint32_t instr,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t &gotpc, uint32_t &gotpcn){

	uint8_t buffer[4];
	buffer[0]=(instr>>24)&0xFF;
	buffer[1]=(instr>>16)&0xFF;
	buffer[2]=(instr>> 8)&0xFF;
	buffer[3]=(instr>> 0)&0xFF;

	uint32_t pc;
	mips_error tmp = mips_cpu_get_pc(cpu, &pc);

	if(tmp!=mips_Success){
		fprintf(stderr, "mips_cpu_get_pc : failed.\n");
		exit(1);
	}

	mips_error e=mips_mem_write(
		mem,	        //!< Handle to target memory
		pc,	    		//!< Byte address to start transaction at
		4,	            //!< Number of bytes to transfer
		buffer	        //!< Receives the target bytes
	);

	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_write : failed.\n");
		exit(1);
	}

	// 2 - put register values in cpu
	e = mips_cpu_set_register(cpu, reg1, n1);
	e = mips_cpu_set_register(cpu, reg2, n2);

	// 3 - step CPU
	e=mips_cpu_step(cpu);
	if(e!=mips_Success){
		fprintf(stderr, "mips_cpu_step : failed.\n");
		exit(1);
	}

	// 4 -Check the pc
	e = mips_cpu_get_pc(cpu, &gotpc);

	// 5 -Check pcNext with sll 0, 0, 0
	for(int i = 0; i < 4; i++){
		buffer[i]=0;
	}
	e=mips_mem_write(
			mem,	        //!< Handle to target memory
			gotpc,	    	//!< Byte address to start transaction at
			4,	            //!< Number of bytes to transfer
			buffer	        //!< Receives the target bytes
	);
	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_write : failed.\n");
		exit(1);
	}
	e=mips_cpu_step(cpu);
	if(e!=mips_Success){
		fprintf(stderr, "mips_cpu_step : failed.\n");
		exit(1);
	}
	e = mips_cpu_get_pc(cpu, &gotpcn);

}

void setupJ(mips_cpu_h cpu, mips_mem_h mem, uint32_t instr,
		uint32_t &gotpc, uint32_t &gotpcn){

	uint8_t buffer[4];
	buffer[0]=(instr>>24)&0xFF;
	buffer[1]=(instr>>16)&0xFF;
	buffer[2]=(instr>> 8)&0xFF;
	buffer[3]=(instr>> 0)&0xFF;

	uint32_t pc;
	mips_error tmp = mips_cpu_get_pc(cpu, &pc);

	if(tmp!=mips_Success){
		fprintf(stderr, "mips_cpu_get_pc : failed.\n");
		exit(1);
	}

	mips_error e=mips_mem_write(
		mem,	        //!< Handle to target memory
		pc,	    		//!< Byte address to start transaction at
		4,	            //!< Number of bytes to transfer
		buffer	        //!< Receives the target bytes
	);

	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_write : failed.\n");
		exit(1);
	}

	e = mips_cpu_step(cpu);
	if(e!=mips_Success){
		fprintf(stderr, "mips_cpu_step : failed.\n");
		exit(1);
	}

	// 4 -Check the pc
	e = mips_cpu_get_pc(cpu, &gotpc);

	// 5 -Check pcNext with sll 0, 0, 0
	for(int i = 0; i < 4; i++){
		buffer[i]=0;
	}
	e=mips_mem_write(
			mem,	        //!< Handle to target memory
			gotpc,	    	//!< Byte address to start transaction at
			4,	            //!< Number of bytes to transfer
			buffer	        //!< Receives the target bytes
	);
	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_write : failed.\n");
		exit(1);
	}
	e=mips_cpu_step(cpu);
	if(e!=mips_Success){
		fprintf(stderr, "mips_cpu_step : failed.\n");
		exit(1);
	}
	e = mips_cpu_get_pc(cpu, &gotpcn);

}


void testadd(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t reg2, int32_t n2,
		uint32_t regdest){

	int testId = mips_test_begin_test("add");

	uint32_t instr =
		(0ul << 26)
		|
		(reg1 << 21)
		|
		(reg2 << 16)
		|
		(regdest << 11)
		|
		(0ul << 6)
		|
		(0b100000ul << 0);

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			regdest, got);

	int32_t gotsigned = got;

	int passed;
	if (regdest == 0){
		passed = (gotsigned == 0);
	} else {
		passed = (gotsigned == (n1+n2));
	}

	mips_test_end_test(testId, passed, "add failed");

}

void testaddi(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint16_t imm,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("addi");

	uint32_t instr =
	        (0b001000 << 26)
	        |
	        (reg1 << 21)
	        |
	        (regdest << 16)
	        |
	        (imm << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			reg1, n1,
			regdest, got);

	int16_t immsig = imm;
	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1+immsig));
	}

	mips_test_end_test(testId, passed, "addi failed");

}

void testaddiu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint16_t imm,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("addiu");

	uint32_t instr =
			(0b001001 << 26)
			|
			(reg1 << 21)
			|
			(regdest << 16)
			|
			(imm << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			reg1, n1,
			regdest, got);

	int16_t immsig = imm;
	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1+immsig));
	}

	mips_test_end_test(testId, passed, "addiu failed");

}

void testaddu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t reg2, int32_t n2,
		uint32_t regdest)
{

    int testId = mips_test_begin_test("addu");

    uint32_t instr =
        (0ul << 26) // opcode = 0
        |
        (reg1 << 21) //   srca = r4
        |
        (reg2 << 16) //   srcb = r5
        |
        (regdest << 11) //   dst  = r3
        |
        (0ul << 6) //   shift = 0
        |
        (0x21 << 0);// fncode = 21

    uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1+n2));
	}

	mips_test_end_test(testId, passed, "addu failed");

}

void testand(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("and");

	uint32_t instr =
		(0ul << 26) // opcode = 0
		|
		(reg1 << 21) //   srca = r4
		|
		(reg2 << 16) //   srcb = r5
		|
		(regdest << 11) //   dst  = r3
		|
		(0ul << 6) //   shift = 0
		|
		(0x24 << 0);// fncode = 24

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 and n2));
	}

	mips_test_end_test(testId, passed, "and failed");

}

void testandi(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint16_t imm,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("andi");

	uint32_t instr =
			(0b001100 << 26)
			|
			(reg1 << 21)
			|
			(regdest << 16)
			|
			(imm << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			reg1, n1,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 and imm));
	}

	mips_test_end_test(testId, passed, "andi failed");

}

void testbeq(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t off)
{

	int testId = mips_test_begin_test("beq");

	uint32_t instr =
			(0b000100 << 26)
			|
			(reg1 << 21)
			|
			(reg2 << 16)
			|
			(off << 0);

	uint32_t gotpc;
	uint32_t gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);
	int32_t offs = off;
	offs = (offs << 2);

	setupB(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			gotpc, gotpcn);

	int passed;
	if(n1 == n2){
		passed = ((gotpcn == (pc + 4 + offs)) && (gotpc == pc + 4));
	} else {
		passed = ((gotpcn == (pc + 8)) && (gotpc == pc + 4));
	}

	mips_test_end_test(testId, passed, "beq failed");

}

void testbgez(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off)
{

	int testId = mips_test_begin_test("bgez");

	uint32_t instr =
			(0b000001 << 26)
			|
			(reg1 << 21)
			|
			(1ul << 16)
			|
			(off << 0);

	uint32_t gotpc;
	uint32_t gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);
	off = (off << 2);
	int32_t offs = off;

	setupB(cpu, mem, instr,
			reg1, n1,
			0, 0,
			gotpc, gotpcn);

	int passed;
	int32_t n1new = n1;
	if(n1new >= 0){
		passed = ((gotpcn == (pc + 4 + offs)) && (gotpc == pc + 4));
	} else {
		passed = ((gotpcn == (pc + 8)) && (gotpc == pc + 4));
	}

	mips_test_end_test(testId, passed, "bgez failed");

}

void testbgezal(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off)
{

	int testId = mips_test_begin_test("bgezal");

	uint32_t instr =
			(0b000001 << 26)
			|
			(reg1 << 21)
			|
			(0b10001 << 16)
			|
			(off << 0);

	uint32_t gotpc;
	uint32_t gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);
	off = (off << 2);
	int32_t offs = off;

	setupB(cpu, mem, instr,
			reg1, n1,
			0, 0,
			gotpc, gotpcn);

	uint32_t reg31;
	mips_error e = mips_cpu_get_register(cpu, 31, &reg31);
	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_read : failed.\n");
		exit(1);
	}

	int passed;
	int32_t n1new = n1;
	if(n1new >= 0){
		passed = ((gotpcn == (pc + 4 + offs)) && (gotpc == pc + 4) && (reg31 == (pc + 8)));
	} else {
		passed = ((gotpcn == (pc + 8)) && (gotpc == pc + 4));
	}

	mips_test_end_test(testId, passed, "bgezal failed");

}

void testbgtz(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off)
{

	int testId = mips_test_begin_test("bgtz");

	uint32_t instr =
			(0b000111 << 26)
			|
			(reg1 << 21)
			|
			(0 << 16)
			|
			(off << 0);

	uint32_t gotpc;
	uint32_t gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);
	off = (off << 2);
	int32_t offs = off;

	setupB(cpu, mem, instr,
			reg1, n1,
			0, 0,
			gotpc, gotpcn);

	int passed;
	int32_t n1new = n1;
	if(n1new > 0){
		passed = ((gotpcn == (pc + 4 + offs)) && (gotpc == pc + 4));
	} else {
		passed = ((gotpcn == (pc + 8)) && (gotpc == pc + 4));
	}

	mips_test_end_test(testId, passed, "bgtz failed");

}

void testblez(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off)
{

	int testId = mips_test_begin_test("blez");

	uint32_t instr =
			(0b000110 << 26)
			|
			(reg1 << 21)
			|
			(0 << 16)
			|
			(off << 0);

	uint32_t gotpc;
	uint32_t gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);
	int32_t offs = off;
	offs = (offs << 2);

	setupB(cpu, mem, instr,
			reg1, n1,
			0, 0,
			gotpc, gotpcn);

	int passed;
	int32_t n1new = n1;
	if(n1new <= 0){
		passed = ((gotpcn == (pc + 4 + offs)) && (gotpc == pc + 4));
	} else {
		passed = ((gotpcn == (pc + 8)) && (gotpc == pc + 4));
	}

	mips_test_end_test(testId, passed, "blez failed");

}

void testbltz(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off)
{

	int testId = mips_test_begin_test("bltz");

	uint32_t instr =
			(0b000001 << 26)
			|
			(reg1 << 21)
			|
			(0 << 16)
			|
			(off << 0);

	uint32_t gotpc;
	uint32_t gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);
	int32_t offs = off;
	offs = (offs << 2);

	setupB(cpu, mem, instr,
			reg1, n1,
			0, 0,
			gotpc, gotpcn);

	int passed;
	int32_t n1new = n1;
	if(n1new < 0){
		passed = ((gotpcn == (pc + 4 + offs)) && (gotpc == pc + 4));
	} else {
		passed = ((gotpcn == (pc + 8)) && (gotpc == pc + 4));
	}

	mips_test_end_test(testId, passed, "bltz failed");

}

void testbltzal(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t off)
{

	int testId = mips_test_begin_test("bltzal");

	uint32_t instr =
			(0b000001 << 26)
			|
			(reg1 << 21)
			|
			(0b10000 << 16)
			|
			(off << 0);

	uint32_t gotpc;
	uint32_t gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);
	int32_t offs = off;
	offs = (offs << 2);

	setupB(cpu, mem, instr,
			reg1, n1,
			0, 0,
			gotpc, gotpcn);

	uint32_t reg31;
	mips_error e = mips_cpu_get_register(cpu, 31, &reg31);
	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_read : failed.\n");
		exit(1);
	}

	int passed;
	int32_t n1new = n1;
	if(n1new < 0){
		passed = ((gotpcn == (pc + 4 + offs)) && (gotpc == pc + 4) && (reg31 == (pc + 8)));
	} else {
		passed = ((gotpcn == (pc + 8)) && (gotpc == pc + 4));
	}

	mips_test_end_test(testId, passed, "bltzal failed");

}

void testbne(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t off)
{

	int testId = mips_test_begin_test("bne");

	uint32_t instr =
			(0b000101 << 26)
			|
			(reg1 << 21)
			|
			(reg2 << 16)
			|
			(off << 0);

	uint32_t gotpc;
	uint32_t gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);
	int32_t offs = off;
	offs = (offs << 2);

	setupB(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			gotpc, gotpcn);

	int passed;
	if(n1 != n2){
		passed = ((gotpcn == (pc + 4 + offs)) && (gotpc == pc + 4));
	} else {
		passed = ((gotpcn == (pc + 8)) && (gotpc == pc + 4));
	}

	mips_test_end_test(testId, passed, "bne failed");

}

void testj(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t address)
{

	int testId = mips_test_begin_test("j");

	address = address & 0x3FFFFFF;

	uint32_t instr =
			(0b000010 << 26)
			|
			(address);

	uint32_t gotpc, gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);

	setupJ(cpu, mem, instr,
			gotpc, gotpcn);

	address = (address << 2);

	int passed = ((gotpc == (pc + 4)) && (gotpcn == address));

	mips_test_end_test(testId, passed, "j failed");

}

void testjal(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t address)
{

	int testId = mips_test_begin_test("jal");

	address = address & 0x3FFFFFF;

	uint32_t instr =
			(0b000011 << 26)
			|
			(address);

	uint32_t gotpc, gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);

	setupJ(cpu, mem, instr,
			gotpc, gotpcn);

	address = (address << 2);

	uint32_t reg31;
	mips_error e = mips_cpu_get_register(cpu, 31, &reg31);
	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_read : failed.\n");
		exit(1);
	}

	int passed = ((gotpc == (pc + 4)) && (gotpcn == address) && (reg31 == (pc + 8)));

	mips_test_end_test(testId, passed, "jal failed");

}

void testjalr(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t address_reg, uint32_t address,
		uint32_t dst_reg)
{

	int testId = mips_test_begin_test("jalr");

	uint32_t instr =
			(0ul << 26)
			|
			(address_reg << 21)
			|
			(dst_reg << 11)
			|
			(0b001001);

	uint32_t gotpc, gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);

	mips_error e = mips_cpu_set_register(cpu, address_reg, address);
	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_write : failed.\n");
		exit(1);
	}

	setupJ(cpu, mem, instr,
			gotpc, gotpcn);


	uint dst;
	e = mips_cpu_get_register(cpu, dst_reg, &dst);
	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_read : failed.\n");
		exit(1);
	}

//	cout << "the pc should be " << pc+4 << endl;
//	cout << "the pc is " << gotpc << endl;
//	cout << "the pcNext should be " << address << endl;
//	cout << "the pcNext is " << gotpcn << endl;

	int passed = ((gotpc == (pc + 4)) && (gotpcn == address) && (dst == (pc + 8)));

	mips_test_end_test(testId, passed, "jalr failed");

}

void testjr(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t address_reg, uint32_t address)
{

	int testId = mips_test_begin_test("jr");

	uint32_t instr =
			(0ul << 26)
			|
			(address_reg << 21)
			|
			(0b001000);

	uint32_t gotpc, gotpcn;
	uint32_t pc;
	mips_cpu_get_pc(cpu, &pc);

	mips_error e = mips_cpu_set_register(cpu, address_reg, address);
	if(e!=mips_Success){
		fprintf(stderr, "mips_mem_write : failed.\n");
		exit(1);
	}

	setupJ(cpu, mem, instr,
			gotpc, gotpcn);

	int passed = ((gotpc == (pc + 4)) && (gotpcn == address));

	mips_test_end_test(testId, passed, "jr failed");

}

void testlb(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst)
{

	int testId = mips_test_begin_test("lb");

	uint32_t instr =
			(0b100000 << 26)
			|
			(base_reg << 21)
			|
			(dst << 16)
			|
			(off);

	uint32_t got;
	setupI(cpu, mem, instr,
			base_reg, base,
			dst, got);

	uint8_t data;

	mips_error e1 = mips_mem_read(
		    mem,		//!< Handle to target memory
		    (off + base),	//!< Byte address to start transaction at
		    1,				//!< Number of bytes to transfer
		    &data			//!< Receives the target bytes
		);

	int32_t data2 = data;

	int passed;
	if (dst == 0){
		passed = (got == 0);
	} else {
		passed = (got == data2);
	}

	mips_test_end_test(testId, passed, "lb failed");

}

void testlbu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst)
{

	int testId = mips_test_begin_test("lbu");

	uint32_t instr =
			(0b100100 << 26)
			|
			(base_reg << 21)
			|
			(dst << 16)
			|
			(off);

	uint32_t got;
	setupI(cpu, mem, instr,
			base_reg, base,
			dst, got);

	uint8_t data;

	mips_error e1 = mips_mem_read(
		    mem,		//!< Handle to target memory
		    (off + base),	//!< Byte address to start transaction at
		    1,				//!< Number of bytes to transfer
		    &data			//!< Receives the target bytes
		);

	uint32_t data2 = data;

	int passed;
	if (dst == 0){
		passed = (got == 0);
	} else {
		passed = (got == data2);
	}

	mips_test_end_test(testId, passed, "lbu failed");

}

void testlh(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst)
{

	int testId = mips_test_begin_test("lh");

	uint32_t instr =
			(0b100001 << 26)
			|
			(base_reg << 21)
			|
			(dst << 16)
			|
			(off);

	uint32_t got;
	setupI(cpu, mem, instr,
			base_reg, base,
			dst, got);

	uint8_t data[2] = {0};

	mips_error e1 = mips_mem_read(
		    mem,		//!< Handle to target memory
		    (off + base),	//!< Byte address to start transaction at
		    2,				//!< Number of bytes to transfer
		    data			//!< Receives the target bytes
		);

	uint32_t tmp0 = data[0];
	uint32_t tmp1 = data[1];

	uint32_t data2 =
			(tmp0 << 8)
			|
			(tmp1 << 0);

	int passed;
	if (dst == 0){
		passed = (got == 0);
	} else {
		passed = ((got & 0xFFFF) == data2);
	}

	mips_test_end_test(testId, passed, "lh failed");

}

void testlhu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst)
{

	int testId = mips_test_begin_test("lhu");

	uint32_t instr =
			(0b100001 << 26)
			|
			(base_reg << 21)
			|
			(dst << 16)
			|
			(off);

	uint32_t got;
	setupI(cpu, mem, instr,
			base_reg, base,
			dst, got);

	uint8_t data[2] = {0};

	mips_error e1 = mips_mem_read(
		    mem,		//!< Handle to target memory
		    (off + base),	//!< Byte address to start transaction at
		    2,				//!< Number of bytes to transfer
		    data			//!< Receives the target bytes
		);

	uint32_t tmp0 = data[0];
	uint32_t tmp1 = data[1];

	uint32_t data2 =
			(tmp0 << 8)
			|
			(tmp1 << 0);

	int passed;
	if (dst == 0){
		passed = (got == 0);
	} else {
		passed = ((got & 0xFFFF) == data2);
	}

	mips_test_end_test(testId, passed, "lhu failed");

}

void testlui(mips_mem_h mem, mips_cpu_h cpu,
		uint16_t imm,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("lui");

	uint32_t instr =
			(0b001111 << 26)
			|
			(0 << 21)
			|
			(regdest << 16)
			|
			(imm << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			0, 0,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (imm << 16));
	}

	mips_test_end_test(testId, passed, "lui failed");

}

void testlw(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint16_t off,
		uint32_t dst)
{

	int testId = mips_test_begin_test("lw");

	uint32_t instr =
			(0b100011 << 26)
			|
			(base_reg << 21)
			|
			(dst << 16)
			|
			(off);

	uint32_t got;
	setupI(cpu, mem, instr,
			base_reg, base,
			dst, got);

	uint8_t data[4] = {0};

	mips_error e1 = mips_mem_read(
		    mem,		//!< Handle to target memory
		    (off + base),	//!< Byte address to start transaction at
		    4,				//!< Number of bytes to transfer
		    data			//!< Receives the target bytes
		);

	uint32_t tmp0 = data[0];
	uint32_t tmp1 = data[1];
	uint32_t tmp2 = data[2];
	uint32_t tmp3 = data[3];

	uint32_t data2 =
			(tmp0 << 24)
			|
			(tmp1 << 16)
			|
			(tmp2 << 8)
			|
			(tmp3);

	int passed;
	if (dst == 0){
		passed = (got == 0);
	} else {
		passed = (got == data2);
	}

	mips_test_end_test(testId, passed, "lw failed");

}

void testor(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("or");

	uint32_t instr =
		(0ul << 26) // opcode = 0
		|
		(reg1 << 21) //   srca = r4
		|
		(reg2 << 16) //   srcb = r5
		|
		(regdest << 11) //   dst  = r3
		|
		(0ul << 6) //   shift = 0
		|
		(0b100101 << 0);// fncode = 24

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 or n2));
	}

	mips_test_end_test(testId, passed, "or failed");

}

void testori(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint16_t imm,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("ori");

	uint32_t instr =
			(0b001101 << 26)
			|
			(reg1 << 21)
			|
			(regdest << 16)
			|
			(imm << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			reg1, n1,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 or imm));
	}

	mips_test_end_test(testId, passed, "ori failed");

}

void testsb(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint32_t src_reg, uint32_t src,
		uint16_t off)
{

	int testId = mips_test_begin_test("sb");

	uint32_t instr =
			(0b101000 << 26)
			|
			(base_reg << 21)
			|
			(src_reg << 16)
			|
			(off);

	uint32_t got;
	setupR(cpu, mem, instr,
			base_reg, base,
			src_reg, src,
			src, got);

	uint8_t data;

	mips_error e1 = mips_mem_read(
		    mem,			//!< Handle to target memory
		    (off + base),	//!< Byte address to start transaction at
		    1,				//!< Number of bytes to transfer
		    &data			//!< Receives the target bytes
		);

	int32_t data2 = data;

	int passed;
	if (src == 0){
		passed = (got == 0);
	} else {
		passed = ((src & 0xFF) == data2);
	}

	mips_test_end_test(testId, passed, "sb failed");

}

void testsh(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint32_t src_reg, uint32_t src,
		uint16_t off)
{

	int testId = mips_test_begin_test("sh");

	uint32_t instr =
			(0b101001 << 26)
			|
			(base_reg << 21)
			|
			(src_reg << 16)
			|
			(off);

	uint32_t got;
	setupR(cpu, mem, instr,
			base_reg, base,
			src_reg, src,
			src, got);

	uint8_t data[2] = {0};

	mips_error e1 = mips_mem_read(
		    mem,			//!< Handle to target memory
		    (off + base),	//!< Byte address to start transaction at
		    2,				//!< Number of bytes to transfer
		    data			//!< Receives the target bytes
		);

	uint32_t tmp0 = data[0];
	uint32_t tmp1 = data[1];

	uint32_t data2 =
			(tmp0 << 8)
			|
			(tmp1 << 0);

	int passed;
	if (src == 0){
		passed = (got == 0);
	} else {
		passed = ((src & 0xFFFF) == data2);
	}

	mips_test_end_test(testId, passed, "sh failed");

}

void testsll(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t sa,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("sll");

	sa = sa & 0b11111;

	uint32_t instr =
		(0ul << 26) // opcode = 0
		|
		(0 << 21)
		|
		(reg1 << 16)
		|
		(regdest << 11)
		|
		(sa << 6)
		|
		(0 << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			reg1, n1,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 << sa));
	}

	mips_test_end_test(testId, passed, "sll failed");

}

void testsllv(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t sareg, uint32_t sa,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("sllv");

	uint32_t instr =
		(0ul << 26) // opcode = 0
		|
		(sareg << 21)
		|
		(reg1 << 16)
		|
		(regdest << 11)
		|
		(0 << 6)
		|
		(0b000100 << 0);

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			sareg, sa,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 << sa));
	}

	mips_test_end_test(testId, passed, "sllv failed");

}

void testslt(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t reg2, int32_t n2,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("slt");

	uint32_t instr =
		(0ul << 26)
		|
		(reg1 << 21)
		|
		(reg2 << 16)
		|
		(regdest << 11)
		|
		(0ul << 6)
		|
		(0b101010 << 0);

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			regdest, got);

	int passed;
	uint comp = 0;
	if(n1 < n2){
		comp = 1;
	}

	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == comp);
	}

	mips_test_end_test(testId, passed, "slt failed");

}

void testslti(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint16_t imm,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("slti");

	uint32_t instr =
			(0b001010 << 26)
			|
			(reg1 << 21)
			|
			(regdest << 16)
			|
			(imm << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			reg1, n1,
			regdest, got);

	int16_t immsig = imm;
	int passed;
	uint comp = 0;
	if(n1 < immsig){
		comp = 1;
	}


	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == comp);
	}

	mips_test_end_test(testId, passed, "slti failed");

}

void testsltiu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint16_t imm,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("sltiu");

	uint32_t instr =
			(0b001011 << 26)
			|
			(reg1 << 21)
			|
			(regdest << 16)
			|
			(imm << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			reg1, n1,
			regdest, got);

	int passed;
	uint comp = 0;
	if(n1 < imm){
		comp = 1;
	}

	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == comp);
	}

	mips_test_end_test(testId, passed, "sltiu failed");

}

void testsltu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("sltu");

	uint32_t instr =
		(0ul << 26)
		|
		(reg1 << 21)
		|
		(reg2 << 16)
		|
		(regdest << 11)
		|
		(0ul << 6)
		|
		(0b101011 << 0);

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			regdest, got);

	int passed;
	uint comp = 0;
	if(n1 < n2){
		comp = 1;
	}

	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == comp);
	}

	mips_test_end_test(testId, passed, "sltu failed");

}

void testsra(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t sa,
		uint32_t regdest)
{

	sa = sa & 0b11111;

	int testId = mips_test_begin_test("sra");

	uint32_t instr =
		(0ul << 26)
		|
		(0 << 21)
		|
		(reg1 << 16)
		|
		(regdest << 11)
		|
		(sa << 6)
		|
		(0b11 << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			reg1, n1,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 >> sa));
	}

	mips_test_end_test(testId, passed, "sra failed");

}

void testsrav(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t sareg, uint32_t sa,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("srav");

	uint32_t instr =
		(0ul << 26) // opcode = 0
		|
		(sareg << 21)
		|
		(reg1 << 16)
		|
		(regdest << 11)
		|
		(0 << 6)
		|
		(0b000111 << 0);

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			sareg, sa,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 >> sa));
	}

	mips_test_end_test(testId, passed, "srav failed");

}

void testsrl(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t sa,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("srl");

	sa = sa & 0b11111;

	uint32_t instr =
		(0ul << 26)
		|
		(0 << 21)
		|
		(reg1 << 16)
		|
		(regdest << 11)
		|
		(sa << 6)
		|
		(0b10 << 0);

	uint32_t got;
	setupI(cpu, mem, instr,
			reg1, n1,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 >> sa));
	}

	mips_test_end_test(testId, passed, "srl failed");

}

void testsrlv(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t sareg, uint32_t sa,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("srlv");

	uint32_t instr =
		(0ul << 26) // opcode = 0
		|
		(sareg << 21)
		|
		(reg1 << 16)
		|
		(regdest << 11)
		|
		(0 << 6)
		|
		(0b000110 << 0);

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			sareg, sa,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 >> sa));
	}

	mips_test_end_test(testId, passed, "srlv failed");

}

void testsub(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, int32_t n1,
		uint32_t reg2, int32_t n2,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("sub");

	uint32_t instr =
		(0ul << 26)
		|
		(reg1 << 21)
		|
		(reg2 << 16)
		|
		(regdest << 11)
		|
		(0ul << 6)
		|
		(0b100010 << 0);

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1-n2));
	}

	mips_test_end_test(testId, passed, "sub failed");

}

void testsubu(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("subu");

	uint32_t instr =
		(0ul << 26) // opcode = 0
		|
		(reg1 << 21) //   srca = r4
		|
		(reg2 << 16) //   srcb = r5
		|
		(regdest << 11) //   dst  = r3
		|
		(0ul << 6) //   shift = 0
		|
		(0x23 << 0);// fncode = 23

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1-n2));
	}

	mips_test_end_test(testId, passed, "subu failed");

}

void testsw(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t base_reg, uint32_t base,
		uint32_t src_reg, uint32_t src,
		uint16_t off)
{

	int testId = mips_test_begin_test("sw");

	uint32_t instr =
			(0b101011 << 26)
			|
			(base_reg << 21)
			|
			(src_reg << 16)
			|
			(off);

	uint32_t got;
	setupR(cpu, mem, instr,
			base_reg, base,
			src_reg, src,
			src, got);

	uint8_t data[4] = {0};

	mips_error e1 = mips_mem_read(
		    mem,			//!< Handle to target memory
		    (off + base),	//!< Byte address to start transaction at
		    4,				//!< Number of bytes to transfer
		    data			//!< Receives the target bytes
		);

	uint32_t tmp0 = data[0];
	uint32_t tmp1 = data[1];
	uint32_t tmp2 = data[2];
	uint32_t tmp3 = data[3];

	uint32_t data2 =
			(tmp0 << 24)
			|
			(tmp1 << 16)
			|
			(tmp2 << 8)
			|
			(tmp3);

	int passed;
	if (src == 0){
		passed = (got == 0);
	} else {
		passed = (src == data2);
	}

	mips_test_end_test(testId, passed, "sw failed");

}

void testxor(mips_mem_h mem, mips_cpu_h cpu,
		uint32_t reg1, uint32_t n1,
		uint32_t reg2, uint32_t n2,
		uint32_t regdest)
{

	int testId = mips_test_begin_test("xor");

	uint32_t instr =
		(0ul << 26) // opcode = 0
		|
		(reg1 << 21) //   srca = r1
		|
		(reg2 << 16) //   srcb = r2
		|
		(regdest << 11) //   dst  = r3
		|
		(0ul << 6) //   shift = 0
		|
		(0x26 << 0);// fncode = 26

	uint32_t got;
	setupR(cpu, mem, instr,
			reg1, n1,
			reg2, n2,
			regdest, got);

	int passed;
	if (regdest == 0){
		passed = (got == 0);
	} else {
		passed = (got == (n1 xor n2));
	}

	mips_test_end_test(testId, passed, "xor  failed");

}
