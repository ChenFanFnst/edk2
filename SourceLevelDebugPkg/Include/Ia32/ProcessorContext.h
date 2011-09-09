/** @file
  IA32/x64 architecture specific defintions needed by debug transfer protocol.It is only
  intended to be used by Debug related module implementation.

  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __PROCESSOR_CONTEXT_H__
#define __PROCESSOR_CONTEXT_H__

//
//  IA-32/x64 processor register index table
//
#define SOFT_DEBUGGER_REGISTER_DR0      0
#define SOFT_DEBUGGER_REGISTER_DR1      1
#define SOFT_DEBUGGER_REGISTER_DR2      2
#define SOFT_DEBUGGER_REGISTER_DR3      3
#define SOFT_DEBUGGER_REGISTER_DR6      4
#define SOFT_DEBUGGER_REGISTER_DR7      5
#define SOFT_DEBUGGER_REGISTER_EFLAGS   6
#define SOFT_DEBUGGER_REGISTER_LDTR     7
#define SOFT_DEBUGGER_REGISTER_TR       8
#define SOFT_DEBUGGER_REGISTER_GDTR0    9  // the low 32bit of GDTR
#define SOFT_DEBUGGER_REGISTER_GDTR1   10 // the high 32bit of GDTR
#define SOFT_DEBUGGER_REGISTER_IDTR0   11 // the low 32bit of IDTR
#define SOFT_DEBUGGER_REGISTER_IDTR1   12 // the high 32bot of IDTR
#define SOFT_DEBUGGER_REGISTER_EIP     13
#define SOFT_DEBUGGER_REGISTER_GS      14
#define SOFT_DEBUGGER_REGISTER_FS      15
#define SOFT_DEBUGGER_REGISTER_ES      16
#define SOFT_DEBUGGER_REGISTER_DS      17
#define SOFT_DEBUGGER_REGISTER_CS      18
#define SOFT_DEBUGGER_REGISTER_SS      19
#define SOFT_DEBUGGER_REGISTER_CR0     20
#define SOFT_DEBUGGER_REGISTER_CR1     21
#define SOFT_DEBUGGER_REGISTER_CR2     22
#define SOFT_DEBUGGER_REGISTER_CR3     23
#define SOFT_DEBUGGER_REGISTER_CR4     24

#define SOFT_DEBUGGER_REGISTER_DI      25
#define SOFT_DEBUGGER_REGISTER_SI      26
#define SOFT_DEBUGGER_REGISTER_BP      27
#define SOFT_DEBUGGER_REGISTER_SP      28
#define SOFT_DEBUGGER_REGISTER_DX      29
#define SOFT_DEBUGGER_REGISTER_CX      30
#define SOFT_DEBUGGER_REGISTER_BX      31
#define SOFT_DEBUGGER_REGISTER_AX      32

//
// This below registers are only available for x64 (not valid for Ia32 mode)
//
#define SOFT_DEBUGGER_REGISTER_CR8     33
#define SOFT_DEBUGGER_REGISTER_R8      34
#define SOFT_DEBUGGER_REGISTER_R9      35
#define SOFT_DEBUGGER_REGISTER_R10     36
#define SOFT_DEBUGGER_REGISTER_R11     37
#define SOFT_DEBUGGER_REGISTER_R12     38
#define SOFT_DEBUGGER_REGISTER_R13     39
#define SOFT_DEBUGGER_REGISTER_R14     40
#define SOFT_DEBUGGER_REGISTER_R15     41

#define SOFT_DEBUGGER_REGISTER_MAX_COUNT_IA32     33
#define SOFT_DEBUGGER_REGISTER_MAX_COUNT_X64      42

//
// This below registers are FP / MMX / XMM registers
//
#define SOFT_DEBUGGER_REGISTER_FP_BASE            50

#define SOFT_DEBUGGER_REGISTER_FP_FCW          (SOFT_DEBUGGER_REGISTER_FP_BASE +  0)
#define SOFT_DEBUGGER_REGISTER_FP_FSW          (SOFT_DEBUGGER_REGISTER_FP_BASE +  1)
#define SOFT_DEBUGGER_REGISTER_FP_FTW          (SOFT_DEBUGGER_REGISTER_FP_BASE +  2)
#define SOFT_DEBUGGER_REGISTER_FP_OPCODE       (SOFT_DEBUGGER_REGISTER_FP_BASE +  3)
#define SOFT_DEBUGGER_REGISTER_FP_EIP          (SOFT_DEBUGGER_REGISTER_FP_BASE +  4)
#define SOFT_DEBUGGER_REGISTER_FP_CS           (SOFT_DEBUGGER_REGISTER_FP_BASE +  5)
#define SOFT_DEBUGGER_REGISTER_FP_DATAOFFSET   (SOFT_DEBUGGER_REGISTER_FP_BASE +  6)
#define SOFT_DEBUGGER_REGISTER_FP_DS           (SOFT_DEBUGGER_REGISTER_FP_BASE +  7)
#define SOFT_DEBUGGER_REGISTER_FP_MXCSR        (SOFT_DEBUGGER_REGISTER_FP_BASE +  8)
#define SOFT_DEBUGGER_REGISTER_FP_MXCSR_MASK   (SOFT_DEBUGGER_REGISTER_FP_BASE +  9)
#define SOFT_DEBUGGER_REGISTER_ST0             (SOFT_DEBUGGER_REGISTER_FP_BASE + 10)
#define SOFT_DEBUGGER_REGISTER_ST1             (SOFT_DEBUGGER_REGISTER_FP_BASE + 11)
#define SOFT_DEBUGGER_REGISTER_ST2             (SOFT_DEBUGGER_REGISTER_FP_BASE + 12)
#define SOFT_DEBUGGER_REGISTER_ST3             (SOFT_DEBUGGER_REGISTER_FP_BASE + 13)
#define SOFT_DEBUGGER_REGISTER_ST4             (SOFT_DEBUGGER_REGISTER_FP_BASE + 14)
#define SOFT_DEBUGGER_REGISTER_ST5             (SOFT_DEBUGGER_REGISTER_FP_BASE + 15)
#define SOFT_DEBUGGER_REGISTER_ST6             (SOFT_DEBUGGER_REGISTER_FP_BASE + 16)
#define SOFT_DEBUGGER_REGISTER_ST7             (SOFT_DEBUGGER_REGISTER_FP_BASE + 17)
#define SOFT_DEBUGGER_REGISTER_XMM0            (SOFT_DEBUGGER_REGISTER_FP_BASE + 18)
#define SOFT_DEBUGGER_REGISTER_XMM1            (SOFT_DEBUGGER_REGISTER_FP_BASE + 19)
#define SOFT_DEBUGGER_REGISTER_XMM2            (SOFT_DEBUGGER_REGISTER_FP_BASE + 20)
#define SOFT_DEBUGGER_REGISTER_XMM3            (SOFT_DEBUGGER_REGISTER_FP_BASE + 21)
#define SOFT_DEBUGGER_REGISTER_XMM4            (SOFT_DEBUGGER_REGISTER_FP_BASE + 22)
#define SOFT_DEBUGGER_REGISTER_XMM5            (SOFT_DEBUGGER_REGISTER_FP_BASE + 23)
#define SOFT_DEBUGGER_REGISTER_XMM6            (SOFT_DEBUGGER_REGISTER_FP_BASE + 24)
#define SOFT_DEBUGGER_REGISTER_XMM7            (SOFT_DEBUGGER_REGISTER_FP_BASE + 25)
#define SOFT_DEBUGGER_REGISTER_XMM8            (SOFT_DEBUGGER_REGISTER_FP_BASE + 26)
#define SOFT_DEBUGGER_REGISTER_XMM9            (SOFT_DEBUGGER_REGISTER_FP_BASE + 27)
#define SOFT_DEBUGGER_REGISTER_XMM10           (SOFT_DEBUGGER_REGISTER_FP_BASE + 28)
#define SOFT_DEBUGGER_REGISTER_XMM11           (SOFT_DEBUGGER_REGISTER_FP_BASE + 29)
#define SOFT_DEBUGGER_REGISTER_XMM12           (SOFT_DEBUGGER_REGISTER_FP_BASE + 30)
#define SOFT_DEBUGGER_REGISTER_XMM13           (SOFT_DEBUGGER_REGISTER_FP_BASE + 31)
#define SOFT_DEBUGGER_REGISTER_XMM14           (SOFT_DEBUGGER_REGISTER_FP_BASE + 32)
#define SOFT_DEBUGGER_REGISTER_XMM15           (SOFT_DEBUGGER_REGISTER_FP_BASE + 33)
#define SOFT_DEBUGGER_REGISTER_MM0             (SOFT_DEBUGGER_REGISTER_FP_BASE + 34)
#define SOFT_DEBUGGER_REGISTER_MM1             (SOFT_DEBUGGER_REGISTER_FP_BASE + 35)
#define SOFT_DEBUGGER_REGISTER_MM2             (SOFT_DEBUGGER_REGISTER_FP_BASE + 36)
#define SOFT_DEBUGGER_REGISTER_MM3             (SOFT_DEBUGGER_REGISTER_FP_BASE + 37)
#define SOFT_DEBUGGER_REGISTER_MM4             (SOFT_DEBUGGER_REGISTER_FP_BASE + 38)
#define SOFT_DEBUGGER_REGISTER_MM5             (SOFT_DEBUGGER_REGISTER_FP_BASE + 39)
#define SOFT_DEBUGGER_REGISTER_MM6             (SOFT_DEBUGGER_REGISTER_FP_BASE + 40)
#define SOFT_DEBUGGER_REGISTER_MM7             (SOFT_DEBUGGER_REGISTER_FP_BASE + 41)

//
// This below registers are for GDT, LDT, TSS
//
#define SOFT_DEBUGGER_REGISTER_OTHERS_BASE            100

#define SOFT_DEBUGGER_REGISTER_CS_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  0)
#define SOFT_DEBUGGER_REGISTER_SS_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  1)
#define SOFT_DEBUGGER_REGISTER_GS_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  2)
#define SOFT_DEBUGGER_REGISTER_FS_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  3)
#define SOFT_DEBUGGER_REGISTER_ES_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  4)
#define SOFT_DEBUGGER_REGISTER_DS_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  5)
#define SOFT_DEBUGGER_REGISTER_LDT_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE + 6)
#define SOFT_DEBUGGER_REGISTER_TSS_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE + 7)

#define SOFT_DEBUGGER_REGISTER_CS_BAS          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  8)
#define SOFT_DEBUGGER_REGISTER_SS_BAS          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  9)
#define SOFT_DEBUGGER_REGISTER_GS_BAS          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  10)
#define SOFT_DEBUGGER_REGISTER_FS_BAS          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  11)
#define SOFT_DEBUGGER_REGISTER_ES_BAS          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  12)
#define SOFT_DEBUGGER_REGISTER_DS_BAS          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  13)
#define SOFT_DEBUGGER_REGISTER_LDT_BAS         (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  14)
#define SOFT_DEBUGGER_REGISTER_TSS_BAS         (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  15)

#define SOFT_DEBUGGER_REGISTER_CSAS            (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  16)
#define SOFT_DEBUGGER_REGISTER_SSAS            (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  17)
#define SOFT_DEBUGGER_REGISTER_GSAS            (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  18)
#define SOFT_DEBUGGER_REGISTER_FSAS            (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  19)
#define SOFT_DEBUGGER_REGISTER_ESAS            (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  20)
#define SOFT_DEBUGGER_REGISTER_DSAS            (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  21)
#define SOFT_DEBUGGER_REGISTER_LDTAS           (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  22)
#define SOFT_DEBUGGER_REGISTER_TSSAS           (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  23)

#define SOFT_DEBUGGER_REGISTER_IDT_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE + 24)
#define SOFT_DEBUGGER_REGISTER_GDT_LIM          (SOFT_DEBUGGER_REGISTER_OTHERS_BASE + 25)
#define SOFT_DEBUGGER_REGISTER_IDT_BAS         (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  26)
#define SOFT_DEBUGGER_REGISTER_GDT_BAS         (SOFT_DEBUGGER_REGISTER_OTHERS_BASE +  27)


#define SOFT_DEBUGGER_MSR_EFER                (0xC0000080)

//
// Definition for the Index field for DEBUG_DATA_READ_REGISTER_GROUP
//
#define SOFT_DEBUGGER_REGISTER_GROUP_GPDRS32                1 //for cs,ds,es,fs,gs,ss,eflags,ebp,eip,esp,eax,ebx,ecx,edx,esi,edi,dr0,dr1,dr2,dr3,dr6,dr7
#define SOFT_DEBUGGER_REGISTER_GROUP_SEGMENT_LIMITS32       2 //for cslim,sslim,gslim,fslim,eslim,dslim,ldtlim,tsslim
#define SOFT_DEBUGGER_REGISTER_GROUP_SEGMENT_BASES32        3 //for csbas,ssbas,gsbas,fsbas,esbas,dsbas,ldtbas,tssbas

#define SOFT_DEBUGGER_REGISTER_GROUP_SEGMENT64              4  //for cs,ds,es,fs,gs,ss
#define SOFT_DEBUGGER_REGISTER_GROUP_GP2_64                 5  //for eflags,rbp,rip,rsp
#define SOFT_DEBUGGER_REGISTER_GROUP_GP64                   6  //for rax,rbx,rcx,rdx,rsi,rdi,r8,r9,r10,r11,r12,r13,r14,r15
#define SOFT_DEBUGGER_REGISTER_GROUP_DR64                   7  //for dr0,dr1,dr2,dr3,dr6,dr7
#define SOFT_DEBUGGER_REGISTER_GROUP_SEGMENT_BAS_LIM64      8  //for ldtbas,ldtlim,gdtbas,gdtlim,cslim,sslim,gslim,fslim,eslim,dslim,ldtlim,tsslim,csbas,ssbas,gsbas,fsbas,esbas,dsbas,ldtbas,tssbas
#define SOFT_DEBUGGER_REGISTER_GROUP_SEGMENT_BASES64        9  //for idtr,tr,csas,ssas,gsas,fsas,esas,dsas,idtas,tssas
#define SOFT_DEBUGGER_REGISTER_GROUP_CR64                   10 //for cr0,cr2,cr3,cr4,cr8
#define SOFT_DEBUGGER_REGISTER_GROUP_XMM64                  11 //for xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm8,xmm9,xmm10,xmm11,xmm12,xmm13,xmm14,xmm15


#endif
