::  16While.csc
::
::  Simple while loops.

:A

	int: n, k;
	:O "Enter a positive integer upper limit for counting: ";
	:I n;
	:N;
	k := 1;
	:O "Forward: ";
	:W (k <= n)
		:O k;
		k := k + 1;
	:.

	:O "\n";
	k := n;
	:O "Backward: ";
	:W (k >= 1)
		:O k;
		k := k - 1;
	:.
	:O "\n";

:Z
