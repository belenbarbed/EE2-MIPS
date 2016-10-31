/*
 * instrTable.cpp
 *
 *  Created on: 21 Oct 2016
 *      Author: bb2115
 */

#include "mips_cpu_instrTable.h"
#include <iostream>
using namespace std;

const int table_size = 52;

TableEntry table[table_size] = {
	TableEntry(0b0,      0b0,      (op_t)do_sll),

    TableEntry(0b0,      0b100000, (op_t)do_add),
    TableEntry(0b001000, 0b0,      (op_t)do_addi),
    TableEntry(0b001001, 0b0,      (op_t)do_addiu),
    TableEntry(0b0,      0b100001, (op_t)do_addu),

	TableEntry(0b0,      0b100100, (op_t)do_and),
	TableEntry(0b001100, 0b0,      (op_t)do_andi),

	TableEntry(0b000100, 0b0,      (op_t)do_beq),
	TableEntry(0b000001, 0b0,      (op_t)do_bgez),
	TableEntry(0b000001, 0b0,      (op_t)do_bgezal),
	TableEntry(0b000111, 0b0,      (op_t)do_bgtz),
	TableEntry(0b000110, 0b0,      (op_t)do_blez),
	TableEntry(0b000001, 0b0,      (op_t)do_bltz),
	TableEntry(0b000001, 0b0,      (op_t)do_bltzal),
	TableEntry(0b000101, 0b0,      (op_t)do_bne),

	TableEntry(0b0,      0b011010, (op_t)do_div),
	TableEntry(0b0,      0b011011, (op_t)do_divu),

	TableEntry(0b000010, 0b0,      (op_t)do_j),
	TableEntry(0b000011, 0b0,      (op_t)do_jal),
	TableEntry(0b0     , 0b001001, (op_t)do_jalr),
	TableEntry(0b0     , 0b001000, (op_t)do_jr),

	TableEntry(0b001111, 0b0,      (op_t)do_lui),

	TableEntry(0b100011, 0b0,      (op_t)do_lw),
	TableEntry(0b101011, 0b0,      (op_t)do_sw),
	TableEntry(0b100000, 0b0,      (op_t)do_lb),
	TableEntry(0b100100, 0b0,      (op_t)do_lbu),
	TableEntry(0b101000, 0b0,      (op_t)do_sb),
	TableEntry(0b100001, 0b0,      (op_t)do_lh),
	TableEntry(0b100101, 0b0,      (op_t)do_lhu),
	TableEntry(0b101001, 0b0,      (op_t)do_sh),

	TableEntry(0b0,      0b010000, (op_t)do_mfhi),
	TableEntry(0b0,      0b010010, (op_t)do_mflo),
	TableEntry(0b0,      0b010001, (op_t)do_mthi),
	TableEntry(0b0,      0b010011, (op_t)do_mtlo),

	TableEntry(0b0,      0b011000, (op_t)do_mult),
	TableEntry(0b0,      0b011001, (op_t)do_multu),

	TableEntry(0b0,      0b100101, (op_t)do_or),
	TableEntry(0b001101, 0b0,      (op_t)do_ori),

	TableEntry(0b0,      0b000100, (op_t)do_sllv),

	TableEntry(0b0,      0b101010, (op_t)do_slt),
	TableEntry(0b001010, 0b0,      (op_t)do_slti),
	TableEntry(0b001011, 0b0,      (op_t)do_sltiu),
	TableEntry(0b0,      0b101011, (op_t)do_sltu),

	TableEntry(0b0,      0b000011, (op_t)do_sra),
	TableEntry(0b0,      0b000111, (op_t)do_srav),
	TableEntry(0b0,      0b000010, (op_t)do_srl),
	TableEntry(0b0,      0b000110, (op_t)do_srlv),

	TableEntry(0b0,      0b100010, (op_t)do_sub),
	TableEntry(0b0,      0b100011, (op_t)do_subu),

	TableEntry(0b0,      0b100110, (op_t)do_xor),

	TableEntry(0b100010, 0b0,      (op_t)do_lwl),
	TableEntry(0b100110, 0b0,      (op_t)do_lwr)
};

