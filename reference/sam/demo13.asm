% Demo13.asm     RDBW and WRBW

      WRST PROMPT
      RDBW WORD1
      RDNL
      WRBW WORD1
      WRNL
      WRST PROMPT
      RDBW WORD2
      RDNL
      WRBW WORD2
      WRNL
      WRNL
      BI   R2,WORD1
      WRST INVERT
      WRBW R2
      WRNL
      BI   R3,WORD2
      WRST INVERT
      WRBW R3
      WRNL
      WRNL
      LD   R10,WORD1
      BO   R10,WORD2
      WRST OR
      WRBW R10
      WRNL
      WRNL
      LD   R11,WORD1
      BA   R11,WORD2
      WRST AND
      WRBW R11
      WRNL
      HALT
% Data
% ----
LABEL PROMPT
      STRING "Enter binary word:: "
LABEL INVERT
      STRING "Inversion:: "
LABEL OR
      STRING "Or:: "
LABEL AND
      STRING "And:: "
LABEL WORD1
      SKIP 2
LABEL WORD2
      SKIP 2
