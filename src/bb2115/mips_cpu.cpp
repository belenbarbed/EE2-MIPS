#include "mips.h"
#include "mips_cpu_structdef.h"
#include "mips_cpu_instrTable.h"


mips_error mips_cpu_set_pc(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	uint32_t pc			//!< Address of the next instruction to execute.
){

	if (pc > 0x20000000){
		return mips_ExceptionInvalidAddress;
	}

	state->pc = pc;
	state->pcNext = state->pc + 4;
	return mips_Success;
}

mips_error mips_cpu_set_pcNext(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	uint32_t pc,		//!< Address of the next instruction to execute.
	uint32_t pcNext
){

	if ((pcNext > 0x20000000) || (pc > 0x20000000)){
		return mips_ExceptionInvalidAddress;
	}

	state->pc = pc;
	state->pcNext = pcNext;
	return mips_Success;
}

mips_error mips_cpu_get_pc(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	uint32_t *pc		//!< Where to write the byte address too
)
{
    *pc = state->pc;
    return mips_Success;
}

mips_error mips_cpu_get_register(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	unsigned index,		//!< Index from 0 to 31
	uint32_t *value		//!< Where to write the value to
)
{

    if (index < 32) {
    	*value = state->regs[index];
    	return mips_Success;
    } else if (index == 0){
    	*value = 0;
    	return mips_Success;
    } else{
    	return mips_ExceptionInvalidAddress;
    }

}

mips_error mips_cpu_set_register(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	unsigned index,		//!< Index from 0 to 31
	uint32_t value		//!< New value to write into register file
)
{

	if(index == 0){
		return mips_Success;
	}

	if (index < 32) {
		state->regs[index] = value;
		return mips_Success;
	} else {
		return mips_ExceptionInvalidAddress;
	}

}

mips_cpu_h mips_cpu_create(mips_mem_h mem)
{
    mips_cpu_impl *cpu=new mips_cpu_impl;

    cpu->pc     = 0;
    cpu->pcNext = cpu->pc + 4;
    for(int i=0;i<32;i++){
        cpu->regs[i]=0;
    }
    cpu->HI = 0;
    cpu->LO = 0;
    cpu->mem=mem;

    return cpu;
}

mips_error mips_cpu_reset(mips_cpu_h state){

	state->pc=0;
	state->pcNext = state->pc + 4;
	for(int i=0;i<32;i++){
		state->regs[i]=0;
	}
    state->HI = 0;
    state->LO = 0;

	return mips_Success;
}

uint32_t to_big(const uint8_t *pData)
{
	/*! \param pData Array of 4 bytes
	    \retrieval The big-endian equivalent
	*/
    return
        (((uint32_t)pData[0])<<24)
        |
        (((uint32_t)pData[1])<<16)
        |
        (((uint32_t)pData[2])<<8)
        |
        (((uint32_t)pData[3])<<0);
}

mips_error mips_cpu_set_debug_level(mips_cpu_h state, unsigned level, FILE *dest)
{
    state->logLevel = level;
    state->logDst = dest;
    return mips_Success;
}

void mips_cpu_free(mips_cpu_h state){
	// TODO: THIS SHIT

}

mips_error mips_cpu_step(
	mips_cpu_h state	//! Valid (non-empty) handle to a CPU
)
{

	uint8_t buffer[4];

    mips_error err=mips_mem_read(
        state->mem,		//!< Handle to target memory
        state->pc,		//!< Byte address to start transaction at
        4,				//!< Number of bytes to transfer
        buffer			//!< Receives the target bytes
    );

    if(err!=0){
        return err;
    }

    uint32_t instruction = to_big(buffer);
    uint32_t opcode      = (instruction>> 26) & 0x3F;
//    fprintf(state->logDst, "the opcode is %u\n", opcode);
    uint32_t fncode      = (instruction>>  0) & 0x3F;
//    fprintf(state->logDst, "the fncode is %u\n", fncode);

    return decoding(state, instruction, opcode, fncode);

}
