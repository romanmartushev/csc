% Demo18.asm    RDHD, RDHW, WRHD, and WRHW

      WRST PROMPT
      RDHW R5
      WRNL
      WRHW R5
      WRNL
      WRHD R5
      WRNL
      WRHW X
      WRNL
      WRST PROMPT2
      RDHD R6
      WRHD R6
      HALT

% Data
% ----
LABEL PROMPT
      STRING "Enter hex word:: "
LABEL PROMPT2
      STRING "Enter hex digit:: "
LABEL X
      INT 32767
