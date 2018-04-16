:/  13IfThen.csc

    Tests a simple if statement with an else clause.
/:

:A
	int: n, m;

	:O "Enter two integers: ";
	:I n, m;
	:? (n > m )
		:O n, " is greater than ", m, "\n";
	:!
		:O n, " is less than or equal to ", m, "\n";
	:.
	:O "\n";
:Z
