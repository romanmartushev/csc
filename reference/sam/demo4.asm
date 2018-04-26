% Demo4.asm    Floating Point Arithmetic

WRST PROMPT
RDF  NUM1  
RDF  NUM2
RDNL

LDA  R1,NUM1

LD   R7, +0(R1)
LD   R8, +2(R1)
FA   R7,NUM2
WRF  R7
WRNL

LD   R7,+0(R1)
LD   R8, +2(R1)
FS   R7,NUM2
WRF  R7
WRNL

LD   R7,+0(R1)
LD   R8, +2(R1)
FM   R7,NUM2
WRF  R7
WRNL

LD   R7,+0(R1)
LD   R8, +2(R1)
FD   R7,NUM2
WRF  R7
WRNL

HALT

% Data Area
% ---------
LABEL   PROMPT
STRING  "Enter two real numbers:: "
LABEL   NUM1
SKIP    4
LABEL   NUM2
SKIP    4