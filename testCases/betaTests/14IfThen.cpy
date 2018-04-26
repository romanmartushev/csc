::  14IfThen.csc

::  Tests nested if statement with else clauses.

:A
	int: n, m;	
	:O "Enter two integers: ";
	:I n, m;
	:? (n > m)
		:O n, " is greater than ", m, "\n";
	:! 
		:? (n < m)
			:O n, " is less than ", m, "\n";
		:!
			:O n, " is equal to ", m, "\n";
		:.
	:.
	:O "\n";

:Z
