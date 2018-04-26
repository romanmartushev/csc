::  12IfThen.csc
::
::  Tests simple if statements (no else clauses).

:A

	int: n, m;
	

	:O "Enter two integers: ";
	:I n, m;
	:? (n > m )
		:O n, " is greater than ", m, "\n";
	:.
	:? (m > n)
		:O m, " is greater than ", n, "\n";
	:.
	:O "\n";

:Z