TableEntry::TableEntry(): opCode(0), fnCode(0), name(NULL) {}
TableEntry::TableEntry(uint32_t opCode_in, uint32_t fnCode_in, op_t name_in): opCode(opCode_in), fnCode(fnCode_in), name(name_in) {}


mips_error decoding(
	mips_cpu_h state,
	uint32_t instruction,
	uint32_t opcode,
	uint32_t function)
{

	if(opcode == 0){
		// R-type instruction
		for(int i = 0; i < table_size; i++){
			if(table[i].fnCode == function){
				return table[i].name(state, instruction);
			}
		}

		fprintf(state->logDst, "instruction not found\n");
		//return mips_ErrorNotImplemented;
		return mips_ExceptionInvalidInstruction;

	} else {
		// I and J-type instruction
		for(int i = 0; i < table_size; i++){
			if(table[i].opCode == opcode){
				return table[i].name(state, instruction);
			}
		}

		fprintf(state->logDst, "instruction not found\n");
		//return mips_ErrorNotImplemented;
		return mips_ExceptionInvalidInstruction;

	}

}

mips_error check_errors(mips_error e1, mips_error e2){

	if(e1 != mips_Success){
		cout << "this be wrong" << endl;
		return mips_ExceptionInvalidAddress;
	} else {
		if(e2 != mips_Success){
			cout << "this be wrong" << endl;
			return mips_ExceptionInvalidAddress;
		} else {
			return mips_Success;
		}
	}

}


mips_error do_add(mips_cpu_h state, uint32_t instruction){

	uint32_t src1 = (instruction>> 21) & 0x1F;
    uint32_t src2 = (instruction>> 16) & 0x1F;
    uint32_t dst  = (instruction>> 11) & 0x1F;

	int32_t va = state->regs[src1];
	int32_t vb = state->regs[src2];
	int32_t res;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "add %u, %u, %u.\n", dst, src1, src2);
	}

	res = va + vb;

	if((va & 0x80000000) == (vb & 0x80000000) && ((va & 0x80000000) != (res & 0x80000000))){
		fprintf(state->logDst, "OVERFLOW\n");
		return mips_ExceptionArithmeticOverflow;
	}

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_addi(mips_cpu_h state, uint32_t instruction){

	int16_t imm = instruction & 0xFFFF;

	uint32_t src = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "addi %u, %u, %d.\n", dst, src, imm);
	}

	int32_t va = state->regs[src];

	int32_t res = va + imm;

	if((va & 0x80000000) == (imm & 0x80000000) && ((va & 0x80000000) != (res & 0x80000000))){
		fprintf(state->logDst, "OVERFLOW\n");
		return mips_ExceptionArithmeticOverflow;
	}

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_addiu(mips_cpu_h state, uint32_t instruction){

	int16_t imm = instruction & 0xFFFF;

	uint32_t src = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "addiu %u, %u, %d.\n", dst, src, imm);
	}

	int32_t va = state->regs[src];

	int32_t res = va + imm;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_addu(mips_cpu_h state, uint32_t instruction){

	uint32_t src1 = (instruction>> 21) & 0x1F;
    uint32_t src2 = (instruction>> 16) & 0x1F;
    uint32_t dst  = (instruction>> 11) & 0x1F;

	int32_t va = state->regs[src1];
	int32_t vb = state->regs[src2];
	int32_t res;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "addu %u, %u, %u.\n", dst, src1, src2);
	}

	res = va + vb;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_and(mips_cpu_h state, uint32_t instruction){

	uint32_t src1     = (instruction>> 21) & 0x1F;
	uint32_t src2     = (instruction>> 16) & 0x1F;
	uint32_t dst      = (instruction>> 11) & 0x1F;

	uint32_t va=state->regs[src1];
	uint32_t vb=state->regs[src2];
	uint32_t res;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "and %u, %u, %u.\n", dst, src1, src2);
	}

	res = va and vb;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_andi(mips_cpu_h state, uint32_t instruction){

	uint16_t imm = instruction & 0xFFFF;

	uint32_t src = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "andi %u, %u, %d.\n", dst, src, imm);
	}

	uint32_t va = state->regs[src];
	uint32_t res = va and imm;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_beq(mips_cpu_h state, uint32_t instruction){

	int32_t off = instruction & 0xFFFF;
	off = (off << 2);

	uint32_t src1 = (instruction>> 21) & 0x1F;
	uint32_t src2 = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "beq %u, %u, %d.\n", src1, src2, off);
	}

	int32_t va = state->regs[src1];
	int32_t vb = state->regs[src2];

	mips_error e = mips_ExceptionBreak;

	if(va == vb){
		uint address = state->pcNext + off;
		e = mips_cpu_set_pcNext(state, state->pcNext, address);
	} else {
		e = mips_cpu_set_pc(state, state->pcNext);
	}

	return e;

}

