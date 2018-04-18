% Demo14.asm     SRZ, SRO, SRE, and SRC

      WRNL
      WRST PROMPT
      RDBW WORD1
      RDNL
      WRNL
      WRST TAB5
      WRBW WORD1
      WRNL
      WRNL
%
      LD   R0,WORD1
      SRZ  R0,7
      WRST SRZ
      WRBW R0
      WRNL
%
      LD   R0,WORD1
      SRO  R0,7
      WRST SRO
      WRBW R0
      WRNL
%
      LD   R0,WORD1
      SRE  R0,7
      WRST SRE
      WRBW R0
      WRNL
%
      LD   R0,WORD1
      SRC  R0,7
      WRST SRC
      WRBW R0
      WRNL
      WRNL
      HALT
% Data
% ----
LABEL PROMPT
      STRING "Enter binary word:: "
LABEL TAB5
      STRING "     "
LABEL SRZ
      STRING "SRZ:: "
LABEL SRO
      STRING "SRO:: "
LABEL SRE
      STRING "SRE:: "
LABEL SRC
      STRING "SRC:: "
LABEL WORD1
      SKIP 2
