% Demo19.asm    

LDA       R15,VAR9999 % Variables
LDA       R14,STR9999 % Strings
LDA       R13,FLT9999 % Real Constants
WRST      +0(R14)
WRF       +0(R15)
WRNL      
RDF       +4(R15)
WRST      +6(R14)
WRF       +4(R15)
WRNL      
WRF       +4(R13)
WRNL      
LABEL     EX0
HALT      
LABEL     VAR9999    % *** Variables
REAL            5.3  %  REAL x
REAL              0  %  REAL y
LABEL     STR9999    % *** Strings
STRING   "x = "
STRING   "y = "
LABEL     FLT9999    % *** Real Constants
REAL            5.3
REAL           76.5