mips_error do_bgez(mips_cpu_h state, uint32_t instruction){

	uint32_t type = (instruction>> 16) & 0x1F;
	if(type == 0b10000){
		return do_bltzal(state, instruction);
	}else if(type == 0b10001){
		return do_bgezal(state, instruction);
	}else if(type == 0){
		return do_bltz(state, instruction);
	}

	int32_t off = instruction & 0xFFFF;
	off = (off << 2);

	uint32_t src = (instruction>> 21) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "bgez %u, %d.\n", src, off);
	}

	int32_t va = state->regs[src];

	mips_error e = mips_ExceptionBreak;

	if(va >= 0){
		uint address = state->pcNext + off;
		e = mips_cpu_set_pcNext(state, state->pcNext, address);
	} else {
		e = mips_cpu_set_pc(state, state->pcNext);
	}

	return e;

}

mips_error do_bgezal(mips_cpu_h state, uint32_t instruction){

	int32_t off = instruction & 0xFFFF;
	off = (off << 2);

	uint32_t src = (instruction>> 21) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "bgezal %u, %d.\n", src, off);
	}

	int32_t va = state->regs[src];

	if(va >= 0){
		uint address = state->pcNext + off;
		mips_error e1 = mips_cpu_set_register(state, 31, (state->pc + 8));
		mips_error e2 = mips_cpu_set_pcNext(state, state->pcNext, address);
		return check_errors(e1, e2);
	} else {
		mips_error e = mips_cpu_set_pc(state, state->pcNext);
		return e;
	}

}

mips_error do_bgtz(mips_cpu_h state, uint32_t instruction){

	int32_t off = instruction & 0xFFFF;
	off = (off << 2);

	uint32_t src = (instruction>> 21) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "bgtz %u, %d.\n", src, off);
	}

	int32_t va = state->regs[src];

	mips_error e = mips_ExceptionBreak;

	if(va > 0){
		uint address = state->pcNext + off;
		e = mips_cpu_set_pcNext(state, state->pcNext, address);
	} else {
		e = mips_cpu_set_pc(state, state->pcNext);
	}

	return e;

}

mips_error do_blez(mips_cpu_h state, uint32_t instruction){

	int32_t off = instruction & 0xFFFF;
	off = (off << 2);

	uint32_t src = (instruction>> 21) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "blez %u, %d.\n", src, off);
	}

	int32_t va = state->regs[src];

	mips_error e = mips_ExceptionBreak;

	if(va <= 0){
		uint address = state->pcNext + off;
		e = mips_cpu_set_pcNext(state, state->pcNext, address);
	} else {
		e = mips_cpu_set_pc(state, state->pcNext);
	}

	return e;

}

mips_error do_bltz(mips_cpu_h state, uint32_t instruction){

	int32_t off = instruction & 0xFFFF;
	off = (off << 2);

	uint32_t src = (instruction>> 21) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "bltz %u, %d.\n", src, off);
	}

	int32_t va = state->regs[src];

	mips_error e = mips_ExceptionBreak;

	if(va < 0){
		uint address = state->pcNext + off;
		e = mips_cpu_set_pcNext(state, state->pcNext, address);
	} else {
		e = mips_cpu_set_pc(state, state->pcNext);
	}

	return e;

}

mips_error do_bltzal(mips_cpu_h state, uint32_t instruction){

	int32_t off = instruction & 0xFFFF;
	off = (off << 2);

	uint32_t src = (instruction>> 21) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "bltzal %u, %d.\n", src, off);
	}

	int32_t va = state->regs[src];

	if(va < 0){
		uint address = state->pcNext + off;
		mips_error e1 = mips_cpu_set_register(state, 31, (state->pc + 8));
		mips_error e2 = mips_cpu_set_pcNext(state, state->pcNext, address);
		return check_errors(e1, e2);
	} else {
		mips_error e = mips_cpu_set_pc(state, state->pcNext);
		return e;
	}

}

