% Demo2.asm    Some Simple Addressing

WRST PROMPT
RDI  NUM
RDNL
LDA  R5, NUM
LD   R11,*R5
IA   R11,#1000
WRI  R11
WRNL
WRI  R5
WRNL
WRI  *R5
WRNL
WRI  NUM
WRNL
WRI  +2(R5)
WRNL
WRI  +4(R5)
WRNL

HALT

% Data Area
% ---------
LABEL   PROMPT
STRING  "Enter an integer:: "
LABEL   NUM
INT     0
INT     801
INT     -13
