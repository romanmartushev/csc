::  21ForLoop.csc
::
::  Simple for loops.

:A
	int: n, k;
	:O "Enter a positive integer:";
	:I n;
	:N;
	:O "Forward: ";
	:F ( k := 1; k <= n; k := k + 1)
		:O k;
		:N;
	:.

	:O "\n";
	:O "Backward: ";
	:F (k := n; k >= 1; k := k - 1)
		:O k;
		:N;
	:.
	:O "\n";

:Z