mips_error do_bne(mips_cpu_h state, uint32_t instruction){

	int32_t off = instruction & 0xFFFF;
	off = (off << 2);

	uint32_t src1 = (instruction>> 21) & 0x1F;
	uint32_t src2 = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "bne %u, %u, %d.\n", src1, src2, off);
	}

	int32_t va = state->regs[src1];
	int32_t vb = state->regs[src2];

	mips_error e = mips_ExceptionBreak;

	if(va != vb){
		uint address = state->pcNext + off;
		e = mips_cpu_set_pcNext(state, state->pcNext, address);
	} else {
		e = mips_cpu_set_pc(state, state->pcNext);
	}

	return e;

}

mips_error do_div(mips_cpu_h state, uint32_t instruction){

	return mips_Success;
}

mips_error do_divu(mips_cpu_h state, uint32_t instruction){

	return mips_Success;
}

mips_error do_j(mips_cpu_h state, uint32_t instruction){

	uint32_t instr_index = instruction & 0x3FFFFFF;
	instr_index = (instr_index << 2);

	if(state->logLevel >= 1){
		fprintf(state->logDst, "j %u.\n", instr_index);
	}

	return mips_cpu_set_pcNext(state, state->pcNext, instr_index);

}

mips_error do_jal(mips_cpu_h state, uint32_t instruction){

	uint32_t instr_index = instruction & 0x3FFFFFF;
	instr_index = (instr_index << 2);

	if(state->logLevel >= 1){
		fprintf(state->logDst, "jal %u.\n", instr_index);
	}

	mips_error e1 = mips_cpu_set_register(state, 31, (state->pc + 8));
	mips_error e2 = mips_cpu_set_pcNext(state, state->pcNext, instr_index);
	return check_errors(e1, e2);

}

mips_error do_jalr(mips_cpu_h state, uint32_t instruction){

	uint32_t instr_reg = (instruction>> 21) & 0x1F;
	uint32_t dst  = (instruction>> 11) & 0x1F;

	uint32_t instr_index = state->regs[instr_reg];

	if(state->logLevel >= 1){
		fprintf(state->logDst, "jalr %u %u.\n", dst, instr_reg);
	}

	if(instr_index & 0b11) {
		return mips_ExceptionInvalidAddress;
	}

	mips_error e1 = mips_cpu_set_register(state, dst, (state->pc + 8));
	mips_error e2 = mips_cpu_set_pcNext(state, state->pcNext, instr_index);

	return check_errors(e1, e2);

}

mips_error do_jr(mips_cpu_h state, uint32_t instruction){

	uint32_t instr_reg = (instruction>> 21) & 0x1F;
	uint32_t instr_index = state->regs[instr_reg];

	if(state->logLevel >= 1){
		fprintf(state->logDst, "jr %u.\n", instr_reg);
	}

	if(instr_index & 0b11) {
		return mips_ExceptionInvalidAddress;
	}

	return mips_cpu_set_pcNext(state, state->pcNext, instr_index);

}

mips_error do_lb(mips_cpu_h state, uint32_t instruction){

	int16_t off = instruction & 0xFFFF;

	uint32_t base_reg = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "lb %u, %d(%u).\n", dst, off, base_reg);
	}

	uint32_t base = state->regs[base_reg];
	uint32_t location = base + off;

	uint8_t data;

	mips_error e1 = mips_mem_read(
		    state->mem,		//!< Handle to target memory
		    location,		//!< Byte address to start transaction at
		    1,				//!< Number of bytes to transfer
		    &data			//!< Receives the target bytes
		);

	int32_t data2 = data;

	mips_error e2 = mips_cpu_set_register(state, dst, data2);
	mips_error e3 = mips_cpu_set_pc(state, state->pcNext);

	mips_error etmp = check_errors(e1, e2);
	return check_errors(etmp, e3);

}

