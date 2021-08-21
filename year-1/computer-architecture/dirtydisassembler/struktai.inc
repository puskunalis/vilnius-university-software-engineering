r_000     db "AL$"
r_001     db "CL$"
r_010     db "DL$"
r_011     db "BL$"
r_100     db "AH$"
r_101     db "CH$"
r_110     db "DH$"
r_111     db "BH$"


r_array:
	dw r_000, r_001, r_010, r_011, r_100, r_101, r_110, r_111

rw_000    db "AX$"
rw_001    db "CX$"
rw_010    db "DX$"
rw_011    db "BX$"
rw_100    db "SP$"
rw_101    db "BP$"
rw_110    db "SI$"
rw_111    db "DI$"

rw32_000    db "EAX$"
rw32_001    db "ECX$"
rw32_010    db "EDX$"
rw32_011    db "EBX$"
rw32_100    db "ESP$"
rw32_101    db "EBP$"
rw32_110    db "ESI$"
rw32_111    db "EDI$"

rw_array:
	dw rw_000, rw_001, rw_010, rw_011, rw_100, rw_101, rw_110, rw_111
	
rw32_array:
	dw rw32_000, rw32_001, rw32_010, rw32_011, rw32_100, rw32_101, rw32_110, rw32_111

s_regES   db "ES$"
s_regCS   db "CS$"
s_regSS   db "SS$"
s_regDS   db "DS$"

sr_array:
	dw s_regES, s_regCS, s_regSS, s_regDS
	
registru_array:
	dw 0000, r_000, r_001, r_010, r_011, r_100, r_101, r_110, r_111
	dw rw_000, rw_001, rw_010, rw_011, rw_100, rw_101, rw_110, rw_111
	dw s_regES, s_regCS, s_regSS, s_regDS
	
reg32_array:
	times 9 dw 0000
	dw rw32_000, rw32_001, rw32_010, rw32_011, rw32_100, rw32_101, rw32_110, rw32_111

rm_000    db "BX+SI$"
rm_001    db "BX+DI$"
rm_010    db "BP+SI$"
rm_011    db "BP+DI$"
rm_100    db "SI$"
rm_101    db "DI$"
rm_110    db "BP$"
rm_111    db "BX$"

rm_array:
	dw rm_000, rm_001, rm_010, rm_011, rm_100, rm_101, rm_110, rm_111

