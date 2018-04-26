% Demo7.asm    Block Move

      WRST BSU
	  WRNL
	  CLR  R8
	  LDA  R13,BSU2

	  LDA  R4,BSU
	  LD   R5,#7
	  BKT  R4,BSU2
	  STO  R8,+7(R13)

	  WRST BSU2
	  WRNL

      IA   R4,#8
	  LD   R5,#5
	  BKT  R4,BSU2
	  STO  R8,+5(R13)

	  WRST BSU2
	  WRNL

      IA   R4,#6
	  LD   R5,#10
	  BKT  R4,BSU2
	  STO  R8,+10(R13)

	  WRST BSU2
	  WRNL

	  HALT

% Data
% ----
LABEL BSU
      STRING "Bemidji State University"
LABEL BSU2
      SKIP 30
