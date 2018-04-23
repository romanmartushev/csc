LDA       R15,VARS
LDA       R14,STRINGS
LD        R0,#0
STO       R0,+0(R15)
WRI       #8
WRNL      
WRI       +0(R15)
HALT      
LABEL     STRINGS
LABEL     VARS
INT    0
