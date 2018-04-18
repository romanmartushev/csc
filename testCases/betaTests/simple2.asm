LDA       R15,VARS
LDA       R14,STRINGS
LD        R0,#5
STO       R0,+0(R15)
LD        R0,+0(R15)
IC        R0,#5
WRST      +0(R14)
LABEL     IFEND1
HALT      
LABEL     STRINGS
STRING    "1"
LABEL     VARS
INT    5