t_opAAA         db    "AAA     $"
t_opAAD         db    "AAD     $"
t_opAAM         db    "AAM     $"
t_opAAS         db    "AAS     $"
t_opADC         db    "ADC     $"
t_opADD         db    "ADD     $"
t_opAND         db    "AND     $"
t_opCALL        db    "CALL    $"
t_opCALLF       db    "CALL    FAR $"
t_opCBW         db    "CBW     $"
t_opCLC         db    "CLC     $"
t_opCLD         db    "CLD     $"
t_opCLI         db    "CLI     $"
t_opCMC         db    "CMC     $"
t_opCMP         db    "CMP     $"
t_opCMPSB       db    "CMPSB$"
t_opCMPSW       db    "CMPSW$"
t_opCWD         db    "CWD     $"
t_opDAA         db    "DAA     $"
t_opDAS         db    "DAS     $"
t_opDEC         db    "DEC     $"
t_opDIV         db    "DIV     $"
t_opHLT         db    "HLT     $"
t_opIDIV        db    "IDIV    $"
t_opIMUL        db    "IMUL    $"
t_opIN          db    "IN      $"
t_opINC         db    "INC     $"
t_opINT         db    "INT     $"
t_opINTO        db    "INTO$"
t_opIRET        db    "IRET    $"
t_opJA          db    "JA      $"
t_opJAE         db    "JAE     $"
t_opJB          db    "JB      $"
t_opJBE         db    "JBE     $"
t_opJCXZ        db    "JCXZ    $"
t_opJG          db    "JG      $"
t_opJGE         db    "JGE     $"
t_opJL          db    "JL      $"
t_opJLE         db    "JLE     $"
t_opJMP         db    "JMP     $"
t_opJMPF        db    "JMP     FAR $"
t_opJNO         db    "JNO     $"
t_opJNS         db    "JNS     $"
t_opJNZ         db    "JNZ     $"
t_opJO          db    "JO      $"
t_opJPE         db    "JPE     $"
t_opJPO         db    "JPO     $"
t_opJS          db    "JS      $"
t_opJZ          db    "JZ      $"
t_opLAHF        db    "LAHF    $"
t_opLDS         db    "LDS     $"
t_opLEA         db    "LEA     $"
t_opLES         db    "LES     $"
t_opLOCK        db    "LOCK    $"
t_opLODSB       db    "LODSB$"
t_opLODSW       db    "LODSW$"
t_opLOOP        db    "LOOPW   $"
t_opLOOPNZ      db    "LOOPNZW $"
t_opLOOPZ       db    "LOOPZW  $"
t_opMOV         db    "MOV     $"
t_opMOVSB       db    "MOVSB$"
t_opMOVSW       db    "MOVSW$"
t_opMUL         db    "MUL     $"
t_opNEG         db    "NEG     $"
t_opNOP         db    "NOP$"
t_opNOT         db    "NOT     $"
t_opOR          db    "OR      $"
t_opOUT         db    "OUT     $"
t_opPOP         db    "POP     $"
t_opPOPF        db    "POPF    $"
t_opPUSH        db    "PUSH    $"
t_opPUSHF       db    "PUSHF   $"
t_opRCL         db    "RCL     $"
t_opRCR         db    "RCR     $"
t_opREP         db    "REPE    $"
t_opREPNE       db    "REPNE   $"
t_opRET         db    "RET     $"
t_opRETF        db    "RETF    $"
t_opREPZ        db    "REPZ    $"
t_opROL         db    "ROL     $"
t_opROR         db    "ROR     $"
t_opSAHF        db    "SAHF    $"
t_opSAL         db    "SAL     $"
t_opSAR         db    "SAR     $"
t_opSBB         db    "SBB     $"
t_opSCASB       db    "SCASB$"
t_opSCASW       db    "SCASW$"
t_opSEGCS       db    "SEGCS   $"
t_opSEGDS       db    "SEGDS   $"
t_opSEGES       db    "SEGES   $"
t_opSEGSS       db    "SEGSS   $"
t_opSHL         db    "SHL     $"
t_opSHR         db    "SHR     $"
t_opSTC         db    "STC     $"
t_opSTD         db    "STD     $"
t_opSTI         db    "STI     $"
t_opSTOS        db    "STOS    $" 
t_opSTOSB       db    "STOSB$"
t_opSTOSW       db    "STOSW$"
t_opSUB         db    "SUB     $"
t_opTEST        db    "TEST    $"
t_opWAIT        db    "WAIT    $"
t_opXCHG        db    "XCHG    $"
t_opXLAT        db    "XLAT    $"
t_opXOR         db    "XOR     $"
t_opESC         db    "ESC     $"
t_opEMPTY       db    "$"
t_opUNSUPPORTED db    "$"
t_opUNKNOWN     db    "$"

; 80-83
grp1:
    dw t_opADD, t_opOR, t_opADC, t_opSBB
    dw t_opAND, t_opSUB, t_opXOR, t_opCMP
	
; D0-D3
grp2:
    dw t_opROL, t_opROR, t_opRCL, t_opRCR
    dw t_opSHL, t_opSHR, t_opSAL, t_opSAR
	
; F6-F7
grp3: 
    dw t_opTEST, t_opTEST, t_opNOT, t_opNEG
    dw t_opMUL, t_opIMUL, t_opDIV, t_opIDIV
    
; FE
grp4:
    dw t_opINC, t_opDEC, t_opUNKNOWN, t_opUNKNOWN
    dw t_opUNKNOWN, t_opUNKNOWN, t_opUNKNOWN, t_opUNKNOWN

