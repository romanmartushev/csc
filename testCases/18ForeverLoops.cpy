:: 18ForeverLoops.csc
::
::  Uses bool constants and variables as conditions.

:A
	int: i;
	int: cond1, cond2;
	::cond1 := 1 == 1; cond2 := 1==0;
	:O "\nwhile true do ... end\n";
	:W (1 == 1)
		:O "i = ";
		:I i;
		:?( i == 0 ) :B; :.
		:O i;
		:N;
	:.

	:O "\ndo ... until false;\n";
	:D
		:O "i = ";
		:I i;
		:? (i == 0) :B; :.
		:O i;
		:N;
	:U (1 == 0);
:Z