mips_error do_lbu(mips_cpu_h state, uint32_t instruction){

	int16_t off = instruction & 0xFFFF;

	uint32_t base_reg = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "lbu %u, %d(%u).\n", dst, off, base_reg);
	}

	uint32_t base = state->regs[base_reg];
	uint32_t location = base + off;

	uint8_t data;

	mips_error e1 = mips_mem_read(
		    state->mem,		//!< Handle to target memory
		    location,		//!< Byte address to start transaction at
		    1,				//!< Number of bytes to transfer
		    &data			//!< Receives the target bytes
		);

	uint32_t data2 = data;

	mips_error e2 = mips_cpu_set_register(state, dst, data2);
	mips_error e3 = mips_cpu_set_pc(state, state->pcNext);

	mips_error etmp = check_errors(e1, e2);
	return check_errors(etmp, e3);

}

mips_error do_lh(mips_cpu_h state, uint32_t instruction){

	int16_t off = instruction & 0xFFFF;

	uint32_t base_reg = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "lh %u, %d(%u).\n", dst, off, base_reg);
	}

	uint32_t base = state->regs[base_reg];
	uint32_t location = base + off;

	if(location & 0b1){
		return mips_ExceptionInvalidAddress;
	}

	uint8_t data[2] = {0};

	mips_error e1 = mips_mem_read(
		    state->mem,		//!< Handle to target memory
		    location,		//!< Byte address to start transaction at
		    2,				//!< Number of bytes to transfer
		    data			//!< Receives the target bytes
		);

	uint32_t tmp0 = data[0];
	uint32_t tmp1 = data[1];

	uint16_t datatmp =
			(tmp0 << 8)
			|
			(tmp1);

	int32_t data2 = datatmp;

	mips_error e2 = mips_cpu_set_register(state, dst, data2);
	mips_error e3 = mips_cpu_set_pc(state, state->pcNext);

	mips_error etmp = check_errors(e1, e2);
	return check_errors(etmp, e3);

}

mips_error do_lhu(mips_cpu_h state, uint32_t instruction){

	int16_t off = instruction & 0xFFFF;

	uint32_t base_reg = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "lhu %u, %d(%u).\n", dst, off, base_reg);
	}

	uint32_t base = state->regs[base_reg];
	uint32_t location = base + off;

	if(location & 0b1){
		return mips_ExceptionInvalidAddress;
	}

	uint8_t data[2] = {0};

	mips_error e1 = mips_mem_read(
		    state->mem,		//!< Handle to target memory
		    location,		//!< Byte address to start transaction at
		    2,				//!< Number of bytes to transfer
		    data			//!< Receives the target bytes
		);

	uint32_t tmp0 = data[0];
	uint32_t tmp1 = data[1];

	uint16_t datatmp =
			(tmp0 << 8)
			|
			(tmp1);

	uint32_t data2 = datatmp;

	mips_error e2 = mips_cpu_set_register(state, dst, data2);
	mips_error e3 = mips_cpu_set_pc(state, state->pcNext);

	mips_error etmp = check_errors(e1, e2);
	return check_errors(etmp, e3);

}

mips_error do_lui(mips_cpu_h state, uint32_t instruction){

	uint16_t imm = instruction & 0xFFFF;

	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "lui %u, %u.\n", dst, imm);
	}


	uint32_t res = (imm << 16);

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_lw(mips_cpu_h state, uint32_t instruction){

	int16_t off = instruction & 0xFFFF;

	uint32_t base_reg = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "lw %u, %d(%u).\n", dst, off, base_reg);
	}

	uint32_t base = state->regs[base_reg];
	uint32_t location = base + off;

	if(location & 0b11){
		return mips_ExceptionInvalidAddress;
	}

	uint8_t data[4] = {0};

	mips_error e1 = mips_mem_read(
		    state->mem,		//!< Handle to target memory
		    location,		//!< Byte address to start transaction at
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

	mips_error e2 = mips_cpu_set_register(state, dst, data2);
	mips_error e3 = mips_cpu_set_pc(state, state->pcNext);

	mips_error etmp = check_errors(e1, e2);
	return check_errors(etmp, e3);

}

mips_error do_mfhi(mips_cpu_h state, uint32_t instruction){

	uint32_t dst_reg = (instruction>> 11) & 0x1F;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst_reg, state->HI);

	return check_errors(e1, e2);

}

