LDA       R15,VAR9999 % Variables
LDA       R14,STR9999 % Strings
LDA       R13,FLT9999 % Real Constants
LDA       R12,TMP9999 % Temporary Storage
WRST      +0(R15)  % name
WRNL      
WRST      +12(R15)  % place
WRNL      
LABEL HALT999
HALT      
% WRBOOL Subroutine: writes a bool value
% --------------------------------------
LABEL WRBOOL
IC        R0,#0
JNE       TOUT
WRST      FALSE
JMP       *R7
LABEL TOUT
WRST      TRUE
JMP       *R7
LABEL FALSE
STRING    "false"
LABEL TRUE
STRING    "true"
% STRCMP Subroutine: compares the strings pointed to
% --------------------------------------------------
%                    by R4 and R5.
LABEL STRCMP
LD        R0,*R4
SRZ       R0,8
LD        R1,*R5
SRZ       R1,8
IC        R0,#0
JEQ       ENDCMP
IC        R1,#0
JEQ       ENDCMP
IC        R0,R1
IA        R4,#1
IA        R5,#1
JEQ       STRCMP
JMP       *R7
LABEL ENDCMP
IC        R0,R1
JMP       *R7
LABEL VAR9999 % ... Variables
STRING "Ralph"			 
SKIP        7
STRING "Bemidji"
SKIP        5
STRING "Ralph"	
SKIP        7
STRING ""	
SKIP       12
LABEL STR9999 % ... String Literals
LABEL FLT9999 % ...Real Literals
LABEL TMP9999