; FF   
grp5:
    dw t_opINC, t_opDEC, t_opCALL, t_opCALLF
    dw t_opJMP, t_opJMP, t_opPUSH, t_opUNKNOWN

argNone       equ 0
argAL         equ 1
argCL         equ 2
argDL         equ 3
argBL         equ 4
argAH         equ 5
argCH         equ 6
argDH         equ 7
argBH         equ 8
argAX         equ 9
argCX         equ 10
argDX         equ 11
argBX         equ 12
argSP         equ 13
argBP         equ 14
argSI         equ 15 
argDI         equ 16
  
argES         equ 17
argCS         equ 18
argSS         equ 19
argDS         equ 20
  
argConst1     equ 21
argConst3     equ 22
; Argumentai nereikalaujantys adresavimo baito
argImm8       equ 23
argEImm8      equ 24
argShort      equ 25
argOffs8      equ 26
argImm16      equ 27
argOffs16     equ 28
argNear       equ 29 
argFar        equ 30
; Argumentai reikalaujantys adresavimo baito
argRegMem8    equ 31
argRegMem16   equ 32
argReg8       equ 33
argReg16      equ 34 
argSegReg     equ 35

; Extra atvejis, nereikalauja adresavimo baito
argUseless    equ 36

kNormal       equ 1  
kExtraOpk     equ 2
kEmpty        equ 3
kUnknown      equ 3
kUnsupported  equ 3
kPrefix       equ 4
kPrefixOp     equ 5
kUseless      equ 6
k32bitPrefix  equ 7

struc opkodas
	pavadinimas: resw 1
	tipas: resb 1
	arg1: resb 1
	arg2: resb 1
endstruc

op00: istruc opkodas
    at pavadinimas, dw t_opADD
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op01: istruc opkodas
    at pavadinimas, dw t_opADD
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op02: istruc opkodas
    at pavadinimas, dw t_opADD
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op03: istruc opkodas
    at pavadinimas, dw t_opADD
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op04: istruc opkodas
    at pavadinimas, dw t_opADD
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
op05: istruc opkodas
    at pavadinimas, dw t_opADD
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
op06: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argES
    at arg2, db argNone
    iend
op07: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argES
    at arg2, db argNone
    iend
op08: istruc opkodas
    at pavadinimas, dw t_opOR
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op09: istruc opkodas
    at pavadinimas, dw t_opOR
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op0A: istruc opkodas
    at pavadinimas, dw t_opOR
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op0B: istruc opkodas
    at pavadinimas, dw t_opOR
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op0C: istruc opkodas
    at pavadinimas, dw t_opOR
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
op0D: istruc opkodas
    at pavadinimas, dw t_opOR
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
op0E: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argCS
    at arg2, db argNone
    iend
op0F: istruc opkodas
    at pavadinimas, dw t_opUNKNOWN
    at tipas, db kUnknown
    at arg1, db argNone
    at arg2, db argNone
    iend
op10: istruc opkodas
    at pavadinimas, dw t_opADC
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op11: istruc opkodas
    at pavadinimas, dw t_opADC
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op12: istruc opkodas
    at pavadinimas, dw t_opADC
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op13: istruc opkodas
    at pavadinimas, dw t_opADC
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op14: istruc opkodas
    at pavadinimas, dw t_opADC
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
op15: istruc opkodas
    at pavadinimas, dw t_opADC
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
op16: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argSS
    at arg2, db argNone
    iend
op17: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argSS
    at arg2, db argNone
    iend
op18: istruc opkodas
    at pavadinimas, dw t_opSBB
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op19: istruc opkodas
    at pavadinimas, dw t_opSBB
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op1A: istruc opkodas
    at pavadinimas, dw t_opSBB
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op1B: istruc opkodas
    at pavadinimas, dw t_opSBB
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op1C: istruc opkodas
    at pavadinimas, dw t_opSBB
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
op1D: istruc opkodas
    at pavadinimas, dw t_opSBB
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
op1E: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argDS
    at arg2, db argNone
    iend
