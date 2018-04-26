:/ 06Assign.csc

   Arithmetic expressions and assignments.
/:

:A
	int:  x;
	float: y, z;
	int:  n;

	x := (3 + 5) * 4;
	:O "\nx =", x;
	y := (2.3 + 7.1) * 5.0;
	:O "\ny =", y;
	z := 5.0 * (3.6 - 2.9);
	:O "\nz =", z;
	n := ((2 + 6 * 9) - 8) / 7;
	:O "\nn =", n;
	:N;
:Z
