LDA       R15,VARS
LD        R0,#0
STO       R0,+26(R15)
LD        R0,#47
STO       R0,+28(R15)
LD        R0,#8
STO       R0,+30(R15)
LD        R0,#5
STO       R0,+32(R15)
WRST      +0(R15)
WRNL      
WRI       +30(R15)
WRNL      
WRST      +10(R15)
WRNL      
WRI       +28(R15)
WRNL      
WRNL      
WRST      +0(R15)
WRNL      
WRST      +10(R15)
WRNL      
WRST      +34(R15)
WRNL      
WRI       +28(R15)
WRNL      
WRNL      
HALT      
LABEL     VARS
STRING    "hello"
SKIP      3
STRING    "world"
SKIP      8
STRING    "HELLOCAAAAAAAB"
SKIP      4
