% Demo15.asm     SLZ, SLO, SLE, and SLC

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
      SLZ  R0,7
      WRST SLZ
      WRBW R0
      WRNL
%
      LD   R0,WORD1
      SLO  R0,7
      WRST SLO
      WRBW R0
      WRNL
%
      LD   R0,WORD1
      SLE  R0,7
      WRST SLE
      WRBW R0
      WRNL
%
      LD   R0,WORD1
      SLC  R0,7
      WRST SLC
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
LABEL SLZ
      STRING "SLZ:: "
LABEL SLO
      STRING "SLO:: "
LABEL SLE
      STRING "SLE:: "
LABEL SLC
      STRING "SLC:: "
LABEL WORD1
      SKIP 2