op1F: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argDS
    at arg2, db argNone
    iend
op20: istruc opkodas
    at pavadinimas, dw t_opAND
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op21: istruc opkodas
    at pavadinimas, dw t_opAND
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op22: istruc opkodas
    at pavadinimas, dw t_opAND
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op23: istruc opkodas
    at pavadinimas, dw t_opAND
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op24: istruc opkodas
    at pavadinimas, dw t_opAND
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
op25: istruc opkodas
    at pavadinimas, dw t_opAND
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
op26: istruc opkodas
    at pavadinimas, dw s_regES
    at tipas, db kPrefix
    at arg1, db argNone
    at arg2, db argNone
    iend
op27: istruc opkodas
    at pavadinimas, dw t_opDAA
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op28: istruc opkodas
    at pavadinimas, dw t_opSUB
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op29: istruc opkodas
    at pavadinimas, dw t_opSUB
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op2A: istruc opkodas
    at pavadinimas, dw t_opSUB
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op2B: istruc opkodas
    at pavadinimas, dw t_opSUB
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op2C: istruc opkodas
    at pavadinimas, dw t_opSUB
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
op2D: istruc opkodas
    at pavadinimas, dw t_opSUB
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
op2E: istruc opkodas
    at pavadinimas, dw s_regCS
    at tipas, db kPrefix
    at arg1, db argNone
    at arg2, db argNone
    iend
op2F: istruc opkodas
    at pavadinimas, dw t_opDAS
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op30: istruc opkodas
    at pavadinimas, dw t_opXOR
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op31: istruc opkodas
    at pavadinimas, dw t_opXOR
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op32: istruc opkodas
    at pavadinimas, dw t_opXOR
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op33: istruc opkodas
    at pavadinimas, dw t_opXOR
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op34: istruc opkodas
    at pavadinimas, dw t_opXOR
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
op35: istruc opkodas
    at pavadinimas, dw t_opXOR
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
op36: istruc opkodas
    at pavadinimas, dw s_regSS
    at tipas, db kPrefix
    at arg1, db argNone
    at arg2, db argNone
    iend
op37: istruc opkodas
    at pavadinimas, dw t_opAAA
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op38: istruc opkodas
    at pavadinimas, dw t_opCMP
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op39: istruc opkodas
    at pavadinimas, dw t_opCMP
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op3A: istruc opkodas
    at pavadinimas, dw t_opCMP
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op3B: istruc opkodas
    at pavadinimas, dw t_opCMP
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op3C: istruc opkodas
    at pavadinimas, dw t_opCMP
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
op3D: istruc opkodas
    at pavadinimas, dw t_opCMP
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
op3E: istruc opkodas
    at pavadinimas, dw s_regDS
    at tipas, db kPrefix
    at arg1, db argNone
    at arg2, db argNone
    iend
op3F: istruc opkodas
    at pavadinimas, dw t_opAAS
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op40: istruc opkodas
    at pavadinimas, dw t_opINC
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argNone
    iend
op41: istruc opkodas
    at pavadinimas, dw t_opINC
    at tipas, db kNormal
    at arg1, db argCX
    at arg2, db argNone
    iend
op42: istruc opkodas
    at pavadinimas, dw t_opINC
    at tipas, db kNormal
    at arg1, db argDX
    at arg2, db argNone
    iend
op43: istruc opkodas
    at pavadinimas, dw t_opINC
    at tipas, db kNormal
    at arg1, db argBX
    at arg2, db argNone
    iend
op44: istruc opkodas
    at pavadinimas, dw t_opINC
    at tipas, db kNormal
    at arg1, db argSP
    at arg2, db argNone
    iend
