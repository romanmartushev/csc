% Demo17.asm     SLDZ, SLDO, SLDE, and SLDC

      WRNL
      WRST PROMPT1
      RDBW WORD1
      WRNL
      WRST PROMPT2
      RDBW WORD2
      WRNL
      WRNL
      WRST TAB6
      WRBW WORD1
      WRST SPACE
      WRBW WORD2
      WRNL
      WRNL
%
      LD   R0,WORD1
      LD   R1,WORD2
      SLDZ R0,8
      WRST SLDZ
      WRBW R0
      WRST SPACE
      WRBW R1
      WRNL
%
      LD   R0,WORD1
      LD   R1,WORD2
      SLDO R0,8
      WRST SLDO
      WRBW R0
      WRST SPACE
      WRBW R1
      WRNL
%
      LD   R0,WORD1
      LD   R1,WORD2
      SLDE R0,8
      WRST SLDE
      WRBW R0
      WRST SPACE
      WRBW R1
      WRNL
%
      LD   R0,WORD1
      LD   R1,WORD2
      SLDC R0,8
      WRST SLDC
      WRBW R0
      WRST SPACE
      WRBW R1
      WRNL
%
      HALT
% Data
% ----
LABEL PROMPT1
      STRING "1st binary word:: "
LABEL PROMPT2
      STRING "2nd binary word:: "
LABEL SLDZ
      STRING "SLDZ:: "
LABEL SLDO
      STRING "SLDO:: "
LABEL SLDE
      STRING "SLDE:: "
LABEL SLDC
      STRING "SLDC:: "
LABEL SPACE
      STRING " "
LABEL TAB6
      STRING "      "
LABEL WORD1
      SKIP 2
LABEL WORD2
      SKIP 2
