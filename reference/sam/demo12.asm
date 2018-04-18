% Demo12.asm     STRING and SKIP

      WRST STR1
      WRNL
      WRST STR2
      WRNL
      WRST STR3
      WRNL
      HALT
% Data
% ----
LABEL STR1
      STRING "Have:007 a ni:010ce day!"
LABEL STR2
      STRING "You said:::"help me:" and I did."
      SKIP  100
LABEL STR3
      STRING "Bye, for now."