op45: istruc opkodas
    at pavadinimas, dw t_opINC
    at tipas, db kNormal
    at arg1, db argBP
    at arg2, db argNone
    iend
op46: istruc opkodas
    at pavadinimas, dw t_opINC
    at tipas, db kNormal
    at arg1, db argSI
    at arg2, db argNone
    iend
op47: istruc opkodas
    at pavadinimas, dw t_opINC
    at tipas, db kNormal
    at arg1, db argDI
    at arg2, db argNone
    iend
op48: istruc opkodas
    at pavadinimas, dw t_opDEC
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argNone
    iend
op49: istruc opkodas
    at pavadinimas, dw t_opDEC
    at tipas, db kNormal
    at arg1, db argCX
    at arg2, db argNone
    iend
op4A: istruc opkodas
    at pavadinimas, dw t_opDEC
    at tipas, db kNormal
    at arg1, db argDX
    at arg2, db argNone
    iend
op4B: istruc opkodas
    at pavadinimas, dw t_opDEC
    at tipas, db kNormal
    at arg1, db argBX
    at arg2, db argNone
    iend
op4C: istruc opkodas
    at pavadinimas, dw t_opDEC
    at tipas, db kNormal
    at arg1, db argSP
    at arg2, db argNone
    iend
op4D: istruc opkodas
    at pavadinimas, dw t_opDEC
    at tipas, db kNormal
    at arg1, db argBP
    at arg2, db argNone
    iend
op4E: istruc opkodas
    at pavadinimas, dw t_opDEC
    at tipas, db kNormal
    at arg1, db argSI
    at arg2, db argNone
    iend
op4F: istruc opkodas
    at pavadinimas, dw t_opDEC
    at tipas, db kNormal
    at arg1, db argDI
    at arg2, db argNone
    iend
op50: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argNone
    iend
op51: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argCX
    at arg2, db argNone
    iend
op52: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argDX
    at arg2, db argNone
    iend
op53: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argBX
    at arg2, db argNone
    iend
op54: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argSP
    at arg2, db argNone
    iend
op55: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argBP
    at arg2, db argNone
    iend
op56: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argSI
    at arg2, db argNone
    iend
op57: istruc opkodas
    at pavadinimas, dw t_opPUSH
    at tipas, db kNormal
    at arg1, db argDI
    at arg2, db argNone
    iend
op58: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argNone
    iend
op59: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argCX
    at arg2, db argNone
    iend
op5A: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argDX
    at arg2, db argNone
    iend
op5B: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argBX
    at arg2, db argNone
    iend
op5C: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argSP
    at arg2, db argNone
    iend
op5D: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argBP
    at arg2, db argNone
    iend
op5E: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argSI
    at arg2, db argNone
    iend
op5F: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argDI
    at arg2, db argNone
    iend
op60: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op61: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op62: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op63: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op64: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op65: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op66: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db k32bitPrefix
    at arg1, db argNone
    at arg2, db argNone
    iend
op67: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kEmpty
    at arg1, db argNone
    at arg2, db argNone
    iend
op68: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kEmpty
    at arg1, db argNone
    at arg2, db argNone
    iend
op69: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op6A: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op6B: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op6C: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op6D: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op6E: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op6F: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
op70: istruc opkodas
    at pavadinimas, dw t_opJO
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op71: istruc opkodas
    at pavadinimas, dw t_opJNO
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op72: istruc opkodas
    at pavadinimas, dw t_opJB
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op73: istruc opkodas
    at pavadinimas, dw t_opJAE
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op74: istruc opkodas
    at pavadinimas, dw t_opJZ
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op75: istruc opkodas
    at pavadinimas, dw t_opJNZ
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op76: istruc opkodas
    at pavadinimas, dw t_opJBE
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op77: istruc opkodas
    at pavadinimas, dw t_opJA
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op78: istruc opkodas
    at pavadinimas, dw t_opJS
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op79: istruc opkodas
    at pavadinimas, dw t_opJNS
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op7A: istruc opkodas
    at pavadinimas, dw t_opJPE
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op7B: istruc opkodas
    at pavadinimas, dw t_opJPO
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op7C: istruc opkodas
    at pavadinimas, dw t_opJL
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op7D: istruc opkodas
    at pavadinimas, dw t_opJGE
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op7E: istruc opkodas
    at pavadinimas, dw t_opJLE
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op7F: istruc opkodas
    at pavadinimas, dw t_opJG
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
op80: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem8
    at arg2, db argImm8
    iend