mips_error do_mflo(mips_cpu_h state, uint32_t instruction){

	uint32_t dst_reg = (instruction>> 11) & 0x1F;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst_reg, state->LO);

	return check_errors(e1, e2);

}

mips_error do_mthi(mips_cpu_h state, uint32_t instruction){

	uint32_t src = (instruction>> 21) & 0x1F;

	state->HI = state->regs[src];

	return mips_cpu_set_pc(state, state->pcNext);

}

mips_error do_mtlo(mips_cpu_h state, uint32_t instruction){

	uint32_t src = (instruction>> 21) & 0x1F;

	state->LO = state->regs[src];

	return mips_cpu_set_pc(state, state->pcNext);

}

mips_error do_mult(mips_cpu_h state, uint32_t instruction){

	uint32_t src1 = (instruction>> 21) & 0x1F;
    uint32_t src2 = (instruction>> 16) & 0x1F;

	int32_t va = state->regs[src1];
	int32_t vb = state->regs[src2];
	int64_t res;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "mult %u, %u.\n", src1, src2);
	}

	res = va * vb;

	int32_t LO = res & 0xFFFFFFFF;
	int32_t HI = (res >> 32) & 0xFFFFFFFF;
	state->LO = LO;
	state->HI = HI;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);

	return e1;

}

mips_error do_multu(mips_cpu_h state, uint32_t instruction){

	uint32_t src1 = (instruction>> 21) & 0x1F;
    uint32_t src2 = (instruction>> 16) & 0x1F;

	uint32_t va = state->regs[src1];
	uint32_t vb = state->regs[src2];
	uint64_t res;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "multu %u, %u.\n", src1, src2);
	}

	res = va * vb;

	int32_t LO = res & 0xFFFFFFFF;
	int32_t HI = (res >> 32) & 0xFFFFFFFF;
	state->LO = LO;
	state->HI = HI;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);

	return e1;

}

mips_error do_or(mips_cpu_h state, uint32_t instruction){

	uint32_t src1     = (instruction>> 21) & 0x1F;
	uint32_t src2     = (instruction>> 16) & 0x1F;
	uint32_t dst      = (instruction>> 11) & 0x1F;

	uint32_t va=state->regs[src1];
	uint32_t vb=state->regs[src2];
	uint32_t res;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "or %u, %u, %u.\n", dst, src1, src2);
	}

	res = va or vb;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_ori(mips_cpu_h state, uint32_t instruction){

	uint16_t imm = instruction & 0xFFFF;

	uint32_t src = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "ori %u, %u, %d.\n", dst, src, imm);
	}

	uint32_t va = state->regs[src];
	uint32_t res = va or imm;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_sb(mips_cpu_h state, uint32_t instruction){

	int16_t off = instruction & 0xFFFF;

	uint32_t base_reg = (instruction>> 21) & 0x1F;
	uint32_t src = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "sb %u, %d(%u).\n", src, off, base_reg);
	}

	uint32_t base = state->regs[base_reg];
	uint32_t location = base + off;

	uint32_t data = state->regs[src];

	uint8_t data_in = data & 0xFF;

	mips_error e1 = mips_mem_write(
			state->mem,			//! Handle to target memory
			location,			//! Byte address to start transaction at
			1,					//! Number of bytes to transfer
			&data_in			//! Receives the target bytes
		);

	mips_error e2 = mips_cpu_set_pc(state, state->pcNext);

	return check_errors(e1, e2);

}

mips_error do_sh(mips_cpu_h state, uint32_t instruction){

	int16_t off = instruction & 0xFFFF;

	uint32_t base_reg = (instruction>> 21) & 0x1F;
	uint32_t src = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "sh %u, %d(%u).\n", src, off, base_reg);
	}

	uint32_t base = state->regs[base_reg];
	uint32_t location = base + off;

	if(location & 0b1){
		return mips_ExceptionInvalidAddress;
	}

	uint16_t data = state->regs[src] & 0xFFFF;

	uint8_t data_in[2];
	data_in[0] = ((data >> 8) & 0xFF);
	data_in[1] = ((data >> 0) & 0xFF);

	mips_error e1 = mips_mem_write(
			state->mem,			//! Handle to target memory
			location,			//! Byte address to start transaction at
			2,					//! Number of bytes to transfer
			data_in				//! Receives the target bytes
		);

	mips_error e2 = mips_cpu_set_pc(state, state->pcNext);

	return check_errors(e1, e2);

}

