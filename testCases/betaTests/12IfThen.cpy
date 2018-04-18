::  12IfThen.csc
::
::  Tests simple if statements (no else clauses).

:A

	int: n := 0;
	int: m := 0;

	:O "Enter two integers: ";
	:I n, m;
	:? (n > m )
		:O n, " is greater than ", m;
	:.

	:? (m > n)
		:O m, " is greater than ", n;
	:.
	

:Z
