LDA       R15,VARS
LD        R0,#5
STO       R0,+8(R15)
LD        R0,#1
STO       R0,+0(R15)
LD        R0,+0(R15)
FD        R0,+8(R15)
STO       R0,+14(R15)
LD        R0,+14(R15)
STO       R0,+0(R15)
RDF       +0(R15)
LD        R0,+0(R15)
FA        R0,+8(R15)
STO       R0,+18(R15)
WRF       +18(R15)
HALT      
LABEL     VARS
SKIP      14