mips_error do_sll(mips_cpu_h state, uint32_t instruction){

    uint32_t src = (instruction>> 16) & 0x1F;
    uint32_t dst = (instruction>> 11) & 0x1F;
	uint32_t sa  = (instruction>>  6) & 0b11111;

	uint32_t va = state->regs[src];

	if((state->logLevel >= 1) && (instruction != 0)){
		fprintf(state->logDst, "sll %u, %u, %u.\n", dst, src, sa);
	}

	//uint32_t res = va * (pow(2, sa));  				// would this work the same?
	uint32_t res = (va << sa);

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_sllv(mips_cpu_h state, uint32_t instruction){

	uint32_t src    = (instruction>> 16) & 0x1F;
	uint32_t dst    = (instruction>> 11) & 0x1F;
	uint32_t sareg  = (instruction>> 21) & 0x1F;

	uint32_t va = state->regs[src];
	uint32_t sa = state->regs[sareg];
	sa = sa & 0b11111;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "sllv %u, %u, %u.\n", dst, src, sareg);
	}

	//uint32_t res = va * (pow(2, sa));
	uint32_t res = (va << sa);

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_slt(mips_cpu_h state, uint32_t instruction){

	uint32_t src1 = (instruction>> 21) & 0x1F;
    uint32_t src2 = (instruction>> 16) & 0x1F;
    uint32_t dst  = (instruction>> 11) & 0x1F;

	int32_t va   = state->regs[src1];
	int32_t vb   = state->regs[src2];
	uint32_t res = 0;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "slt %u, %u, %u.\n", dst, src1, src2);
	}

	if(va < vb){
		res = 1;
	}

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_slti(mips_cpu_h state, uint32_t instruction){

	int16_t imm = instruction & 0xFFFF;

	uint32_t src = (instruction >> 21) & 0x1F;
	uint32_t dst = (instruction >> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "slti %u, %u, %d.\n", dst, src, imm);
	}

	int32_t va = state->regs[src];
	uint32_t res = 0;

	if(va < imm){
		res = 1;
	}

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_sltiu(mips_cpu_h state, uint32_t instruction){

	uint16_t imm = instruction & 0xFFFF;

	uint32_t src = (instruction>> 21) & 0x1F;
	uint32_t dst = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "sltiu %u, %u, %u.\n", dst, src, imm);
	}

	uint32_t va = state->regs[src];
	uint32_t res = 0;

	if(va < imm){
		res = 1;
	}

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_sltu(mips_cpu_h state, uint32_t instruction){

	uint32_t src1 = (instruction>> 21) & 0x1F;
    uint32_t src2 = (instruction>> 16) & 0x1F;
    uint32_t dst  = (instruction>> 11) & 0x1F;

	uint32_t va  = state->regs[src1];
	uint32_t vb  = state->regs[src2];
	uint32_t res = 0;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "sltu %u, %u, %u.\n", dst, src1, src2);
	}

	if(va < vb){
		res = 1;
	}

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_sra(mips_cpu_h state, uint32_t instruction){

    uint32_t src = (instruction >> 16) & 0x1F;
    uint32_t dst = (instruction >> 11) & 0x1F;
	uint32_t  sa = (instruction >>  6) & 0x1F;

	int32_t va = state->regs[src];

	if(state->logLevel >= 1){
		fprintf(state->logDst, "sra %u, %u, %u.\n", dst, src, sa);
	}

	int32_t res = (va >> sa);

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_srav(mips_cpu_h state, uint32_t instruction){

	uint32_t src    = (instruction>> 16) & 0x1F;
	uint32_t dst    = (instruction>> 11) & 0x1F;
	uint32_t sareg  = (instruction>> 21) & 0x1F;

	int32_t va  = state->regs[src];
	uint32_t sa = state->regs[sareg];
	sa = sa & 0b11111;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "srav %u, %u, %u.\n", dst, src, sareg);
	}

	int32_t res = (va >> sa);

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_srl(mips_cpu_h state, uint32_t instruction){

    uint32_t src = (instruction >> 16) & 0x1F;
    uint32_t dst = (instruction >> 11) & 0x1F;
	uint32_t sa  = (instruction >>  6) & 0x1F;

	uint32_t va = state->regs[src];

	if(state->logLevel >= 1){
		fprintf(state->logDst, "srl %u, %u, %u.\n", dst, src, sa);
	}

	uint32_t res = (va >> sa);

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_srlv(mips_cpu_h state, uint32_t instruction){

	uint32_t src    = (instruction>> 16) & 0x1F;
	uint32_t dst    = (instruction>> 11) & 0x1F;
	uint32_t sareg  = (instruction>> 21) & 0x1F;

	uint32_t va = state->regs[src];
	uint32_t sa = state->regs[sareg];
	sa = sa & 0b11111;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "srlv %u, %u, %u.\n", dst, src, sareg);
	}

	uint32_t res = (va >> sa);

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_sub(mips_cpu_h state, uint32_t instruction){

	uint32_t src1 = (instruction>> 21) & 0x1F;
    uint32_t src2 = (instruction>> 16) & 0x1F;
    uint32_t dst  = (instruction>> 11) & 0x1F;

	int32_t va = state->regs[src1];
	int32_t vb = state->regs[src2];
	int32_t res;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "sub %u, %u, %u.\n", dst, src1, src2);
	}

	res = va - vb;

	if((va & 0x80000000) != (vb & 0x80000000) && ((vb & 0x80000000) == (res & 0x80000000))){
		fprintf(state->logDst, "OVERFLOW\n");
		return mips_ExceptionArithmeticOverflow;
	}

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}

