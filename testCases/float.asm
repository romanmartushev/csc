LDA       R15,VARS
LDA       R14,STRINGS
LD        R0,#3
STO       R0,+4(R15)
LD        R0,#5
STO       R0,+6(R15)
WRF       +0(R15)
WRNL      
LD        R0,+0(R15)
FLT       R1,#5
FM        R0,R1
STO       R0,+8(R15)
LD        R0,+10(R15)
STO       R0,+0(R15)
LD        R0,+12(R15)
STO       R0,+0(R15)
WRF       +0(R15)
WRNL      
HALT      
LABEL     STRINGS
LABEL     VARS
REAL      3.500000
REAL      0.000000
REAL      3.000000
