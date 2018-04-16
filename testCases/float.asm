LDA       R15,VARS
LDA       R14,STRINGS
LD        R0,#2
FLT       R1,+0(R15)
FA        R0,R1
STO       R0,+4(R15)
LD        R0,+6(R15)
STO       R0,+0(R15)
WRF       +0(R15)
WRNL      
HALT      
LABEL     STRINGS
LABEL     VARS
REAL      3.500000
REAL      0.000000