op81: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem16
    at arg2, db argImm16
    iend
op82: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem8
    at arg2, db argImm8
    iend
op83: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem16
    at arg2, db argEImm8
    iend
op84: istruc opkodas
    at pavadinimas, dw t_opTEST
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op85: istruc opkodas
    at pavadinimas, dw t_opTEST
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op86: istruc opkodas
    at pavadinimas, dw t_opXCHG
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op87: istruc opkodas
    at pavadinimas, dw t_opXCHG
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op88: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argReg8
    iend
op89: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argReg16
    iend
op8A: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argReg8
    at arg2, db argRegMem8
    iend
op8B: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op8C: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argSegReg
    iend
op8D: istruc opkodas
    at pavadinimas, dw t_opLEA
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
op8E: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argSegReg
    at arg2, db argRegMem16
    iend
op8F: istruc opkodas
    at pavadinimas, dw t_opPOP
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argNone
    iend
op90: istruc opkodas
    at pavadinimas, dw t_opNOP
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op91: istruc opkodas
    at pavadinimas, dw t_opXCHG
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argCX
    iend
op92: istruc opkodas
    at pavadinimas, dw t_opXCHG
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argDX
    iend
op93: istruc opkodas
    at pavadinimas, dw t_opXCHG
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argBX
    iend
op94: istruc opkodas
    at pavadinimas, dw t_opXCHG
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argSP
    iend
op95: istruc opkodas
    at pavadinimas, dw t_opXCHG
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argBP
    iend
op96: istruc opkodas
    at pavadinimas, dw t_opXCHG
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argSI
    iend
op97: istruc opkodas
    at pavadinimas, dw t_opXCHG
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argDI
    iend
op98: istruc opkodas
    at pavadinimas, dw t_opCBW
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op99: istruc opkodas
    at pavadinimas, dw t_opCWD
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op9A: istruc opkodas
    at pavadinimas, dw t_opCALLF
    at tipas, db kNormal
    at arg1, db argFar
    at arg2, db argNone
    iend
op9B: istruc opkodas
    at pavadinimas, dw t_opWAIT
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op9C: istruc opkodas
    at pavadinimas, dw t_opPUSHF
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op9D: istruc opkodas
    at pavadinimas, dw t_opPOPF
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op9E: istruc opkodas
    at pavadinimas, dw t_opSAHF
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
op9F: istruc opkodas
    at pavadinimas, dw t_opLAHF
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opA0: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argOffs8
    iend
opA1: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argOffs16
    iend
opA2: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argOffs8
    at arg2, db argAL
    iend
opA3: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argOffs16
    at arg2, db argAX
    iend
opA4: istruc opkodas
    at pavadinimas, dw t_opMOVSB
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opA5: istruc opkodas
    at pavadinimas, dw t_opMOVSW
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opA6: istruc opkodas
    at pavadinimas, dw t_opCMPSB
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opA7: istruc opkodas
    at pavadinimas, dw t_opCMPSW
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opA8: istruc opkodas
    at pavadinimas, dw t_opTEST
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
opA9: istruc opkodas
    at pavadinimas, dw t_opTEST
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
opAA: istruc opkodas
    at pavadinimas, dw t_opSTOSB
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opAB: istruc opkodas
    at pavadinimas, dw t_opSTOSW
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opAC: istruc opkodas
    at pavadinimas, dw t_opLODSB
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opAD: istruc opkodas
    at pavadinimas, dw t_opLODSW
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opAE: istruc opkodas
    at pavadinimas, dw t_opSCASB
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opAF: istruc opkodas
    at pavadinimas, dw t_opSCASW
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opB0: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
opB1: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argCL
    at arg2, db argImm8
    iend
