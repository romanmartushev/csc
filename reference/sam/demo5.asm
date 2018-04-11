% Demo5.asm   Addressing Modes

WRST PROMPT
RDI  NUM 
LDA  R0,NUM
STO  R0,ADDR
LDA  R1,ADDR

WRI  NUM      % memory direct addressing
WRNL

WRI  +0(R0)   % indexed addressing
WRNL

WRI  *R0      % register indirect addressing
WRNL

WRI  *ADDR    % memory indirect addressing
WRNL

WRI  *+2(R0)  % indexed indirect addressing
WRNL

WRI  &+24     % PC relative
WRNL

HALT

% Data Area
% ---------
LABEL   PROMPT
STRING  "Enter an integer:: "
LABEL   NUM
SKIP    2
LABEL   ADDR
SKIP    2
