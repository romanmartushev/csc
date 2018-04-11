LDA       R15,VARS
LDA       R14,STRINGS
LD        R0,#0
STO       R0,+0(R15)
LD        R0,#0
STO       R0,+2(R15)
LD        R0,#0
STO       R0,+4(R15)
LD        R0,#0
STO       R0,+8(R15)
WRI       #5
WRI       #3
WRI       #2
WRI       #4
WRST      +0(R14)
WRI       #1
WRST      +4(R14)
WRI       #8
WRST      +16(R14)
HALT      
LABEL     STRINGS
STRING    "\n\n"
STRING    " :"start:" "
STRING    "*"
LABEL     VARS
