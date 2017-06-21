#include "functions.h"
void func0(struct regs* myreg){
	/* do nothing */
}
/* 01: comm_count --> buffer_reg */
void func1(struct regs* myreg){
	myreg->buffer_reg = (myreg->comm_count & 2047);
	myreg->mic_com_reg = 0x0300;
	//printf("MK_reg: %04x\n", myreg->mic_com_reg);
}
/* 02: buffer_reg --> address_reg */	
void func2(struct regs *myreg){
	myreg->address_reg = (myreg->buffer_reg & 2047);
	myreg->mic_com_reg = 0x4001;
}
/* 03: OP(address_reg) --> data_reg*/
void func3(struct regs *myreg){
	myreg->data_reg = myreg->mem[myreg->address_reg];
	myreg->buffer_reg = myreg->comm_count + 1;
	myreg->mic_com_reg = 0x0311;
}
/* 04: buffer_reg --> comm_count */
void func4(struct regs *myreg){
	myreg->comm_count = (myreg->buffer_reg & 2047);
	myreg->mic_com_reg = 0x4004;
}
/* 05: data_reg --> buffer_reg */
void func5(struct regs *myreg){
	myreg->buffer_reg = myreg->data_reg;
	myreg->mic_com_reg = 0x0100;
}
/* 06: buffer_reg --> comm_reg */
void func6(struct regs* myreg){
    myreg->comm_reg = myreg->buffer_reg;
    myreg->mic_com_reg = 0x4003;
}
/* 07: if (BIT(15, comm_reg) == 0) --> goto 0C (12 in dec) */
void func7(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xaf0c;
    if ((myreg->comm_reg & 0x8000) != 0x8000)
        myreg->count_mic_com = 12;
}
/* 08: if(BIT(14, comm_reg) == 0) --> goto 0C (12 in dec) */
void func8(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xae0c;
    if ((16384 & myreg->comm_reg) != 16384)
        myreg->count_mic_com = 12;
}
/* 09: if(BIT(13, comm_reg) == 0) --> goto 0C (12 in dec) */
void func9(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xad0c;
    if((8192 & myreg->comm_reg) != 8192)
        myreg->count_mic_com = 12;
}
/* 0A = 10: if(BIT(12, comm_reg) == 1) --> goto 5E (94 in dec) */
void func10(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xec5e;
    if ((4096 & myreg->comm_reg) == 4096)
        myreg->count_mic_com = 94;
}
/* 0B = 11: goto 8E (142 in dec) */
void func11(struct regs* myreg){
    myreg->mic_com_reg = 0x838e;
    myreg->count_mic_com = 142;
    myreg->buffer_reg = myreg->status_register;
}
/* 0C = 12: if(BIT(11, myreg->comm_reg) == 0) --> goto 1D (29 in dec) */
void func12(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xab1d;
    if ((myreg->comm_reg & 0x0800) == 0){
        myreg->count_mic_com = 29;
    }
}
/* Cycle pf getting operator's address */
/* 0D = 13: myreg->data_reg --> myreg->buffer_reg */
void func13(struct regs* myreg){
    myreg->buffer_reg = myreg->data_reg;
    myreg->mic_com_reg = 0x0100;
}
/* 0E = 14: myreg->buffer_reg --> myreg->address_reg */
void func14(struct regs* myreg){
    myreg->address_reg = (myreg->buffer_reg & 2047);
    myreg->mic_com_reg = 0x4001;
}
/* 0F = 15: myreg->memory(myreg->address_reg)--> myreg->data_reg */
void func15(struct regs* myreg){
    myreg->buffer_reg = 0;
    myreg->data_reg = myreg->mem[myreg->address_reg];
    myreg->mic_com_reg = 0x0001;
}
/* 010 = 16: if(BIT(3, myreg->comm_reg) == 0) --> goto 1D (29 in dec) */
void func16(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xa31d;
    if ((8 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 29;
}
/* 011 = 17: if(BIT(4, myreg->comm_reg) == 1) --> goto 1D (29 in dec) */
void func17(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xe41d;
    if ((16 & myreg->comm_reg) != 0)
        myreg->count_mic_com = 29;
}
/* 012 = 18: if(BIT(5, myreg->comm_reg) == 1) --> goto 1D (29 in dec) */
void func18(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xe51d;
    if ((32 & myreg->comm_reg) != 0)
        myreg->count_mic_com = 29;
}
/* 013 = 19: if(BIT(6, myreg->comm_reg) == 1) --> goto 1D (29 in dec) */
void func19(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xe61d;
    if ((64 & myreg->comm_reg) != 0)
        myreg->count_mic_com = 29;
}
/* 014 = 20: if(BIT(7, myreg->comm_reg) == 1) --> goto 1D (29 in dec) */
void func20(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xe71d;
    if ((128 & myreg->comm_reg) == 1)
        myreg->count_mic_com = 29;
}
/* 015 = 21: if(BIT(8, myreg->comm_reg) == 1) --> goto 1D (29 in dec) */
void func21(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xe81d;
    if ((256 & myreg->comm_reg) == 1)
        myreg->count_mic_com = 29;
}
/* 016 = 22: if(BIT(9, myreg->comm_reg) == 1) --> goto 1D (29 in dec) */
void func22(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xe91d;
    if ((512 & myreg->comm_reg) == 1)
        myreg->count_mic_com = 29;
}
/* 017 = 23: if(BIT(10, myreg->comm_reg) == 1) --> goto 1D (29 in dec) */
void func23(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xea1d;
    if ((1024 & myreg->comm_reg) == 1)
        myreg->count_mic_com = 29;
}
/* 018 = 24: myreg->data_reg + 1 --> myreg->buffer_reg */
void func24(struct regs* myreg){
    myreg->mic_com_reg = 0x0110;
    myreg->buffer_reg = myreg->data_reg + 1;
}
/* 019 = 25: myreg->buffer_reg --> myreg->data_reg */
void func25(struct regs* myreg){
    myreg->mic_com_reg = 0x4002;
    myreg->data_reg = myreg->buffer_reg;
}
/* 01A = 26: myreg->data_reg --> myreg->mem(myreg->address_reg) */
void func26(struct regs* myreg){
    myreg->mem[myreg->address_reg] = myreg->data_reg;
    myreg->mic_com_reg =   0x0002;
}
/* 01b = 27: myreg->data_reg - 1 --> myreg->buffer_reg */
void func27(struct regs* myreg){
    myreg->buffer_reg = myreg->data_reg - 1;
    myreg->mic_com_reg = 0x0140;
}
/* 01c = 28: myreg->buffer_reg --> myreg->data_reg */
void func28(struct regs* myreg){
    myreg->data_reg = myreg->buffer_reg;
    myreg->mic_com_reg = 0x4002;
}
/* RUNNING ADDRESS COMMANDS */
/* CYCLE OF DECODING ADDRESS COMMANDS */
/* 01d = 29: (BIT(15, myreg->comm_reg) == 1) --> goto 2D (45 in dec) */
void func29(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0XEF2D;
    if ((myreg->comm_reg & 32768) != 0)
        myreg->count_mic_com = 45;
}
/* 01e = 30: myreg->data_reg --> myreg->buffer_reg */
void func30(struct regs* myreg){
    myreg->mic_com_reg = 0x0100;
    myreg->buffer_reg = myreg->data_reg;
}
/* 01f = 31: myreg->buffer_reg --> myreg->address_reg*/
void func31(struct regs* myreg){
    myreg->mic_com_reg = 0x4001;
    myreg->address_reg = (myreg->buffer_reg & 2047);
}
/* 020 = 32: if(BIT(14, myreg->comm_reg) == 1) --> goto 27 (39 in dec) */
void func32 (struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xee27;
    if ((myreg->comm_reg & 0x4000) != 0){
        myreg->count_mic_com = 0x0027;
    }
}
/* 021 = 33: if(BIT(13, myreg->comm_reg) == 0) --> goto 0x24 (161 in dec) */
void func33(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xad24;
    if ((myreg->comm_reg & 0x2000) == 0)
        myreg->count_mic_com = 0x24;
}
/* 022 = 34: if(BIT(12, myreg->comm_reg) == 0) --> goto 57 (87 in dec) */
void func34(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xac57;
    if ((4096 & myreg->comm_reg) != 4096)
        myreg->count_mic_com = 57;
}
/* 023 = 35: goto 38 (56 in dec)*/
void func35(struct regs* myreg){
    myreg->mic_com_reg = 0x8338;
    myreg->count_mic_com = 0x38;
    myreg->buffer_reg = myreg->status_register;
}
/* 024 = 36: myreg->mem(myreg->address_reg) --> myreg->data_reg */
void func36(struct regs* myreg){
    myreg->buffer_reg = 0;
    myreg->mic_com_reg = 0x0001;
    myreg->data_reg = myreg->mem[myreg->address_reg];
}
/* 025 = 37: BIT(12, myreg->comm_reg) == 0) --> goto 50 (80 in dec) */
void func37(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xac50;
    if ((4096 & myreg->comm_reg) != 4096)
        myreg->count_mic_com = 80;
}
/* 026 = 38: goto 35 (53 in dec)*/
void func38(struct regs* myreg){
    myreg->mic_com_reg = 0x8335;
    myreg->count_mic_com = 0x35;
    myreg->buffer_reg = myreg->mic_com_reg;
}
/* 027 = 39: myreg->mem(myreg->address_reg --> myreg->data_reg) */
void func39(struct regs* myreg){
    myreg->buffer_reg = 0;
    myreg->mic_com_reg = 0x0001;
    myreg->data_reg = myreg->mem[myreg->address_reg];
}
/* 028 = 40: if(BIT(13, myreg->comm_reg) == 0) --> goto 2B (43 in dec) */
void func40(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xad2b;
    if((0x2000 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 43;
}
/* 029 = 41: if(BIT(12, myreg->comm_reg) == 0) --> goto 43 (67 in dec) */
void func41(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xac43;
    if((4096 & myreg->comm_reg) != 4096)
        myreg->count_mic_com = 67;
}
/* 02A = 42: goto B0 (176 in dec) */
void func42(struct regs* myreg){
    myreg->mic_com_reg = 0x83b0;
    myreg->count_mic_com = 176;
    myreg->buffer_reg = myreg->status_register;
}
/* 02B = 43: if(BIT(12, myreg->comm_reg) == 0) --> goto 3c (60 in dec) */
void func43(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xac3c;
    if((4096 & myreg->comm_reg) != 4096)
        myreg->count_mic_com = 60;
}
/* 02C = 44: goto 3f (63 in dec) */
void func44(struct regs* myreg){
    myreg->mic_com_reg = 0x833f;
    myreg->count_mic_com = 63;
    myreg->buffer_reg = myreg->status_register;
}
/* 02D = 45: if(BIT(14, myreg->comm_reg) == 0) --> goto 30 (48 in dec) */
void func45(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xae30;
    if ((16384 & myreg->comm_reg) != 16384)
        myreg->count_mic_com = 48;
}
/* 02E = 46: if(BIT(12, myreg->comm_reg) == 0) --> goto 47 (71 in dec) */
void func46(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xac47;
    if ((4096 & myreg->comm_reg) != 4096)
        myreg->count_mic_com = 71;
}
/* 02F = 47: goto D0 (208 in dec)*/
void func47(struct regs* myreg){
    myreg->mic_com_reg = 0xac47;
    myreg->count_mic_com = 208;
    myreg->buffer_reg = myreg->status_register;
}
/* 030 = 48: if(BIT(13, myreg->comm_reg) == 0) --> goto 33 (51 in dec) */
void func48(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xad33;
    if ((8192 & myreg->comm_reg) != 8192)
        myreg->count_mic_com = 51;
}
/* 031 = 49: if(BIT(12, myreg->comm_reg) == 0) --> goto 4C (76 in dec) */
void func49(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xac4c;
    if ((4096 & myreg->comm_reg) != 4096)
        myreg->count_mic_com = 76;
}
/* 032 = 50: goto 4e (78 in dec) */
void func50(struct regs* myreg){
    myreg->mic_com_reg = 0x834e;
    myreg->count_mic_com = 78;
    myreg->buffer_reg = myreg->status_register;
}
/* 033 = 51: if(BIT(12, myreg->comm_reg) == 0) --> goto 46 (70 in dec) */
void func51(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xac46;
    if ((4096 & myreg->comm_reg) != 4096)
        myreg->count_mic_com = 70;
}
/* 034 = 52: goto 4a (74 in dec) */
void func52(struct regs* myreg){
    myreg->mic_com_reg = 0x834a;
    myreg->count_mic_com = 74;
    myreg->buffer_reg = myreg->status_register;
}
/* ADDRESS COMMANDS */
/* AND*/
/* 035 = 53: A & myreg->data_reg --> buff_reg */
void func53(struct regs* myreg){
    myreg->buffer_reg = (myreg->accum & myreg->data_reg);
    myreg->mic_com_reg = 0x1120;
}
/* 036 = 54: buff_reg --> myreg->accum, c, z */
void func54(struct regs* myreg){
    myreg->mic_com_reg = 0x4035;
    if ((myreg->buffer_reg & 131072) == 131072){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
}
/* 037 = 55: goto 090 */
void func55(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* MOV */
/* 038 = 56: myreg->accum --> buff_reg */
void func56(struct regs* myreg){
    myreg->buffer_reg = myreg->accum;
    myreg->mic_com_reg = 0x100;
}
/* 39 = 57: buff_reg --> myreg->data_reg */
void func57(struct regs* myreg){
    myreg->data_reg = (myreg->buffer_reg & 0xffff);
    myreg->mic_com_reg = 0x4002;
}
/* 03a = 58: myreg->data_reg --> myreg->mem[myreg->address_reg] */
void func58(struct regs* myreg){
    myreg->mem[myreg->address_reg] = myreg->data_reg;
    myreg->mic_com_reg = 0x0002;
}
/* 03b = 59: goto 90 (144 in dec) */
void func59(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* ADD */
/* 03c = 60: myreg->accum + myreg->data_reg --> myreg->buffer_reg */
void func60(struct regs* myreg){
    myreg->buffer_reg = myreg->accum + myreg->data_reg;
    myreg->mic_com_reg = 0x1100;
}
/* 03d = 61: myreg->buffer_reg --> A, C, N, Z */
void func61(struct regs* myreg){
    myreg->mic_com_reg = 0x4035;
    if ((myreg->buffer_reg & 0x10000) != 0){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
    if(myreg->accum == 0){
        myreg->status_register |= 2;
        myreg->n_bit = 1;
    }
    else{
        myreg->status_register &= 509;
        myreg->n_bit = 0;
    }
}
/* 03e = 62: goto 90 (144 in dec) */
void func62(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* ADC */
/* 03f = 63: if BIT(0, stat_reg) == 0) --> goto 3C (60 in dec) */
void func63(struct regs* myreg){
    myreg->buffer_reg = myreg->status_register;
    myreg->mic_com_reg = 0x803c;
    if ((myreg->status_register & 1) == 0)
        myreg->count_mic_com = 60;
}
/* 40 = 64: myreg->accum + myreg->data_reg + 1 --> Buff_reg */
void func64(struct regs* myreg){
    myreg->mic_com_reg = 0x1110;
    myreg->buffer_reg = myreg->accum + myreg->data_reg + 1;
}
/* 41 = 65: myreg->buffer_reg --> a, c, n, z */
void func65(struct regs* myreg){
    myreg->mic_com_reg = 0x4075;
    if ((myreg->buffer_reg & 131072) == 131072){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
    if(myreg->accum == 0){
        myreg->status_register |= 2;
        myreg->n_bit = 1;
    }
    else{
        myreg->status_register &= 509;
        myreg->n_bit = 0;
    }
}
/* 42 = 66: goto 90 (144 in dec) */
void func66(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* SUB */
/* 43 = 67: myreg->accum + (~myreg->data_reg) + 1 --> buff_reg */
void func67(struct regs* myreg){
    myreg->buffer_reg = 0;
    myreg->mic_com_reg = 0x1190;
    myreg->buffer_reg = (myreg->accum - myreg->data_reg);
}
/* 44 = 68: myreg->buffer_reg --> a, c, n, z */
void func68(struct regs* myreg){
    myreg->mic_com_reg = 0x4075;
    if ((myreg->buffer_reg & 0x10000) != 0){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
    if(myreg->accum == 0){
        myreg->status_register |= 2;
        myreg->n_bit = 1;
    }
    else{
        myreg->status_register &= 509;
        myreg->n_bit = 0;
    }
}
/* 45 = 69: goto 90 (144) */
void func69(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* BSC */
/* 46 = 70: if BIT(0, stat_reg) == 0 --> goto 90 (144 in dec) */
void func70(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0x8090;
    if ((myreg->status_register & 1) == 0)
        myreg->count_mic_com = 144;
}
/* BR */
/* 47 = 71: myreg->data_reg --> buff_reg */
void func71(struct regs* myreg){
    myreg->mic_com_reg = 0x0100;
    myreg->buffer_reg = myreg->data_reg;
}
/* 48 = 72: buff_reg --> command_count*/
void func72(struct regs* myreg){
    myreg->mic_com_reg = 0x4004;
    myreg->comm_count = (myreg->buffer_reg & 2047);
}
/* 49 = 73: goto 90 (144 in dec) */
void func73(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* BPL */
/* 4a = 74: if BIT(2, stat_reg) == 1 --> goto 90 */
void func74(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xc290;
    if ((myreg->status_register & 4) != 0)
        myreg->count_mic_com = 144;
}
/* 4b = 75: goto 47 */
void func75(struct regs* myreg) {
    myreg->mic_com_reg = 0x8347;
    myreg->count_mic_com = 71;
    myreg->buffer_reg = myreg->status_register;
}
/* BMI */
/* 4c = 76: if BIT(2, stat_reg) == 0 --> goto 90 */
void func76(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0x8290;
    if ((myreg->status_register & 4) != 1)
        myreg->count_mic_com = 144;
}
/* 4d = 77: goto 47 */
void func77(struct regs* myreg){
    myreg->mic_com_reg = 0x8347;
    myreg->count_mic_com = 71;
    myreg->buffer_reg = myreg->status_register;
}
/* BEQ */
/* 4e = 78: if BIT(1, stat_reg) == 0 --> goto 90 */
void func78(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0x8190;
    if ((myreg->status_register & 2) == 0)
        myreg->count_mic_com = 144;
}
/* 4f = 79: goto 47 */
void func79(struct regs* myreg){
    myreg->mic_com_reg = 0x8347;
    myreg->count_mic_com = 71;
    myreg->buffer_reg = myreg->status_register;
}
/* ISZ */
/* 50 = 80: myreg->data_reg + 1 --> buff_reg */
void func80(struct regs* myreg){
    myreg->buffer_reg = myreg->data_reg + 1;
    myreg->mic_com_reg = 0x0110;
}
/* 51 = 81: buff_reg --> myreg->data_reg */
void func81(struct regs* myreg){
    myreg->data_reg = (myreg->buffer_reg & 65535);
    myreg->mic_com_reg = 0x4002;
}
/* 52 = 82: myreg->data_reg --> myreg->mem[myreg->address_reg] */
void func82(struct regs* myreg){
    myreg->mem[myreg->address_reg] = myreg->data_reg;
    myreg->mic_com_reg = 0x0002;
}
/* 53 = 83: if BIT(15, myreg->data_reg) == 1 --> goto 90 */
void func83(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xdf90;
    if ((myreg->data_reg & 32768) != 0)
        myreg->count_mic_com = 144;
}
/* SKP */
/* 54 = 84: myreg->comm_count + 1 --> myreg->buffer_reg */
void func84(struct regs* myreg){
    myreg->mic_com_reg = 0x0310;
    myreg->buffer_reg = myreg->comm_count + 1;
}
/* 55 = 85: myreg->buffer_reg --> myreg->comm_count */
void func85(struct regs* myreg){
    myreg->mic_com_reg = 0x4004;
    myreg->comm_count = (myreg->buffer_reg & 2047);
}
/* 56 = 86: goto 90 */
void func86(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
}
/* JSR */
/* 57 = 87: myreg->data_reg + 1 --> myreg->buffer_reg */
void func87(struct regs* myreg){
    myreg->mic_com_reg = 0x0110;
    myreg->buffer_reg = myreg->data_reg + 1;
}
/* 58 = 88: myreg->buffer_reg --> myreg->comm_reg */
void func88(struct regs* myreg){
    myreg->mic_com_reg = 0x4003;
    myreg->comm_reg = (myreg->buffer_reg & 0xffff);
}
/* 59 = 89: myreg->comm_count --> buff_reg */
void func89(struct regs* myreg){
    myreg->mic_com_reg = 0x0300;
    myreg->buffer_reg = myreg->comm_count;
}
/* 5a = 90: buff_reg --> myreg->data_reg */
void func90(struct regs* myreg){
    myreg->mic_com_reg = 0x4002;
    myreg->data_reg = (myreg->buffer_reg & 65535);
}
/* 5b = 91: myreg->data_reg --> myreg->mem[add_reg], myreg->comm_reg --> buff_reg */
void func91(struct regs* myreg){
    myreg->mic_com_reg = 0x0202;
    myreg->mem[myreg->address_reg] = myreg->data_reg;
    myreg->buffer_reg = myreg->comm_reg;
}
/* 5c = 92: buff_reg --> myreg->comm_count */
void func92(struct regs* myreg){
    myreg->mic_com_reg = 0x4004;
    myreg->comm_count = (myreg->buffer_reg & 65535);
}
/* 5d = 93: goto 90 */
void func93(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* CYCLE OF NON-ADDRESS COMMANDS */
/* Decoding cmds */
/* 5e = 94: if(BIT(11, myreg->comm_reg) == 0) --> goto 61 (97 in dec) */
void func94(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xab61;
    if ((2048 & myreg->comm_reg) != 2048)
        myreg->count_mic_com = 97;
}
/* 5f = 95: if (BIT(10, myreg->comm_reg) == 0) --> goto 6C (108 in dec) */
void func95(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xaa6c;
    if ((1024 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 108;
}
/* 60 = 96: goto E0 */
void func96(struct regs* myreg){
    myreg->mic_com_reg = 0x83e0;
    myreg->count_mic_com = 224;
    myreg->buffer_reg = myreg->status_register;
}
/* 61 = 97: if (BIT(10, myreg->comm_reg) == 0) --> goto 67 (103 in dec) */
void func97(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xaa67;
    if ((1024 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 103;
}
/* 62 = 98: if (BIT(9, myreg->comm_reg) == 0) --> goto 65 (101 in dec) */
void func98(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xa965;
    if ((512 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 101;
}
/* 63 = 99: if (BIT(8, myreg->comm_reg) == 0) --> goto 82 (101 in dec) */
void func99(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xa882;
    if ((256 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 130;
}
/* 64 = 100: goto 85 */
void func100(struct regs* myreg){
    myreg->mic_com_reg = 0x8385;
    myreg->count_mic_com = 133;
    myreg->buffer_reg = myreg->status_register;
}
/* 65 = 101: BIT(8, myreg->comm_reg) == 0) --> goto 7B */
void func101(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xa87b;
    if ((256 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 123;
}
/* 66 = 102: goto 7E */
void func102(struct regs* myreg){
    myreg->mic_com_reg = 0x837e;
    myreg->count_mic_com = 126;
    myreg->buffer_reg = myreg->status_register;
}
/* 67 = 103: if (BIT(9, myreg->comm_reg) == 0) --> goto 6A */
void func103(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xa96a;
    if ((512 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 106;
}
/* 68 = 104: BIT(8, myreg->comm_reg) == 0) --> goto 7B */
void func104(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xa876;
    if ((0x100 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 0x76;
}
/* 69 = 105: goto 79 */
void func105(struct regs* myreg){
    myreg->mic_com_reg = 0x8379;
    myreg->count_mic_com = 121;
    myreg->buffer_reg = myreg->status_register;
}
/* 6a = 106: if BIT(8, myreg->comm_reg) == 0) --> goto 88 */
void func106(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xa888;
    if ((256 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 136;
}
/* 6b = 107: goto  87 */
void func107(struct regs* myreg){
    myreg->mic_com_reg = 0x8387;
    myreg->count_mic_com = 87;
    myreg->buffer_reg = myreg->status_register;
}
/* 6c = 108: if (BIT(9, myreg->comm_reg) == 0) --> goto 6F */
void func108(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xa96f;
    if ((512 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 111;;
}
/* 6d = 109: if BIT(8, myreg->comm_reg) == 0) --> goto 8A */
void func109(struct regs* myreg){
    myreg->buffer_reg = myreg->comm_reg;
    myreg->mic_com_reg = 0xa88a;
    if ((256 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 138;
}
/* 6e = 110: goto 8c */
void func110(struct regs* myreg){
    myreg->mic_com_reg = 0x838c;
    myreg->count_mic_com = 140;
    myreg->buffer_reg = myreg->status_register;
}
/* 6f = 111: if BIT(8, myreg->comm_reg) == 0) --> goto 73 */
void func111(struct regs* myreg){
    myreg->mic_com_reg = 0xa873;
    if ((256 & myreg->comm_reg) == 0)
        myreg->count_mic_com = 115;
}
/* DEC */
/* 70 = 112: myreg->accum - 1 --> buff_reg */
void func112(struct regs* myreg){
    myreg->mic_com_reg = 0x1080;
    myreg->buffer_reg = myreg->accum - 1;
}
/* 71 = 113: buffer --> a, c, n, z */
void func113(struct regs* myreg){
    myreg->mic_com_reg = 0x4075;
    if ((myreg->buffer_reg & 131072) == 131072){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
    if(myreg->accum == 0){
        myreg->status_register |= 2;
        myreg->n_bit = 1;
    }
    else{
        myreg->status_register &= 509;
        myreg->n_bit = 0;
    }
}
/* 72 = 114: goto 90 */
void func114(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* INC */
/* 73 = 115: myreg->accum + 1 --> buffer */
void func115(struct regs* myreg){
    myreg->mic_com_reg = 0x1010;
    myreg->buffer_reg = myreg->accum + 1;
}
/* 74 = 116: buffer --> a, c, n, z */
void func116(struct regs* myreg){
    myreg->mic_com_reg = 0x4075;
    if ((myreg->buffer_reg & 131072) == 131072){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
    if(myreg->accum == 0){
        myreg->status_register |= 2;
        myreg->n_bit = 1;
    }
    else{
        myreg->status_register &= 509;
        myreg->n_bit = 0;
    }
}
/* 75 = 117: goto 90 */
void func117(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* 76 = 118: 0 --> myreg->buffer_reg */
void func118(struct regs* myreg){
    myreg->buffer_reg = 0;
    myreg->mic_com_reg = 0x0020;
}
/* 77 = 119: buffer --> a, n, z */
void func119(struct regs* myreg){
    myreg->mic_com_reg = 0x4035;
    if ((myreg->buffer_reg & 131072) == 131072){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
}
/* 78 = 120: goto 90 */
void func120(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* CLC */
/* 79 = 121: 0 --> c */
void func121(struct regs* myreg){
    myreg->mic_com_reg = 0x4080;
    myreg->c_bit = 0;
}
/* 7a = 122: goto 90 */
void func122(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* CMA */
/* 7b = 123: ~A --> buff */
void func123(struct regs* myreg){
    myreg->mic_com_reg = 0x1040;
    myreg->buffer_reg = (~myreg->accum);
}
/* 7c = 124: buffer --> a, n, z */
void func124(struct regs* myreg){
    myreg->mic_com_reg = 0x4035;
    if ((myreg->buffer_reg & 131072) == 131072){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
}
/* 7d = 125: goto 90 */
void func125(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* CMC */
/* 7e = 126: (0, stat_reg) == 0) --> goto 80 */
void func126(struct regs* myreg){
    myreg->mic_com_reg = 0x8080;
    if ((myreg->status_register & 1) == 0)
        myreg->count_mic_com = 128;
}
/* 7f = 127: goto 79 */
void func127(/*int val,*/ struct regs* myreg){
    myreg->mic_com_reg = 0x8379;
    myreg->count_mic_com = 121;
}
/* 80 = 128: 1 --> c */
void func128(struct regs* myreg){
    myreg->mic_com_reg = 0x40c0;
    myreg->c_bit = 1;
    myreg->status_register |= 1;
}
/* 81 = 129: goto 90 */
void func129(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* ROL */
/* 82 = 130: RAL(A) --> buff */
void func130(struct regs* myreg){
    myreg->mic_com_reg = 0x0008;
    myreg->buffer_reg = (myreg->accum << 1) + myreg->c_bit;
}
/* 83 = 131: buffer --> a, c, n, z */
void func131(struct regs* myreg){
    myreg->mic_com_reg = 0x4075;
    if ((myreg->accum & 0x8000) != 0){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
    if(myreg->accum == 0){
        myreg->status_register |= 2;
        myreg->n_bit = 1;
    }
    else{
        myreg->status_register &= 509;
        myreg->n_bit = 0;
    }
}
/* 84 = 132: goto 90 */
void func132(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
    myreg->buffer_reg = myreg->status_register;
}
/* ROR */
/* 85 = 133: RAR(A) --> buff */
void func133(struct regs* myreg){
    myreg->mic_com_reg = 0x0004;
    myreg->buffer_reg = (myreg->c_bit * 0x8000) + (myreg->accum >> 1);
}
/* 86 - 134: br --> a c n z */
void func134(struct regs* myreg){
    myreg->mic_com_reg = 0x4075;
    if ((myreg->accum & 1) != 0){
        myreg->c_bit = 1;
        myreg->status_register |= 1;
    }
    else{
        myreg->c_bit = 0;
        myreg->status_register &= 510;
    }
    myreg->accum = myreg->buffer_reg & 131071;
    /* bit z == sign bit */
    if((myreg->accum & 0x8000) == 0){
        myreg->z_bit = 0;
        myreg->status_register &= 507;
    }
    else{
        myreg->status_register |= 4;
        myreg->z_bit = 1;
    }
    if(myreg->accum == 0){
        myreg->status_register |= 2;
        myreg->n_bit = 1;
    }
    else{
        myreg->status_register &= 509;
        myreg->n_bit = 0;
    }
}
/* NOP */
/* 87 = 135: goto 90 */
void func135(struct regs* myreg){
    myreg->mic_com_reg = 0x8390;
    myreg->count_mic_com = 144;
}
/* HLT */
/* 88 = 136: hlt */
void func136(struct regs* myreg){
    myreg->mic_com_reg = 0x4008;
    /* the end */
}