mips_error do_subu(mips_cpu_h state, uint32_t instruction){

	uint32_t src1 = (instruction>> 21) & 0x1F;
    uint32_t src2 = (instruction>> 16) & 0x1F;
    uint32_t dst  = (instruction>> 11) & 0x1F;

	int32_t va = state->regs[src1];
	int32_t vb = state->regs[src2];
	int32_t res;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "subu %u, %u, %u.\n", dst, src1, src2);
	}

	res = va - vb;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);
}

mips_error do_sw(mips_cpu_h state, uint32_t instruction){

	int16_t off = instruction & 0xFFFF;

	uint32_t base_reg = (instruction>> 21) & 0x1F;
	uint32_t src = (instruction>> 16) & 0x1F;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "sw %u, %d(%u).\n", src, off, base_reg);
	}

	uint32_t base = state->regs[base_reg];
	uint32_t location = base + off;

	if(location & 0b11){
		return mips_ExceptionInvalidAddress;
	}

	uint32_t data = state->regs[src];

	uint8_t data_in[4];
	data_in[0] = ((data >> 24) & 0xFF);
	data_in[1] = ((data >> 16) & 0xFF);
	data_in[2] = ((data >>  8) & 0xFF);
	data_in[3] = ((data >>  0) & 0xFF);

	mips_error e1 = mips_mem_write(
			state->mem,			//! Handle to target memory
			location,			//! Byte address to start transaction at
			4,					//! Number of bytes to transfer
			data_in				//! Receives the target bytes
		);

	mips_error e2 = mips_cpu_set_pc(state, state->pcNext);

	return check_errors(e1, e2);

}

mips_error do_xor(mips_cpu_h state, uint32_t instruction){

	uint32_t src1     = (instruction>> 21) & 0x1F;
	uint32_t src2     = (instruction>> 16) & 0x1F;
	uint32_t dst      = (instruction>> 11) & 0x1F;

	uint32_t va=state->regs[src1];
	uint32_t vb=state->regs[src2];
	uint32_t res;

	if(state->logLevel >= 1){
		fprintf(state->logDst, "xor %u, %u, %u.\n", dst, src1, src2);
	}

	res = va xor vb;

	mips_error e1 = mips_cpu_set_pc(state, state->pcNext);
	mips_error e2 = mips_cpu_set_register(state, dst, res);

	return check_errors(e1, e2);

}



mips_error do_lwl(mips_cpu_h state, uint32_t instruction){

	return mips_Success;
}

mips_error do_lwr(mips_cpu_h state, uint32_t instruction){

	return mips_Success;
}

