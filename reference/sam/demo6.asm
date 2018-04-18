% Demo6.asm    Integer Comparison

% Main Program
% ------------
      WRST PROMPT
      RDI  R0
      RDI  R1
      JSR  R15,LARGEST
      WRNL
      WRI  R2
      WRST MSG
      WRNL
      HALT

% Subroutine
%-----------
LABEL LARGEST
      IC   R0,R1
      JLE  BIGR1
      LD   R2,R0
      JMP  *R15
LABEL BIGR1
      LD   R2,R1
      JMP  *R15

% Data
% ----
LABEL PROMPT
      STRING "Enter 2 integers:: "
LABEL MSG
      STRING " is the largest."