opB2: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argDL
    at arg2, db argImm8
    iend
opB3: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argBL
    at arg2, db argImm8
    iend
opB4: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argAH
    at arg2, db argImm8
    iend
opB5: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argCH
    at arg2, db argImm8
    iend
opB6: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argDH
    at arg2, db argImm8
    iend
opB7: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argBH
    at arg2, db argImm8
    iend
opB8: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm16
    iend
opB9: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argCX
    at arg2, db argImm16
    iend
opBA: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argDX
    at arg2, db argImm16
    iend
opBB: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argBX
    at arg2, db argImm16
    iend
opBC: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argSP
    at arg2, db argImm16
    iend
opBD: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argBP
    at arg2, db argImm16
    iend
opBE: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argSI
    at arg2, db argImm16
    iend
opBF: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argDI
    at arg2, db argImm16
    iend
opC0: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
opC1: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
opC2: istruc opkodas
    at pavadinimas, dw t_opRET
    at tipas, db kNormal
    at arg1, db argImm16
    at arg2, db argNone
    iend
opC3: istruc opkodas
    at pavadinimas, dw t_opRET
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opC4: istruc opkodas
    at pavadinimas, dw t_opLES
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
opC5: istruc opkodas
    at pavadinimas, dw t_opLDS
    at tipas, db kNormal
    at arg1, db argReg16
    at arg2, db argRegMem16
    iend
opC6: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argImm8
    iend
opC7: istruc opkodas
    at pavadinimas, dw t_opMOV
    at tipas, db kNormal
    at arg1, db argRegMem16
    at arg2, db argImm16
    iend
opC8: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
opC9: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
opCA: istruc opkodas
    at pavadinimas, dw t_opRETF
    at tipas, db kNormal
    at arg1, db argImm16
    at arg2, db argNone
    iend
opCB: istruc opkodas
    at pavadinimas, dw t_opRETF
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opCC: istruc opkodas
    at pavadinimas, dw t_opINT
    at tipas, db kNormal
    at arg1, db argConst3
    at arg2, db argNone
    iend
opCD: istruc opkodas
    at pavadinimas, dw t_opINT
    at tipas, db kNormal
    at arg1, db argImm8
    at arg2, db argNone
    iend
opCE: istruc opkodas
    at pavadinimas, dw t_opINTO
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opCF: istruc opkodas
    at pavadinimas, dw t_opIRET
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opD0: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem8
    at arg2, db argConst1
    iend
opD1: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem16
    at arg2, db argConst1
    iend
opD2: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem8
    at arg2, db argCL
    iend
opD3: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem16
    at arg2, db argCL
    iend
opD4: istruc opkodas
    at pavadinimas, dw t_opAAM
    at tipas, db kNormal
    at arg1, db argImm8
    at arg2, db argNone
    iend
opD5: istruc opkodas
    at pavadinimas, dw t_opAAD
    at tipas, db kNormal
    at arg1, db argImm8
    at arg2, db argNone
    iend
opD6: istruc opkodas
    at pavadinimas, dw t_opUNSUPPORTED
    at tipas, db kUnsupported
    at arg1, db argNone
    at arg2, db argNone
    iend
