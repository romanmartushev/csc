% Demo8.asm    Floating Point Comparison

% Main Program
% ------------
      WRST PROMPT
      RDF  R0
      RDF  R2
      JSR  R15,LARGEST
      WRNL
      WRF  R4
      WRST MSG
      WRNL
      HALT

% Subroutine
%-----------
LABEL LARGEST
      FC   R0,R2
      JLE  BIGR2
      LD   R4,R0
      LD   R5,R1
      JMP  *R15
LABEL BIGR2
      LD   R4,R2
      LD   R5,R3
      JMP  *R15

% Data
% ----
LABEL PROMPT
      STRING "Enter 2 real numbers:: "
LABEL MSG
      STRING " is the largest."
