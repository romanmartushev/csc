% Demo10.asm     INT and SKIP

      WRI NUM1
      WRNL
      WRI NUM2
      WRNL
      WRI NUM3
      WRNL
      HALT
% Data
% ----
LABEL NUM1
      INT  4095
LABEL NUM2
      INT -305
      SKIP 2
LABEL NUM3
      INT  7
