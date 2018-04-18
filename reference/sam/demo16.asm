% Demo16.asm     SRDZ, SRDO, SRDE, and SRDC

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
      SRDZ R0,8
      WRST SRDZ
      WRBW R0
      WRST SPACE
      WRBW R1
      WRNL
%
      LD   R0,WORD1
      LD   R1,WORD2
      SRDO R0,8
      WRST SRDO
      WRBW R0
      WRST SPACE
      WRBW R1
      WRNL
%
      LD   R0,WORD1
      LD   R1,WORD2
      SRDE R0,8
      WRST SRDE
      WRBW R0
      WRST SPACE
      WRBW R1
      WRNL
%
      LD   R0,WORD1
      LD   R1,WORD2
      SRDC R0,8
      WRST SRDC
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
LABEL SRDZ
      STRING "SRDZ:: "
LABEL SRDO
      STRING "SRDO:: "
LABEL SRDE
      STRING "SRDE:: "
LABEL SRDC
      STRING "SRDC:: "
LABEL SPACE
      STRING " "
LABEL TAB6
      STRING "      "
LABEL WORD1
      SKIP 2
LABEL WORD2
      SKIP 2