opD7: istruc opkodas
    at pavadinimas, dw t_opXLAT
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opD8: istruc opkodas
    at pavadinimas, dw t_opESC
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opD9: istruc opkodas
    at pavadinimas, dw t_opESC
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opDA: istruc opkodas
    at pavadinimas, dw t_opESC
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opDB: istruc opkodas
    at pavadinimas, dw t_opESC
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opDC: istruc opkodas
    at pavadinimas, dw t_opESC
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opDD: istruc opkodas
    at pavadinimas, dw t_opESC
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opDE: istruc opkodas
    at pavadinimas, dw t_opESC
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opDF: istruc opkodas
    at pavadinimas, dw t_opESC
    at tipas, db kNormal
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opE0: istruc opkodas
    at pavadinimas, dw t_opLOOPNZ
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
opE1: istruc opkodas
    at pavadinimas, dw t_opLOOPZ
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
opE2: istruc opkodas
    at pavadinimas, dw t_opLOOP
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
opE3: istruc opkodas
    at pavadinimas, dw t_opJCXZ
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
opE4: istruc opkodas
    at pavadinimas, dw t_opIN
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
opE5: istruc opkodas
    at pavadinimas, dw t_opIN
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm8
    iend
opE6: istruc opkodas
    at pavadinimas, dw t_opOUT
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argImm8
    iend
opE7: istruc opkodas
    at pavadinimas, dw t_opOUT
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argImm8
    iend
opE8: istruc opkodas
    at pavadinimas, dw t_opCALL
    at tipas, db kNormal
    at arg1, db argNear
    at arg2, db argNone
    iend
opE9: istruc opkodas
    at pavadinimas, dw t_opJMP
    at tipas, db kNormal
    at arg1, db argNear
    at arg2, db argNone
    iend
opEA: istruc opkodas
    at pavadinimas, dw t_opJMP
    at tipas, db kNormal
    at arg1, db argFar
    at arg2, db argNone
    iend
opEB: istruc opkodas
    at pavadinimas, dw t_opJMP
    at tipas, db kNormal
    at arg1, db argShort
    at arg2, db argNone
    iend
opEC: istruc opkodas
    at pavadinimas, dw t_opIN
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argDX
    iend
opED: istruc opkodas
    at pavadinimas, dw t_opIN
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argDX
    iend
opEE: istruc opkodas
    at pavadinimas, dw t_opOUT
    at tipas, db kNormal
    at arg1, db argAL
    at arg2, db argDX
    iend
opEF: istruc opkodas
    at pavadinimas, dw t_opOUT
    at tipas, db kNormal
    at arg1, db argAX
    at arg2, db argDX
    iend
opF0: istruc opkodas
    at pavadinimas, dw t_opLOCK
    at tipas, db kPrefixOp
    at arg1, db argNone
    at arg2, db argNone
    iend
opF1: istruc opkodas
    at pavadinimas, dw t_opUNKNOWN
    at tipas, db kUnknown
    at arg1, db argNone
    at arg2, db argNone
    iend
opF2: istruc opkodas
    at pavadinimas, dw t_opREPNE
    at tipas, db kPrefixOp
    at arg1, db argNone
    at arg2, db argNone
    iend
opF3: istruc opkodas
    at pavadinimas, dw t_opREP
    at tipas, db kPrefixOp
    at arg1, db argNone
    at arg2, db argNone
    iend
opF4: istruc opkodas
    at pavadinimas, dw t_opHLT
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opF5: istruc opkodas
    at pavadinimas, dw t_opCMC
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opF6: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opF7: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem16
    at arg2, db argNone
    iend
opF8: istruc opkodas
    at pavadinimas, dw t_opCLC
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opF9: istruc opkodas
    at pavadinimas, dw t_opSTC
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opFA: istruc opkodas
    at pavadinimas, dw t_opCLI
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opFB: istruc opkodas
    at pavadinimas, dw t_opSTI
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opFC: istruc opkodas
    at pavadinimas, dw t_opCLD
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opFD: istruc opkodas
    at pavadinimas, dw t_opSTD
    at tipas, db kNormal
    at arg1, db argNone
    at arg2, db argNone
    iend
opFE: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem8
    at arg2, db argNone
    iend
opFF: istruc opkodas
    at pavadinimas, dw t_opEMPTY
    at tipas, db kExtraOpk
    at arg1, db argRegMem16
    at arg2, db argNone
    iend
