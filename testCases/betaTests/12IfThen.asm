LDA       R15,VARS
LDA       R14,STRINGS
LD        R0,#0
STO       R0,+0(R15)
LD        R0,#0
STO       R0,+2(R15)
WRST      +0(R14)
RDI       +0(R15)
RDI       +2(R15)
LD        R0,+0(R15)
IC        R0,+2(R15)
JLE       IFEND1
WRI       +0(R15)
WRST      +20(R14)
WRI       +2(R15)
WRST      +38(R14)
LABEL     IFEND1
LD        R0,+2(R15)
IC        R0,+0(R15)
JLE       IFEND2
WRI       +2(R15)
WRST      +40(R14)
WRI       +0(R15)
WRST      +58(R14)
LABEL     IFEND2
WRST      +60(R14)
HALT      
LABEL     STRINGS
STRING    "Enter two integers:: "
STRING    " is greater than "
STRING    ":010"
STRING    " is greater than "
STRING    ":010"
STRING    ":010"
LABEL     VARS
INT    0
INT    0
