/*
 * instrTable.h
 *
 *  Created on: 21 Oct 2016
 *      Author: bb2115
 */

#ifndef MIPS_CPU_INSTRTABLE_H_
#define MIPS_CPU_INSTRTABLE_H_

#include "mips.h"
#include "mips_cpu_structdef.h"
#include <cmath>


typedef mips_error(*op_t)(mips_cpu_h, uint32_t);

struct TableEntry{

	TableEntry();
	TableEntry(uint32_t opCode_in, uint32_t fnCode_in, op_t name);

	uint32_t opCode;
	uint32_t fnCode;
	op_t name;
};

mips_error mips_cpu_set_pcNext(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	uint32_t pc,		//!< Address of the next instruction to execute.
	uint32_t pcNext
);

uint32_t to_big(const uint8_t *pData);

mips_error decoding(
	mips_cpu_h state,
	uint32_t instruction,
	uint32_t opcode,
	uint32_t function
);

mips_error check_errors(mips_error e1, mips_error e2);

mips_error do_add   (mips_cpu_h state, uint32_t instruction);
mips_error do_addi  (mips_cpu_h state, uint32_t instruction);
mips_error do_addiu (mips_cpu_h state, uint32_t instruction);
mips_error do_addu  (mips_cpu_h state, uint32_t instruction);
mips_error do_and   (mips_cpu_h state, uint32_t instruction);
mips_error do_andi  (mips_cpu_h state, uint32_t instruction);
mips_error do_beq   (mips_cpu_h state, uint32_t instruction);
mips_error do_bgez  (mips_cpu_h state, uint32_t instruction);
mips_error do_bgezal(mips_cpu_h state, uint32_t instruction);
mips_error do_bgtz  (mips_cpu_h state, uint32_t instruction);
mips_error do_blez  (mips_cpu_h state, uint32_t instruction);
mips_error do_bltz  (mips_cpu_h state, uint32_t instruction);
mips_error do_bltzal(mips_cpu_h state, uint32_t instruction);
mips_error do_bne   (mips_cpu_h state, uint32_t instruction);
mips_error do_div   (mips_cpu_h state, uint32_t instruction);
mips_error do_divu  (mips_cpu_h state, uint32_t instruction);
mips_error do_j     (mips_cpu_h state, uint32_t instruction);
mips_error do_jal   (mips_cpu_h state, uint32_t instruction);
mips_error do_jalr  (mips_cpu_h state, uint32_t instruction);
mips_error do_jr    (mips_cpu_h state, uint32_t instruction);
mips_error do_lb    (mips_cpu_h state, uint32_t instruction);
mips_error do_lbu   (mips_cpu_h state, uint32_t instruction);
mips_error do_lh    (mips_cpu_h state, uint32_t instruction);
mips_error do_lhu   (mips_cpu_h state, uint32_t instruction);
mips_error do_lui   (mips_cpu_h state, uint32_t instruction);
mips_error do_lw    (mips_cpu_h state, uint32_t instruction);
mips_error do_mfhi  (mips_cpu_h state, uint32_t instruction);
mips_error do_mflo  (mips_cpu_h state, uint32_t instruction);
mips_error do_mthi  (mips_cpu_h state, uint32_t instruction);
mips_error do_mtlo  (mips_cpu_h state, uint32_t instruction);
mips_error do_mult  (mips_cpu_h state, uint32_t instruction);
mips_error do_multu (mips_cpu_h state, uint32_t instruction);
mips_error do_or    (mips_cpu_h state, uint32_t instruction);
mips_error do_ori   (mips_cpu_h state, uint32_t instruction);
mips_error do_sb    (mips_cpu_h state, uint32_t instruction);
mips_error do_sh    (mips_cpu_h state, uint32_t instruction);
mips_error do_sll   (mips_cpu_h state, uint32_t instruction);
mips_error do_sllv  (mips_cpu_h state, uint32_t instruction);
mips_error do_slt   (mips_cpu_h state, uint32_t instruction);
mips_error do_slti  (mips_cpu_h state, uint32_t instruction);
mips_error do_sltiu (mips_cpu_h state, uint32_t instruction);
mips_error do_sltu  (mips_cpu_h state, uint32_t instruction);
mips_error do_sra   (mips_cpu_h state, uint32_t instruction);
mips_error do_srav  (mips_cpu_h state, uint32_t instruction);
mips_error do_srl   (mips_cpu_h state, uint32_t instruction);
mips_error do_srlv  (mips_cpu_h state, uint32_t instruction);
mips_error do_sub   (mips_cpu_h state, uint32_t instruction);
mips_error do_subu  (mips_cpu_h state, uint32_t instruction);
mips_error do_sw    (mips_cpu_h state, uint32_t instruction);
mips_error do_xor   (mips_cpu_h state, uint32_t instruction);

mips_error do_lwl   (mips_cpu_h state, uint32_t instruction);
mips_error do_lwr   (mips_cpu_h state, uint32_t instruction);

#endif /* MIPS_CPU_INSTRTABLE_H_ */
