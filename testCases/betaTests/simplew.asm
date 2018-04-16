LDA       R15,VARS
LDA       R14,STRINGS
LD        R0,#3
STO       R0,+0(R15)
LD        R0,#30
STO       R0,+2(R15)
LABEL     WHLBEG1
LD        R0,+0(R15)
IC        R0,+2(R15)
JGE       WHLEND1
WRST      +0(R14)
LD        R0,+0(R15)
IA        R0,#1
STO       R0,+4(R15)
LD        R0,+4(R15)
STO       R0,+0(R15)
WRI       +0(R15)
JMP       WHLBEG1
LABEL     WHLEND1
HALT      
LABEL     STRINGS
STRING    "hi there"
LABEL     VARS
INT    3
INT    30
INT    0
